#include "leveleditor.h"

LevelEditor::LevelEditor(int screenWidthCamera, int screenHeightCamera) : Scene::Scene(screenWidthCamera, screenHeightCamera)
{
	levelLoader = new Loadlevel();
	level = nullptr;
	textfile = new Textfile();

	world = new b2World(b2Vec2(0.0f, 0.0f));
	world->SetAllowSleeping(false);

	canvasEditor = new Sprite(400, 1080, glm::vec4(0.0f, 0.5f, 0.5f, 0.5f));
	canvasEditor->SetRenderer(RenderManager::GetSimpleRenderer("hud"));
	canvasEditor->localPosition.x = -760;
	this->AddChild(canvasEditor);

	properties = new Text("properties", ResourceManager::GetFont("fonts/arial.ttf", 512, 48), glm::vec3(1,1,1), Text::AlignmentX::centerX, Text::AlignmentY::centerY);
	properties->localPosition = glm::vec2(0.0f, 375);
	canvasEditor->AddChild(properties);

	saveButton = new Button(400/3, 75, 0, true, camera);
	saveButton->SetColor(glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));
	saveButton->CreateText("save", ResourceManager::GetFont("fonts/arial.ttf", 512, 48), glm::vec3(1, 1, 1));
	saveButton->localPosition = glm::vec2(-200 + saveButton->GetWidth()/2 * 1, -540 + 75 / 2);
	saveButton->SetRenderer(RenderManager::GetSimpleRenderer("hud"));
	canvasEditor->AddChild(saveButton);

	loadButton = new Button(400/3, 75, 0, true, camera);
	loadButton->SetColor(glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));
	loadButton->CreateText("load", ResourceManager::GetFont("fonts/arial.ttf", 512, 48), glm::vec3(1, 1, 1));
	loadButton->localPosition = glm::vec2(-200 + loadButton->GetWidth() / 2 + saveButton->GetWidth(), -540 + 75 / 2);
	loadButton->SetRenderer(RenderManager::GetSimpleRenderer("hud"));
	canvasEditor->AddChild(loadButton);

	menuButton = new Button(400 / 3, 75, 0, true, camera);
	menuButton->SetColor(glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));
	menuButton->CreateText("menu", ResourceManager::GetFont("fonts/arial.ttf", 512, 48), glm::vec3(1, 1, 1));
	menuButton->localPosition = glm::vec2(-200 + menuButton->GetWidth() / 2 + loadButton->GetWidth() + saveButton->GetWidth(), -540 + 75 / 2);
	menuButton->SetRenderer(RenderManager::GetSimpleRenderer("hud"));
	canvasEditor->AddChild(menuButton);

	CreateEditorModeTickbox("select", glm::vec2(-150, -400));
	CreateEditorModeTickbox("place", glm::vec2(-75, -400));

	mode = EditorMode::select;
	tickboxesMode[0]->SetActive(true);

	// Player options
	playerCanvas = CreateCanvasPlaceable();
	inputPlayerRotation = CreateInputFloat(playerCanvas, "0", glm::vec2(-150, 250), "rotation");
	inputFloats.push_back(&inputPlayerRotation);
	_player = nullptr;
	// Wall options
	wallCanvas = CreateCanvasPlaceable();
	inputWallWidth = CreateInputFloat(wallCanvas, "100", glm::vec2(-150, 250), "width");
	inputFloats.push_back(&inputWallWidth);
	inputWallRotation = CreateInputFloat(wallCanvas, "0", glm::vec2(0, 250), "rotation");
	inputFloats.push_back(&inputWallRotation);
	// Mirror options
	mirrorCanvas = CreateCanvasPlaceable();
	inputMirrorRotation = CreateInputFloat(mirrorCanvas, "0", glm::vec2(-150, 250), "rotation");
	inputFloats.push_back(&inputMirrorRotation);
	// Crystal options
	crystalCanvas = CreateCanvasPlaceable();
	inputCrystalRotation = CreateInputFloat(crystalCanvas, "0", glm::vec2(-150, 250), "rotation");
	inputFloats.push_back(&inputCrystalRotation);
	// Floor options
	floorCanvas = CreateCanvasPlaceable();
	inputFloorWidth = CreateInputFloat(floorCanvas, "200", glm::vec2(-150, 250), "width");
	inputFloats.push_back(&inputFloorWidth);
	// Door options
	doorCanvas = CreateCanvasPlaceable();
	inputDoorRotation = CreateInputFloat(doorCanvas, "0", glm::vec2(-150, 250), "rotation");
	inputFloats.push_back(&inputDoorRotation);
	// Enemy options
	enemyCanvas = CreateCanvasPlaceable();
	inputEnemyRotation = CreateInputFloat(enemyCanvas, "0", glm::vec2(-150, 250), "rotation");
	inputFloats.push_back(&inputEnemyRotation);
	// Finish options
	finishCanvas = CreateCanvasPlaceable();
	inputFinishWidth = CreateInputFloat(finishCanvas, "400", glm::vec2(-150, 250), "width");
	inputFloats.push_back(&inputFinishWidth);
	inputFinishHeight = CreateInputFloat(finishCanvas, "100", glm::vec2(0, 250), "height");
	inputFloats.push_back(&inputFinishHeight);
	_finish = nullptr;

	CreatePlaceablesTickbox("player", glm::vec2(-150, 500));
	CreatePlaceablesTickbox("wall", glm::vec2(-75, 500));
	CreatePlaceablesTickbox("mirror", glm::vec2(0, 500));
	CreatePlaceablesTickbox("crystal", glm::vec2(75, 500));
	CreatePlaceablesTickbox("floor", glm::vec2(150, 500));
	CreatePlaceablesTickbox("door", glm::vec2(-150, 425));
	CreatePlaceablesTickbox("enemy", glm::vec2(-75, 425));
	CreatePlaceablesTickbox("finish", glm::vec2(0, 425));

	canvasEditor->AddChild(playerCanvas);
	currentPlaceable = Placeables::player;
	currentlySelected.type = currentPlaceable;
	tickboxes[0]->SetActive(true);
}

