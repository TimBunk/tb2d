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

	properties = new Text("properties:", ResourceManager::GetFont("fonts/arial.ttf", 512, 48), glm::vec3(1,1,1), Text::AlignmentX::leftX, Text::AlignmentY::centerY);
	properties->localPosition = glm::vec2(properties->GetWidth() * -1 + 25, 515);
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

	CreateEditorModeTickbox("select", glm::vec2(-150, -260));
	CreateEditorModeTickbox("place", glm::vec2(-75, -260));
	CreateEditorModeTickbox("move", glm::vec2(0, -260));

	mode = EditorMode::select;
	tickboxesMode[0]->SetActive(true);

	// Player options
	playerCanvas = CreateCanvasPlaceable("player");
	inputPlayerRotation = CreateInputFloat(playerCanvas, "0", glm::vec2(-150, 250), "rotation");
	inputFloats.push_back(&inputPlayerRotation);
	_player = nullptr;
	// Wall options
	wallCanvas = CreateCanvasPlaceable("wall");
	inputWallWidth = CreateInputFloat(wallCanvas, "100", glm::vec2(-150, 250), "width");
	inputFloats.push_back(&inputWallWidth);
	inputWallRotation = CreateInputFloat(wallCanvas, "0", glm::vec2(0, 250), "rotation");
	inputFloats.push_back(&inputWallRotation);
	// Mirror options
	mirrorCanvas = CreateCanvasPlaceable("mirror");
	inputMirrorRotation = CreateInputFloat(mirrorCanvas, "0", glm::vec2(-150, 250), "rotation");
	inputFloats.push_back(&inputMirrorRotation);
	// Crystal options
	crystalCanvas = CreateCanvasPlaceable("crystal");
	inputCrystalRotation = CreateInputFloat(crystalCanvas, "0", glm::vec2(-150, 250), "rotation");
	inputFloats.push_back(&inputCrystalRotation);
	// Floor options
	floorCanvas = CreateCanvasPlaceable("floor");
	inputFloorWidth = CreateInputFloat(floorCanvas, "200", glm::vec2(-150, 250), "width");
	inputFloats.push_back(&inputFloorWidth);
	// Door options
	doorCanvas = CreateCanvasPlaceable("door");
	inputDoorRotation = CreateInputFloat(doorCanvas, "0", glm::vec2(-150, 250), "rotation");
	inputFloats.push_back(&inputDoorRotation);
	// Enemy options
	enemyCanvas = CreateCanvasPlaceable("enemy");
	inputEnemyRotation = CreateInputFloat(enemyCanvas, "0", glm::vec2(-150, 250), "rotation");
	inputFloats.push_back(&inputEnemyRotation);
	// Finish options
	finishCanvas = CreateCanvasPlaceable("finish");
	inputFinishWidth = CreateInputFloat(finishCanvas, "400", glm::vec2(-150, 250), "width");
	inputFloats.push_back(&inputFinishWidth);
	inputFinishHeight = CreateInputFloat(finishCanvas, "100", glm::vec2(0, 250), "height");
	inputFloats.push_back(&inputFinishHeight);
	_finish = nullptr;

	canvasObjects = new Entity();
	canvasObjects->localPosition = glm::vec2(0,-300);
	//canvasEditor->AddChild(canvasObjects);
	CreatePlaceablesTickbox("player", glm::vec2(-150, -40));
	CreatePlaceablesTickbox("wall", glm::vec2(-75, -40));
	CreatePlaceablesTickbox("mirror", glm::vec2(0, -40));
	CreatePlaceablesTickbox("crystal", glm::vec2(75, -40));
	CreatePlaceablesTickbox("floor", glm::vec2(150, -40));
	CreatePlaceablesTickbox("door", glm::vec2(-150, -115));
	CreatePlaceablesTickbox("enemy", glm::vec2(-75, -115));
	CreatePlaceablesTickbox("finish", glm::vec2(0, -115));

	canvasEditor->AddChild(playerCanvas);
	currentPlaceable = Placeables::player;
	currentlySelected.type = currentPlaceable;
	tickboxes[0]->SetActive(true);
}