LevelEditor::~LevelEditor()
{
	if (_player != nullptr) {
		delete _player;
	}
	if (_finish != nullptr) {
		delete _finish;
	}
	delete textfile;
	delete saveButton;
	delete loadButton;
	delete menuButton;

	delete canvasEditor;
	delete properties;
	// Delete the properties canvas
	std::vector<Sprite*>::iterator itPropertiesCanvas = propertiesCanvas.begin();
	while (itPropertiesCanvas != propertiesCanvas.end()) {
		delete (*itPropertiesCanvas);
		itPropertiesCanvas = propertiesCanvas.erase(itPropertiesCanvas);
	}
	// Delete the tickboxes
	std::vector<Tickbox*>::iterator itTickbox = tickboxes.begin();
	while (itTickbox != tickboxes.end()) {
		delete (*itTickbox);
		itTickbox = tickboxes.erase(itTickbox);
	}
	// Delete the text of the tickboxes
	std::vector<Text*>::iterator itTickboxText = tickboxesText.begin();
	while (itTickboxText != tickboxesText.end()) {
		delete (*itTickboxText);
		itTickboxText = tickboxesText.erase(itTickboxText);
	}
	// Delete the tickboxes for the modes
	std::vector<Tickbox*>::iterator itTickboxMode = tickboxesMode.begin();
	while (itTickboxMode != tickboxesMode.end()) {
		delete (*itTickboxMode);
		itTickboxMode = tickboxesMode.erase(itTickboxMode);
	}
	// Delete the tickboxes for the text of the modes
	std::vector<Text*>::iterator itTickboxModeText = tickboxesModeText.begin();
	while (itTickboxModeText != tickboxesModeText.end()) {
		delete (*itTickboxModeText);
		itTickboxModeText = tickboxesModeText.erase(itTickboxModeText);
	}
	// Delete the inputFloats
	std::vector<InputFloat*>::iterator itInputFloat = inputFloats.begin();
	while (itInputFloat != inputFloats.end()) {
		delete (*itInputFloat)->input;
		delete (*itInputFloat)->text;
		itInputFloat = inputFloats.erase(itInputFloat);
	}
	// Delete the editor objects
	std::vector<EditorObject>::iterator itEditorObjects = editorObjects.begin();
	while (itEditorObjects != editorObjects.end()) {
		delete (*itEditorObjects).entity;
		itEditorObjects = editorObjects.erase(itEditorObjects);
	}

	delete world;
	delete levelLoader;
	if (level != nullptr) {
		delete level;
	}
}

void LevelEditor::Update(double deltaTime)
{
	// DRAW
	for (int i = 0; i < editorObjects.size(); i++) {
		editorObjects[i].entity->Draw();
		editorObjects[i].entity->DrawChilderen(this);
	}
	if (currentlySelected.entity != nullptr && currentlySelected.type == Placeables::player || currentlySelected.type == Placeables::finish) {
		currentlySelected.entity->Draw();
		currentlySelected.entity->DrawChilderen(this);
	}
	if (_finish != nullptr) {
		DebugRenderer::Line(_finish->localPosition + glm::vec2(inputFinishWidth.output / 2 * -1, inputFinishHeight.output / 2), _finish->localPosition + glm::vec2(inputFinishWidth.output / 2, inputFinishHeight.output / 2), glm::vec3(1, 0, 1));// Horizontal positive
		DebugRenderer::Line(_finish->localPosition + glm::vec2(inputFinishWidth.output / 2, inputFinishHeight.output / 2), _finish->localPosition + glm::vec2(inputFinishWidth.output / 2, inputFinishHeight.output / 2 * -1), glm::vec3(1, 0, 1));// Vertical positive
		DebugRenderer::Line(_finish->localPosition + glm::vec2(inputFinishWidth.output / 2 * -1, inputFinishHeight.output / 2 * -1), _finish->localPosition + glm::vec2(inputFinishWidth.output / 2, inputFinishHeight.output / 2 * -1), glm::vec3(1, 0, 1));// Horizontal negative
		DebugRenderer::Line(_finish->localPosition + glm::vec2(inputFinishWidth.output / 2 * -1, inputFinishHeight.output / 2), _finish->localPosition + glm::vec2(inputFinishWidth.output / 2 * -1, inputFinishHeight.output / 2 * -1), glm::vec3(1, 0, 1));// Vertical negative
	}
	if (_player != nullptr) {
		_player->Draw();
		_player->DrawChilderen(this);
	}
	// END OF DRAWING
	if (UpdateTickboxes()) {
		// If true that means one of the tickboxes has been pressed so we skip one frame to avoid conflicts
		std::cout << "updated tick boxes" << std::endl;
	}
	if (currentlySelected.entity != nullptr && Input::MousePress(1)) {
		Place();
		std::cout << "place" << std::endl;
		currentlySelected.entity = nullptr;
	}

	if (currentlySelected.entity != nullptr) {
		//if (mode == EditorMode::place) {
			currentlySelected.entity->localPosition = Input::GetMousePositionWorldSpace();
		//}
		UpdateInputFloats();
		UpdateCurrentlySelected();
	}
	else if (mode == EditorMode::place) {
		GetPlaceable();
	}

	if (saveButton->Down() && currentlySelected.entity == nullptr) {
		Save("level3.bin");
	}
	if (loadButton->Down() && currentlySelected.entity == nullptr) {
		level = levelLoader->LoadFromFile("level3.bin");
	}

	if (Input::MousePress(0) && mode == EditorMode::select) {
		b2Body* bodylist = world->GetBodyList();
		glm::vec2 _mousePos = Input::GetMousePositionWorldSpace();
		b2Vec2 mousePos = b2Vec2(_mousePos.x * B2Entity::p2m, _mousePos.y * B2Entity::p2m);

		while (bodylist != NULL) {
			if (bodylist->GetFixtureList()->TestPoint(mousePos)) {
				B2Entity* _selected = static_cast<B2Entity*>(bodylist->GetFixtureList()->GetUserData());
				if (_player == _selected) {
					currentlySelected.entity = _player;
					currentlySelected.type = Placeables::player;
					return;
				}
				else if (_finish == _selected) {
					currentlySelected.entity = _finish;
					currentlySelected.type = Placeables::finish;
					return;
				}
				for (int i = 0; i < editorObjects.size(); i++) {
					if (editorObjects[i].entity == _selected) {
						currentlySelected = editorObjects[i];
						break;
					}
				}
			}
			bodylist = bodylist->GetNext();
		}
	}
}