LevelEditor::~LevelEditor()
{
	delete canvasObjects;
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
	// Delete the text of the textVector
	std::vector<Text*>::iterator itText = textVector.begin();
	while (itText != textVector.end()) {
		delete (*itText);
		itText = textVector.erase(itText);
	}
	// Delete the tickboxes for the modes
	std::vector<Tickbox*>::iterator itTickboxMode = tickboxesMode.begin();
	while (itTickboxMode != tickboxesMode.end()) {
		delete (*itTickboxMode);
		itTickboxMode = tickboxesMode.erase(itTickboxMode);
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
	//std::cout << "editorobjects size = " << editorObjects.size() << std::endl;
	//std::cout << "currentplaceable = " << currentPlaceable << std::endl;
	// DRAW
	for (int i = 0; i < editorObjects.size(); i++) {
		editorObjects[i].entity->Draw();
		editorObjects[i].entity->DrawChilderen(this);
	}
	if (currentlySelected.entity != nullptr && currentlySelected.type == Placeables::player) {
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
	UpdateTickboxes();
	UpdateInputFloats();
	UpdateCurrentlySelected();
	if (mode == EditorMode::place) {
		UpdatePlaceMode();
	}
	else {
		UpdateSelectMode();
	}

	/*if (saveButton->Down() && currentlySelected.entity == nullptr) {
		Save("level3.bin");
	}
	if (loadButton->Down() && currentlySelected.entity == nullptr) {
		level = levelLoader->LoadFromFile("level3.bin");
	}*/
}

void LevelEditor::UpdateSelectMode()
{
	//tickboxes[currentlySelected.type]->SetActive(true);
	if (Input::MousePress(0)) {
		b2Body* bodylist = world->GetBodyList();
		glm::vec2 _mousePos = Input::GetMousePositionWorldSpace();
		b2Vec2 mousePos = b2Vec2(_mousePos.x * B2Entity::p2m, _mousePos.y * B2Entity::p2m);

		while (bodylist != NULL) {
			if (bodylist->GetFixtureList()->TestPoint(mousePos)) {
				std::cout << "mouse hit" << std::endl;
				B2Entity* _selected = static_cast<B2Entity*>(bodylist->GetFixtureList()->GetUserData());
				if (_player == _selected) {
					if (currentlySelected.entity != nullptr) {
						Place();
					}
					currentlySelected.entity = _player;
					currentlySelected.type = Placeables::player;
					Select();
					return;
				}
				else if (_finish == _selected) {
					if (currentlySelected.entity != nullptr) {
						Place();
					}
					currentlySelected.entity = _finish;
					currentlySelected.type = Placeables::finish;
					Select();
					return;
				}
				for (int i = 0; i < editorObjects.size(); i++) {
					if (editorObjects[i].entity == _selected) {
						if (currentlySelected.entity != nullptr) {
							Place();
						}
						currentlySelected = editorObjects[i];
						Select();
						break;
					}
				}
			}
			bodylist = bodylist->GetNext();
		}
	}
	if (mode == EditorMode::move) {
		if (currentlySelected.entity != nullptr) {
			currentlySelected.entity->localPosition = Input::GetMousePositionWorldSpace();
			if (Input::MousePress(1)) {
				Place();
				currentlySelected.entity = nullptr;
			}
		}
	}
}

void LevelEditor::UpdatePlaceMode()
{
	if (currentlySelected.entity != nullptr && Input::MousePress(1)) {
		Place();
		currentlySelected.entity = nullptr;
	}
	else if (currentlySelected.entity != nullptr) {
		currentlySelected.entity->localPosition = Input::GetMousePositionWorldSpace();
	}
	if (currentlySelected.entity == nullptr) {
		GetPlaceable();
	}
}

void LevelEditor::UpdateTickboxes()
{
	// Update the tickboxes
	for (int i = 0; i < tickboxes.size(); i++) {
		if (i == currentPlaceable) {
			tickboxes[i]->SetActive(true);
		}
		if (tickboxes[i]->IsActive() && i != currentPlaceable) {
			if (mode == EditorMode::place) {
				DeleteCurrentlySeleceted();
			}
			/*else if (currentlySelected.entity != nullptr) {
				Place();
			}*/
			tickboxes[currentPlaceable]->SetActive(false);
			canvasEditor->RemoveChild(propertiesCanvas[currentPlaceable]);
			currentPlaceable = static_cast<Placeables>(i);
			canvasEditor->AddChild(propertiesCanvas[currentPlaceable]);
		}
	}
	// Update the tickboxes of the modes
	for (int i = 0; i < tickboxesMode.size(); i++) {
		if (i == mode) {
			tickboxesMode[i]->SetActive(true);
		}
		if (tickboxesMode[i]->IsActive() && i != mode) {
			if (mode == EditorMode::select) {
				if (currentlySelected.entity != nullptr) {
					Place();
					currentlySelected.entity = nullptr;
				}
			}
			if (mode != EditorMode::select) {
				DeleteCurrentlySeleceted();
			}
			tickboxesMode[mode]->SetActive(false);
			if (mode == EditorMode::place) {
				canvasEditor->RemoveChild(canvasObjects);
			}
			else if (mode != EditorMode::place && static_cast<EditorMode>(i) == EditorMode::place) {
				canvasEditor->AddChild(canvasObjects);
			}
			mode = static_cast<EditorMode>(i);
		}
	}
}

void LevelEditor::UpdateInputFloats()
{
	for (int i = 0; i < inputFloats.size(); i++) {
		inputFloats[i]->output = inputFloats[i]->input->GetFloat();
	}
}

void LevelEditor::Place()
{
	if (currentlySelected.type == Placeables::player) {
		if (mode == EditorMode::place && _player != nullptr && _player != currentlySelected.entity) {
			delete _player;
		}
		_player = dynamic_cast<Player*>(currentlySelected.entity);
		_player->SetColor(glm::vec4(0,0,0,0));
		_player->CreateCircleCollider(40.0f, true, false);
	}
	else if (currentlySelected.type == Placeables::wall) {
		B2Entity* _wall = dynamic_cast<B2Entity*>(currentlySelected.entity);
		_wall->SetColor(glm::vec4(0, 0, 0, 0));
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
		if (mode == EditorMode::place && _finish != nullptr && _finish != currentlySelected.entity) {
			delete _finish;
		}
		_finish = currentlySelected.entity;
	}
}

void LevelEditor::Select()
{
	if (currentlySelected.type == Placeables::player) {
		_player = dynamic_cast<Player*>(currentlySelected.entity);
		_player->SetColor(glm::vec4(0, 0.5f, 1, 0.5f));
	}
	else if (currentlySelected.type == Placeables::wall) {
		B2Entity* _wall = dynamic_cast<B2Entity*>(currentlySelected.entity);
		_wall->SetColor(glm::vec4(0, 0.5f, 1, 0.5f));
		std::string s = std::to_string(_wall->GetWidth());
		inputWallWidth.input->SetText(s);
		s = std::to_string((int)glm::degrees(_wall->localAngle));
		inputWallRotation.input->SetText(s);
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

	}
	tickboxes[currentlySelected.type]->SetActive(true);
	//currentPlaceable = currentlySelected.type;
}

void LevelEditor::GetPlaceable()
{
	if (currentPlaceable == Placeables::player) {
		Player* thePlayer = new Player(camera, 800.0f, 10.0f, 50.0f, 100, 100, ResourceManager::GetTexture("player")->GetId(), world);
		thePlayer->SetColor(glm::vec4(0, 0.5f, 1, 0.5f));
		currentlySelected.entity = thePlayer;
		currentlySelected.type = Placeables::player;
		return;
	}
	else if (currentPlaceable == Placeables::wall) {
		B2Entity* _wall = new B2Entity(400, 750, ResourceManager::GetTexture("wall")->GetId(), world);
		_wall->SetColor(glm::vec4(0, 0.5f, 1, 0.5f));
		currentlySelected.entity = _wall;
		currentlySelected.type = Placeables::wall;
	}
	else if (currentPlaceable == Placeables::mirror) {
		Mirror* _mirror = new Mirror(true, 45.0f, 240.0f, ResourceManager::GetTexture("mirror")->GetId(), world);
		_mirror->SetColor(glm::vec4(0, 0.5f, 1, 0.5f));
		currentlySelected.entity = _mirror;
		currentlySelected.type = Placeables::mirror;
	}
	else if (currentPlaceable == Placeables::crystal) {
		Crystal* _crystal = new Crystal(70, 70, ResourceManager::GetTexture("crystal")->GetId(), world);
		_crystal->SetColor(glm::vec4(0, 0.5f, 1, 0.5f));
		currentlySelected.entity = _crystal;
		currentlySelected.type = Placeables::crystal;
	}
	else if (currentPlaceable == Placeables::floor) {
		Sprite* _floor = new Sprite(200, 200, ResourceManager::GetTexture("floor")->GetId());
		_floor->SetColor(glm::vec4(0, 0.5f, 1, 0.5f));
		currentlySelected.entity = _floor;
		currentlySelected.type = Placeables::floor;
	}
	else if (currentPlaceable == Placeables::door) {
		Door* _door = new Door(Direction::west, 550, 550, ResourceManager::GetTexture("door")->GetId(), world);
		_door->SetColor(glm::vec4(0, 0.5f, 1, 0.5f));
		currentlySelected.entity = _door;
		currentlySelected.type = Placeables::door;
	}
	else if (currentPlaceable == Placeables::enemy) {
		Enemy* _enemy = new Enemy(nullptr, 3000.0f, 0.6f, 0.5f, 300.0f, 6.0f, 150.0f, 70, 70, ResourceManager::GetTexture("enemy")->GetId(), world);
		_enemy->SetColor(glm::vec4(0, 0.5f, 1, 0.5f));
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
	if (currentlySelected.entity == nullptr) { return; }
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

void LevelEditor::CreatePlaceablesTickbox(std::string text, glm::vec2 position)
{
	Tickbox* tb = new Tickbox(true, ResourceManager::GetTexture("tickboxNotActive")->GetId(), 25, 25, ResourceManager::GetTexture("tickboxActive")->GetId());
	tb->SetRenderer(RenderManager::GetSimpleRenderer("hud"));
	tb->localPosition = position;
	//canvasEditor->AddChild(tb);
	tickboxes.push_back(tb);
	canvasObjects->AddChild(tb);
	
	Text* t = new Text(text, ResourceManager::GetFont("fonts/arial.ttf", 256, 22), glm::vec3(1, 1, 1), Text::AlignmentX::centerX, Text::AlignmentY::bottomY);
	t->localPosition = glm::vec2(position.x, position.y + 25);
	//canvasEditor->AddChild(t);
	textVector.push_back(t);
	canvasObjects->AddChild(t);
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
	textVector.push_back(t);
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

Sprite * LevelEditor::CreateCanvasPlaceable(std::string name)
{
	Sprite* canvas = new Sprite(400, 650, glm::vec4(0.0f, 0.5f, 0.5f, 0.5f));
	canvas->localPosition.y = 140;
	canvas->SetRenderer(RenderManager::GetSimpleRenderer("hud"));
	propertiesCanvas.push_back(canvas);

	Text* t = new Text(name, ResourceManager::GetFont("fonts/arial.ttf", 512, 44), glm::vec3(1, 1, 1), Text::AlignmentX::leftX, Text::AlignmentY::centerY);
	t->localPosition.x = 35;
	t->localPosition.y = 375;
	textVector.push_back(t);
	canvas->AddChild(t);

	return canvas;
}