bool LevelEditor::UpdateTickboxes()
{
	bool change = false;
	// Update the tickboxes
	for (int i = 0; i < tickboxes.size(); i++) {
		if (i == currentPlaceable) {
			tickboxes[i]->SetActive(true);
		}
		if (tickboxes[i]->IsActive() && i != currentPlaceable) {
			std::cout << "test" << std::endl;
			DeleteCurrentlySeleceted();
			tickboxes[currentPlaceable]->SetActive(false);
			canvasEditor->RemoveChild(propertiesCanvas[currentPlaceable]);
			currentPlaceable = static_cast<Placeables>(i);
			canvasEditor->AddChild(propertiesCanvas[currentPlaceable]);
			change = true;
		}
	}
	// Update the tickboxes of the modes
	for (int i = 0; i < tickboxesMode.size(); i++) {
		if (i == mode) {
			tickboxesMode[i]->SetActive(true);
		}
		if (tickboxesMode[i]->IsActive() && i != mode) {
			DeleteCurrentlySeleceted();
			tickboxesMode[mode]->SetActive(false);
			mode = static_cast<EditorMode>(i);
			change = true;
		}
	}
	return change;
}

void LevelEditor::UpdateInputFloats()
{
	for (int i = 0; i < inputFloats.size(); i++) {
		inputFloats[i]->output = inputFloats[i]->input->GetFloat();
	}
}

Level * LevelEditor::GetCurrentLevel()
{
	return level;
}

void LevelEditor::StopCurrentLevel()
{
	if (level != nullptr) {
		delete level;
		level = nullptr;
	}
}

void LevelEditor::Save(char* levelname)
{
	std::cout << "save!" << std::endl;
	/*textfile->Create(levelname);
	for (int i = 0; i < walls.size(); i++) {
		std::string walldata = "wall ";
		walldata += std::to_string(walls[i]->localPosition.x);
		walldata += " ";
		walldata += std::to_string(walls[i]->localPosition.y);
		walldata += " ";
		walldata += std::to_string(walls[i]->localAngle);
		walldata += " ";
		walldata += std::to_string(walls[i]->GetWidth());
		walldata += " ";
		textfile->Write(walldata);
	}
	textfile->Close();*/
}

void LevelEditor::Place()
{
	if (currentlySelected.type == Placeables::player) {
		if (mode == EditorMode::place && _player != nullptr) {
			delete _player;
		}
		_player = dynamic_cast<Player*>(currentlySelected.entity);
		_player->CreateCircleCollider(40.0f, true, false);
	}
	else if (currentlySelected.type == Placeables::wall) {
		B2Entity* _wall = dynamic_cast<B2Entity*>(currentlySelected.entity);
		_wall->CreateBoxCollider(_wall->GetWidth(), 100, glm::vec2(0, 0), false, false);
	}
	else if (currentlySelected.type == Placeables::mirror) {
		
	}
	else if (currentlySelected.type == Placeables::crystal) {
		
	}
	else if (currentlySelected.type == Placeables::floor) {
	
	}
	else if (currentlySelected.type == Placeables::door) {
	
	}
	else if (currentlySelected.type == Placeables::enemy) {

	}
	else if (currentlySelected.type == Placeables::finish) {
		if (mode == EditorMode::place && _finish != nullptr) {
			delete _finish;
		}
		_finish = currentlySelected.entity;
	}
}

void LevelEditor::GetPlaceable()
{
	if (currentPlaceable == Placeables::player) {
		Player* thePlayer = new Player(camera, 800.0f, 10.0f, 50.0f, 100, 100, ResourceManager::GetTexture("player")->GetId(), world);
		currentlySelected.entity = thePlayer;
		currentlySelected.type = Placeables::player;
		return;
	}
	else if (currentPlaceable == Placeables::wall) {
		B2Entity* _wall = new B2Entity(400, 750, ResourceManager::GetTexture("wall")->GetId(), world);
		currentlySelected.entity = _wall;
		currentlySelected.type = Placeables::wall;
	}
	else if (currentPlaceable == Placeables::mirror) {
		Mirror* _mirror = new Mirror(true, 45.0f, 240.0f, ResourceManager::GetTexture("mirror")->GetId(), world);
		currentlySelected.entity = _mirror;
		currentlySelected.type = Placeables::mirror;
	}
	else if (currentPlaceable == Placeables::crystal) {
		Crystal* _crystal = new Crystal(70, 70, ResourceManager::GetTexture("crystal")->GetId(), world);
		currentlySelected.entity = _crystal;
		currentlySelected.type = Placeables::crystal;
	}
	else if (currentPlaceable == Placeables::floor) {
		Sprite* _floor = new Sprite(200, 200, ResourceManager::GetTexture("floor")->GetId());
		currentlySelected.entity = _floor;
		currentlySelected.type = Placeables::floor;
	}
	else if (currentPlaceable == Placeables::door) {
		Door* _door = new Door(Direction::west, 550, 550, ResourceManager::GetTexture("door")->GetId(), world);
		currentlySelected.entity = _door;
		currentlySelected.type = Placeables::door;
	}
	else if (currentPlaceable == Placeables::enemy) {
		Enemy* _enemy = new Enemy(nullptr, 3000.0f, 0.6f, 0.5f, 300.0f, 6.0f, 150.0f, 70, 70, ResourceManager::GetTexture("enemy")->GetId(), world);
		currentlySelected.entity = _enemy;
		currentlySelected.type = Placeables::enemy;
	}
	else if (currentPlaceable == Placeables::finish) {
		Entity* theFinish = new Entity();
		currentlySelected.entity = theFinish;
		currentlySelected.type = Placeables::finish;
		return;
	}
	editorObjects.push_back(currentlySelected);
}

void LevelEditor::UpdateCurrentlySelected()
{
	if (currentlySelected.type == Placeables::player) {
		Player* _player = dynamic_cast<Player*>(currentlySelected.entity);
		_player->localAngle = glm::radians(inputPlayerRotation.output);
		//std::cout << "rotation player = " << glm::radians(inputPlayerRotation.output) << std::endl;
	}
	else if (currentlySelected.type == Placeables::wall) {
		B2Entity* _wall = dynamic_cast<B2Entity*>(currentlySelected.entity);
		_wall->SetWidth(inputWallWidth.output);
		_wall->localAngle = glm::radians(inputWallRotation.output);
	}
	else if (currentlySelected.type == Placeables::mirror) {
		Mirror* _mirror = dynamic_cast<Mirror*>(currentlySelected.entity);
		_mirror->localAngle = glm::radians(inputMirrorRotation.output);
		//_mirror->SetRotation(-90.0f);
	}
	else if (currentlySelected.type == Placeables::crystal) {
		Crystal* _crystal = dynamic_cast<Crystal*>(currentlySelected.entity);
		_crystal->localAngle = glm::radians(inputCrystalRotation.output);
	}
	else if (currentlySelected.type == Placeables::floor) {
		Sprite* _floor = dynamic_cast<Sprite*>(currentlySelected.entity);
		_floor->SetWidth(inputFloorWidth.output);
	}
	else if (currentlySelected.type == Placeables::door) {
		Door* _door = dynamic_cast<Door*>(currentlySelected.entity);
		_door->localAngle = glm::radians(inputDoorRotation.output);
	}
	else if (currentlySelected.type == Placeables::enemy) {
		Enemy* _enemy = dynamic_cast<Enemy*>(currentlySelected.entity);
		_enemy->localAngle = glm::radians(inputEnemyRotation.output);
	}
	else if (currentlySelected.type == Placeables::finish) {
		DebugRenderer::Line(currentlySelected.entity->localPosition + glm::vec2(inputFinishWidth.output / 2 * -1, inputFinishHeight.output / 2), currentlySelected.entity->localPosition + glm::vec2(inputFinishWidth.output / 2, inputFinishHeight.output / 2), glm::vec3(1, 0, 1));// Horizontal positive
		DebugRenderer::Line(currentlySelected.entity->localPosition + glm::vec2(inputFinishWidth.output / 2, inputFinishHeight.output / 2), currentlySelected.entity->localPosition + glm::vec2(inputFinishWidth.output / 2, inputFinishHeight.output / 2 * -1), glm::vec3(1, 0, 1));// Vertical positive
		DebugRenderer::Line(currentlySelected.entity->localPosition + glm::vec2(inputFinishWidth.output / 2 * -1, inputFinishHeight.output / 2 * -1), currentlySelected.entity->localPosition + glm::vec2(inputFinishWidth.output / 2, inputFinishHeight.output / 2 * -1), glm::vec3(1, 0, 1));// Horizontal negative
		DebugRenderer::Line(currentlySelected.entity->localPosition + glm::vec2(inputFinishWidth.output / 2 * -1, inputFinishHeight.output / 2), currentlySelected.entity->localPosition + glm::vec2(inputFinishWidth.output / 2 * -1, inputFinishHeight.output / 2 * -1), glm::vec3(1, 0, 1));// Vertical negative
	}
}

void LevelEditor::DeleteCurrentlySeleceted()
{
	if (currentlySelected.entity == nullptr) {
		return;
	}
	// Delete the editor object
	std::vector<EditorObject>::iterator itEditorObjects = editorObjects.begin();
	while (itEditorObjects != editorObjects.end()) {
		if ((*itEditorObjects).entity == currentlySelected.entity) {
			delete (*itEditorObjects).entity;
			itEditorObjects = editorObjects.erase(itEditorObjects);
			break;
		}
		else {
			++itEditorObjects;
		}
	}
	currentlySelected.entity = nullptr;
}

void LevelEditor::CreatePlaceablesTickbox(std::string text, glm::vec2 position)
{
	Tickbox* tb = new Tickbox(true, ResourceManager::GetTexture("tickboxNotActive")->GetId(), 25, 25, ResourceManager::GetTexture("tickboxActive")->GetId());
	tb->SetRenderer(RenderManager::GetSimpleRenderer("hud"));
	tb->localPosition = position;
	canvasEditor->AddChild(tb);
	tickboxes.push_back(tb);
	
	Text* t = new Text(text, ResourceManager::GetFont("fonts/arial.ttf", 256, 22), glm::vec3(1, 1, 1), Text::AlignmentX::centerX, Text::AlignmentY::bottomY);
	t->localPosition = glm::vec2(position.x, position.y + 25);
	canvasEditor->AddChild(t);
	tickboxesText.push_back(t);
}

void LevelEditor::CreateEditorModeTickbox(std::string text, glm::vec2 position)
{
	Tickbox* tb = new Tickbox(true, ResourceManager::GetTexture("tickboxNotActive")->GetId(), 25, 25, ResourceManager::GetTexture("tickboxActive")->GetId());
	tb->SetRenderer(RenderManager::GetSimpleRenderer("hud"));
	tb->localPosition = position;
	canvasEditor->AddChild(tb);
	tickboxesMode.push_back(tb);

	Text* t = new Text(text, ResourceManager::GetFont("fonts/arial.ttf", 256, 22), glm::vec3(1, 1, 1), Text::AlignmentX::centerX, Text::AlignmentY::bottomY);
	t->localPosition = glm::vec2(position.x, position.y + 25);
	canvasEditor->AddChild(t);
	tickboxesModeText.push_back(t);
}

InputFloat LevelEditor::CreateInputFloat(Sprite * canvas, std::string startValue, glm::vec2 position, std::string text)
{
	InputFloat inputFloat;
	inputFloat.text = new Text(text, ResourceManager::GetFont("fonts/arial.ttf", 512, 22), glm::vec3(1, 1, 1), Text::AlignmentX::centerX, Text::AlignmentY::centerY);
	inputFloat.text->localPosition = glm::vec2(position.x, position.y + 50);
	inputFloat.input = new Textinput(startValue, true, ResourceManager::GetFont("fonts/arial.ttf", 512, 22), glm::vec3(1, 1, 1), true, 100, 40, ResourceManager::GetTexture("textinput")->GetId());
	inputFloat.input->SetMaxLength(7);
	inputFloat.input->SetMaxDecimals(2);
	inputFloat.input->SetRenderer(RenderManager::GetSimpleRenderer("hud"));
	inputFloat.input->localPosition = position;
	inputFloat.output = 0.0f;

	canvas->AddChild(inputFloat.text);
	canvas->AddChild(inputFloat.input);

	return inputFloat;
}

Sprite * LevelEditor::CreateCanvasPlaceable()
{
	Sprite* canvas = new Sprite(400, 650, glm::vec4(0.0f, 0.5f, 0.5f, 0.5f));
	canvas->SetRenderer(RenderManager::GetSimpleRenderer("hud"));
	propertiesCanvas.push_back(canvas);
	return canvas;
}
