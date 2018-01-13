#include "leveleditor.h"

LevelEditor::LevelEditor(int screenWidthCamera, int screenHeightCamera) : Scene::Scene(screenWidthCamera, screenHeightCamera)
{
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

	nameReceiver = new Textinput("", false, ResourceManager::GetFont("fonts/arial.ttf", 512, 48), glm::vec3(1, 1, 1), true, 550, 100, glm::vec4(0, 0, 0, 1));
	nameReceiver->SetRenderer(RenderManager::GetSimpleRenderer("hud"));
	nameReceiverText = new Text("Type the name of the file here", ResourceManager::GetFont("fonts/arial.ttf", 512, 48), glm::vec3(1, 1, 1), Text::AlignmentX::centerX, Text::AlignmentY::bottomY);
	nameReceiverText->localPosition.y = 60;
	textVector.push_back(nameReceiverText);

	saveButton = new Button(400/3, 75, 0, true, camera);
	saveButton->SetColor(glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));
	saveButton->CreateText("save", ResourceManager::GetFont("fonts/arial.ttf", 512, 48), glm::vec3(1, 1, 1));
	saveButton->localPosition = glm::vec2(-200 + saveButton->GetWidth()/2 * 1, -540 + 75 / 2);
	saveButton->SetRenderer(RenderManager::GetSimpleRenderer("hud"));
	canvasEditor->AddChild(saveButton);

	warning = new Button(550, 100, 0, true, camera);
	warning->SetColor(glm::vec4(0.8f, 0, 0, 1));
	warning->CreateText("", ResourceManager::GetFont("fonts/arial.ttf", 512, 22), glm::vec3(1, 1, 1));
	warning->SetRenderer(RenderManager::GetSimpleRenderer("hud"));
	warningState = false;

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
	CreateInputFloat(inputPlayerRotation, playerCanvas, "0", glm::vec2(-150, 250), "rotation");
	CreateInputFloat(inputPlayerHealth, playerCanvas, "800", glm::vec2(0, 250), "health");
	CreateInputFloat(inputPlayerDamage, playerCanvas, "10", glm::vec2(-150, 150), "damage");
	CreateInputFloat(inputPlayerSpeed, playerCanvas, "50", glm::vec2(0, 150), "speed");
	_player = nullptr;
	// Wall options
	wallCanvas = CreateCanvasPlaceable("wall");
	CreateInputFloat(inputWallWidth, wallCanvas, "720", glm::vec2(-150, 250), "width");
	CreateInputFloat(inputWallRotation, wallCanvas, "0", glm::vec2(0, 250), "rotation");
	// Mirror options
	mirrorCanvas = CreateCanvasPlaceable("mirror");
	CreateInputFloat(inputMirrorRotation, mirrorCanvas, "0", glm::vec2(-150, 250), "rotation");
	inputMirrorRotator = CreateTickbox(mirrorCanvas, true, glm::vec2(0, 250), "rotator");
	// Crystal options
	crystalCanvas = CreateCanvasPlaceable("crystal");
	CreateInputFloat(inputCrystalRotation, crystalCanvas, "0", glm::vec2(-150, 250), "rotation");
	// Floor options
	floorCanvas = CreateCanvasPlaceable("floor");
	CreateInputFloat(inputFloorRotation, floorCanvas, "0", glm::vec2(-150, 250), "rotation");
	CreateInputFloat(inputFloorWidth, floorCanvas, "200", glm::vec2(0, 250), "width");
	CreateInputFloat(inputFloorHeight, floorCanvas, "200", glm::vec2(-150, 150), "height");
	// Door options
	doorCanvas = CreateCanvasPlaceable("door");
	CreateInputFloat(inputDoorRotation, doorCanvas, "0", glm::vec2(-150, 250), "rotation");
	inputDoorLink = CreateTickbox(doorCanvas, false, glm::vec2(0, 250), "link");
	// Enemy options
	enemyCanvas = CreateCanvasPlaceable("enemy");
	CreateInputFloat(inputEnemyRotation, enemyCanvas, "0", glm::vec2(-150, 250), "rotation");
	CreateInputFloat(inputEnemyHealth, enemyCanvas, "300", glm::vec2(0, 250), "health");
	CreateInputFloat(inputEnemyDamage, enemyCanvas, "6", glm::vec2(-150, 150), "speed");
	CreateInputFloat(inputEnemySpeed, enemyCanvas, "150", glm::vec2(0, 150), "damage");
	CreateInputFloat(inputEnemyLOS, enemyCanvas, "3000", glm::vec2(-150, 50), "line of sight");
	// Finish options
	finishCanvas = CreateCanvasPlaceable("finish");
	CreateInputFloat(inputFinishRotation, finishCanvas, "0", glm::vec2(-150, 250), "rotation");
	CreateInputFloat(inputFinishWidth, finishCanvas, "400", glm::vec2(0, 250), "width");
	CreateInputFloat(inputFinishHeight, finishCanvas, "100", glm::vec2(-150, 150), "height");
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

	menu = false;
	saving = false;
	loading = false;
	
	remove = new Button(400 / 3, 75, 0, true, camera);
	remove->SetRenderer(RenderManager::GetSimpleRenderer("hud"));
	remove->CreateText("Remove", ResourceManager::GetFont("fonts/arial.ttf", 512, 22), glm::vec3(1, 1, 1));
	remove->SetColor(glm::vec4(1, 0, 0, 1));
	remove->localPosition.y = -375;
	canvasEditor->AddChild(remove);

	crystalID = 0;
	linking = false;
}

LevelEditor::~LevelEditor()
{
	ClearScene();
	delete canvasObjects;
	delete textfile;
	delete saveButton;
	delete nameReceiver;
	delete warning;
	delete loadButton;
	delete menuButton;

	delete canvasEditor;
	delete properties;
	// Delete the tickboxeseditorobjects
	std::vector<Tickbox*>::iterator itTickboxes = editorObjectsTickBoxes.begin();
	while (itTickboxes != editorObjectsTickBoxes.end()) {
		delete (*itTickboxes);
		itTickboxes = editorObjectsTickBoxes.erase(itTickboxes);
	}
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

	delete world;
}

void LevelEditor::Update(double deltaTime)
{
	// Move the camera using the middle mouse button
	if (Input::MouseDown(GLFW_MOUSE_BUTTON_3)) {
		glm::vec2 mousePos = Input::GetMousePositionScreenSpace();
		mousePos *= deltaTime;
		camera->PositionAdd(mousePos);
	}
	else {
		// Move the camera using the arrow keys
		if (Input::KeyDown(GLFW_KEY_LEFT)) {
			camera->PositionAdd(glm::vec2(-200.0f * deltaTime, 0.0f));
		}
		if (Input::KeyDown(GLFW_KEY_UP)) {
			camera->PositionAdd(glm::vec2(0.0f, 200.0f * deltaTime));
		}
		if (Input::KeyDown(GLFW_KEY_RIGHT)) {
			camera->PositionAdd(glm::vec2(200.0f * deltaTime, 0.0f));
		}
		if (Input::KeyDown(GLFW_KEY_DOWN)) {
			camera->PositionAdd(glm::vec2(0.0f, -200.0f * deltaTime));
		}
	}

	// DRAW
	for (int i = 0; i < links.size(); i++) {
		for (int j = 0; j < links[i].crystals.size(); j++) {
			DebugRenderer::Line(links[i].door->GetGlobalPosition(), links[i].crystals[j]->GetGlobalPosition(), glm::vec3(1, 0, 0));
		}
	}
	for (int i = 0; i < floors.size(); i++) {
		floors[i]->Draw();
		floors[i]->DrawChilderen(this);
	}
	for (int i = 0; i < editorObjects.size(); i++) {
		editorObjects[i].entity->Draw();
		editorObjects[i].entity->DrawChilderen(this);
	}
	if (currentlySelected.entity != nullptr) {// && currentlySelected.type == Placeables::player || currentlySelected.type == Placeables::finish) {
		currentlySelected.entity->Draw();
		currentlySelected.entity->DrawChilderen(this);
	}
	if (_finish != nullptr) {
		_finish->Draw();
		_finish->DrawChilderen(this);
	}
	if (_player != nullptr) {
		_player->Draw();
		_player->DrawChilderen(this);
	}
	// END OF DRAWING
	// If saving or loading wait for the user to enter a name to load or save to
	if (saving || loading) {
		if (nameReceiver->IsActive() == false) {
			if (nameReceiver->GetString().size() == 0) {
				nameReceiver->SetActive(true);
			}
			else {
				RemoveChild(nameReceiver);
				RemoveChild(nameReceiverText);
				if (saving) {
					saving = false;
					Save();
				}
				else {
					loading = false;
					Load();
				}
			}
		}

		return;
	}


	UpdateTickboxes();
	UpdateInputFloats();
	UpdateCurrentlySelected();
	if (linking) { return; }

	if (mode == EditorMode::place) {
		UpdatePlaceMode();
	}
	else {
		UpdateSelectMode();
	}

	if (saveButton->Down()) {
		Save();
	}
	if (warning->Down()) {
		warning->Update(deltaTime);
		RemoveChild(warning);
		warningState = false;
	}
	if (loadButton->Down()) {
		//level = levelLoader->LoadFromFile("level3.bin");
		Load();
	}
	if (menuButton->Down()) {
		menu = true;
	}
	if (remove->Down()) {
		DeleteCurrentlySeleceted();
	}
}

void LevelEditor::UpdateSelectMode()
{
	//tickboxes[currentlySelected.type]->SetActive(true);
	if (Input::MousePress(0) && Input::GetMousePositionScreenSpace().x > -560) {
		b2Body* bodylist = world->GetBodyList();
		glm::vec2 _mousePos = Input::GetMousePositionWorldSpace();
		b2Vec2 mousePos = b2Vec2(_mousePos.x * B2Entity::p2m, _mousePos.y * B2Entity::p2m);

		while (bodylist != NULL) {
			if (bodylist->GetFixtureList()->TestPoint(mousePos)) {
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
						return;
					}
				}
				for (int i = 0; i < floors.size(); i++) {
					if (floors[i] == _selected) {
						if (currentlySelected.entity != nullptr) {
							Place();
						}
						currentlySelected.entity = floors[i];
						currentlySelected.type = Placeables::floor;
						Select();
						continue;
					}
				}
			}
			bodylist = bodylist->GetNext();
		}
	}

	if (currentlySelected.entity != nullptr) {
		if (mode == EditorMode::move) {
			currentlySelected.entity->localPosition = Input::GetMousePositionWorldSpace();
		}
		if (Input::MousePress(1)) {
			Place();
			currentlySelected.entity = nullptr;
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
				canvasEditor->AddChild(remove);
			}
			else if (mode != EditorMode::place && static_cast<EditorMode>(i) == EditorMode::place) {
				canvasEditor->AddChild(canvasObjects);
				canvasEditor->RemoveChild(remove);
			}
			mode = static_cast<EditorMode>(i);
		}
	}
}

void LevelEditor::UpdateInputFloats()
{
	for (int i = 0; i < inputFloats.size(); i++) {
		inputFloats[i]->output = inputFloats[i]->input->GetFloat();
		if (inputFloats[i]->input->IsActive()) {
			inputFloats[i]->input->SetColor(glm::vec4(0.5f, 0.5f, 0.5f, 1.0f));
		}
		else {
			inputFloats[i]->input->SetColor(glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));
		}
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
		Mirror* _mirror = dynamic_cast<Mirror*>(currentlySelected.entity);
		_mirror->SetColor(glm::vec4(0, 0, 0, 0));
		_mirror->CreateBoxCollider(100.0f, 110.0f, glm::vec2(0.15f, 0.0f), false, false);
	}
	else if (currentlySelected.type == Placeables::crystal) {
		Crystal* _crystal = dynamic_cast<Crystal*>(currentlySelected.entity);
		_crystal->SetColor(glm::vec4(0, 0, 0, 0));
		_crystal->CreateBoxCollider(70, 70, glm::vec2(0.0f, 0.0f), false, false);
	}
	else if (currentlySelected.type == Placeables::floor) {
		B2Entity* _floor = dynamic_cast<B2Entity*>(currentlySelected.entity);
		_floor->SetColor(glm::vec4(0, 0, 0, 0));
		_floor->CreateBoxCollider(_floor->GetWidth(), _floor->GetHeight(), glm::vec2(0, 0), true, true);
	}
	else if (currentlySelected.type == Placeables::door) {
		Door* _door = dynamic_cast<Door*>(currentlySelected.entity);
		_door->SetColor(glm::vec4(0, 0, 0, 0));
		_door->CreateBoxCollider(550, 100, glm::vec2(0, 0), false, false);
	}
	else if (currentlySelected.type == Placeables::enemy) {
		Enemy* _enemy = dynamic_cast<Enemy*>(currentlySelected.entity);
		_enemy->SetColor(glm::vec4(0, 0, 0, 0));
		_enemy->CreateBoxCollider(70, 70, glm::vec2(0, 0), true, false);
	}
	else if (currentlySelected.type == Placeables::finish) {
		if (mode == EditorMode::place && _finish != nullptr && _finish != currentlySelected.entity) {
			delete _finish;
		}
		_finish = dynamic_cast<B2Entity*>(currentlySelected.entity);
		_finish->SetColor(glm::vec4(1,0,1,0.5f));
		_finish->CreateBoxCollider(_finish->GetWidth(), _finish->GetHeight(), glm::vec2(0, 0), true, true);
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
		Mirror* _mirror = dynamic_cast<Mirror*>(currentlySelected.entity);
		_mirror->SetColor(glm::vec4(0, 0.5f, 1, 0.5f));
		std::string s = std::to_string((int)glm::degrees(_mirror->localAngle));
		inputMirrorRotation.input->SetText(s);
		inputMirrorRotator->SetActive(_mirror->IsRotatable());
	}
	else if (currentlySelected.type == Placeables::crystal) {
		Crystal* _crystal = dynamic_cast<Crystal*>(currentlySelected.entity);
		_crystal->SetColor(glm::vec4(0, 0.5f, 1, 0.5f));
		std::string s = std::to_string((int)glm::degrees(_crystal->localAngle));
		inputCrystalRotation.input->SetText(s);
	}
	else if (currentlySelected.type == Placeables::floor) {
		B2Entity* _floor = dynamic_cast<B2Entity*>(currentlySelected.entity);
		_floor->SetColor(glm::vec4(0, 0.5f, 1, 0.5f));
		std::string s = std::to_string((int)glm::degrees(_floor->localAngle));
		inputFloorRotation.input->SetText(s);
		s = std::to_string((int)_floor->GetWidth());
		inputFloorWidth.input->SetText(s);
		s = std::to_string((int)_floor->GetHeight());
		inputFloorHeight.input->SetText(s);
	}
	else if (currentlySelected.type == Placeables::door) {
		Door* _door = dynamic_cast<Door*>(currentlySelected.entity);
		_door->SetColor(glm::vec4(0, 0.5f, 1, 0.5f));
		std::string s = std::to_string((int)glm::degrees(_door->localAngle));
		inputDoorRotation.input->SetText(s);
	}
	else if (currentlySelected.type == Placeables::enemy) {
		Enemy* _enemy = dynamic_cast<Enemy*>(currentlySelected.entity);
		_enemy->SetColor(glm::vec4(0, 0.5f, 1, 0.5f));
		std::string s = std::to_string((int)glm::degrees(_enemy->localAngle));
		inputEnemyRotation.input->SetText(s);
		s = std::to_string((int)_enemy->GetMaxHealth());
		inputEnemyHealth.input->SetText(s);
		s = std::to_string((int)_enemy->GetDamage());
		inputEnemyDamage.input->SetText(s);
		s = std::to_string((int)_enemy->GetSpeed());
		inputEnemySpeed.input->SetText(s);
		s = std::to_string((int)_enemy->GetLineOfSight());
		inputEnemyLOS.input->SetText(s);
	}
	else if (currentlySelected.type == Placeables::finish) {
		_finish = dynamic_cast<B2Entity*>(currentlySelected.entity);
		_finish->SetColor(glm::vec4(0, 0.5f, 1, 0.5f));
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
		B2Entity* _wall = new B2Entity(720, 750, ResourceManager::GetTexture("wall")->GetId(), world);
		_wall->SetColor(glm::vec4(0, 0.5f, 1, 0.5f));
		currentlySelected.entity = _wall;
		currentlySelected.type = Placeables::wall;
	}
	else if (currentPlaceable == Placeables::mirror) {
		Mirror* _mirror = new Mirror(true, 150.0f, 150.0f, ResourceManager::GetTexture("mirror")->GetId(), world);
		_mirror->SetColor(glm::vec4(0, 0.5f, 1, 0.5f));
		currentlySelected.entity = _mirror;
		currentlySelected.type = Placeables::mirror;
	}
	else if (currentPlaceable == Placeables::crystal) {
		crystalID++;
		Crystal* _crystal = new Crystal(crystalID, 70, 70, ResourceManager::GetTexture("crystal")->GetId(), world);
		_crystal->SetColor(glm::vec4(0, 0.5f, 1, 0.5f));
		currentlySelected.entity = _crystal;
		currentlySelected.type = Placeables::crystal;
	}
	else if (currentPlaceable == Placeables::floor) {
		B2Entity* _floor = new B2Entity(200, 200, ResourceManager::GetTexture("floor")->GetId(), world);
		_floor->SetColor(glm::vec4(0, 0.5f, 1, 0.5f));
		currentlySelected.entity = _floor;
		currentlySelected.type = Placeables::floor;
		floors.push_back(_floor);
		return;
	}
	else if (currentPlaceable == Placeables::door) {
		Door* _door = new Door(550, 550, ResourceManager::GetTexture("door")->GetId(), world);
		_door->SetColor(glm::vec4(0, 0.5f, 1, 0.5f));
		currentlySelected.entity = _door;
		currentlySelected.type = Placeables::door;
		Link link;
		link.door = _door;
		links.push_back(link);
	}
	else if (currentPlaceable == Placeables::enemy) {
		Enemy* _enemy = new Enemy(nullptr, 3000.0f, 0.6f, 0.5f, 300.0f, 6.0f, 150.0f, 70, 70, ResourceManager::GetTexture("enemy")->GetId(), world);
		_enemy->SetColor(glm::vec4(0, 0.5f, 1, 0.5f));
		currentlySelected.entity = _enemy;
		currentlySelected.type = Placeables::enemy;
	}
	else if (currentPlaceable == Placeables::finish) {
		B2Entity* theFinish = new B2Entity(400, 100, 0, world);
		theFinish->SetColor(glm::vec4(0, 0.5f, 1, 0.5f));
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
		_player->SetMaxHealth(inputPlayerHealth.output);
		_player->SetDamage(inputPlayerDamage.output);
		_player->SetSpeed(inputPlayerSpeed.output);
	}
	else if (currentlySelected.type == Placeables::wall) {
		B2Entity* _wall = dynamic_cast<B2Entity*>(currentlySelected.entity);
		_wall->SetWidth(inputWallWidth.output);
		_wall->SetRepeatableUV(glm::vec2(_wall->GetWidth() / 720.0f, _wall->GetHeight() / 750.0f));
		_wall->localAngle = glm::radians(inputWallRotation.output);
	}
	else if (currentlySelected.type == Placeables::mirror) {
		Mirror* _mirror = dynamic_cast<Mirror*>(currentlySelected.entity);
		_mirror->localAngle = glm::radians(inputMirrorRotation.output);
		if (_mirror->IsRotatable() != inputMirrorRotator->IsActive()) {
			_mirror->Rotatable(inputMirrorRotator->IsActive());
		}
	}
	else if (currentlySelected.type == Placeables::crystal) {
		Crystal* _crystal = dynamic_cast<Crystal*>(currentlySelected.entity);
		_crystal->localAngle = glm::radians(inputCrystalRotation.output);
	}
	else if (currentlySelected.type == Placeables::floor) {
		Sprite* _floor = dynamic_cast<Sprite*>(currentlySelected.entity);
		_floor->localAngle = glm::radians(inputFloorRotation.output);
		_floor->SetWidth(inputFloorWidth.output);
		_floor->SetHeight(inputFloorHeight.output);
		_floor->SetRepeatableUV(glm::vec2(_floor->GetWidth() / 200.0f, _floor->GetHeight() / 200.0f));
	}
	else if (currentlySelected.type == Placeables::door) {
		Door* _door = dynamic_cast<Door*>(currentlySelected.entity);
		_door->localAngle = glm::radians(inputDoorRotation.output);
		if (inputDoorLink->IsActive() && linking == false && mode == EditorMode::select) {
			linking = true;
			RemoveChild(canvasEditor);
		}
		else if (linking) {
			if (Input::MousePress(0)) {
				b2Body* bodylist = world->GetBodyList();
				glm::vec2 _mousePos = Input::GetMousePositionWorldSpace();
				b2Vec2 mousePos = b2Vec2(_mousePos.x * B2Entity::p2m, _mousePos.y * B2Entity::p2m);

				while (bodylist != NULL) {
					if (bodylist->GetFixtureList()->TestPoint(mousePos)) {
						B2Entity* _selected = static_cast<B2Entity*>(bodylist->GetFixtureList()->GetUserData());
						for (int i = 0; i < editorObjects.size(); i++) {
							// Look if the selected type is a crystal
							if (editorObjects[i].entity == _selected && editorObjects[i].type == Placeables::crystal) {
								for (int j = 0; j < links.size(); j++) {
									// Look for the correct link
									if (links[j].door == currentlySelected.entity) {
										// Link the crystal with the door
										links[j].crystals.push_back(dynamic_cast<Crystal*>(editorObjects[i].entity));
										inputDoorLink->SetActive(false);
										AddChild(canvasEditor);
										linking = false;
									}
								}
							}
						}
					}
					bodylist = bodylist->GetNext();
				}
			}
			else if (Input::MousePress(1)) {
				inputDoorLink->SetActive(false);
				AddChild(canvasEditor);
				linking = false;
			}
		}
		else if (inputDoorLink->IsActive()) {
			inputDoorLink->SetActive(false);
			if (warningState == false) {
				AddChild(warning);
				warning->SetText("Linking can only be done in select mode");
				warningState = true;
			}
		}
	}
	else if (currentlySelected.type == Placeables::enemy) {
		Enemy* _enemy = dynamic_cast<Enemy*>(currentlySelected.entity);
		_enemy->localAngle = glm::radians(inputEnemyRotation.output);
		_enemy->SetMaxHealth(inputEnemyHealth.output);
		_enemy->SetDamage(inputEnemyDamage.output);
		_enemy->SetSpeed(inputEnemySpeed.output);
		_enemy->SetLineOfSight(inputEnemyLOS.output);
	}
	else if (currentlySelected.type == Placeables::finish) {
		B2Entity* _finish = dynamic_cast<B2Entity*>(currentlySelected.entity);
		_finish->localAngle = glm::radians(inputFinishRotation.output);
		_finish->SetWidth(inputFinishWidth.output);
		_finish->SetHeight(inputFinishHeight.output);
	}
}

void LevelEditor::DeleteCurrentlySeleceted()
{
	if (currentlySelected.entity == nullptr) {
		return;
	}
	if (currentlySelected.entity == _player) {
		delete _player;
		_player = nullptr;
	}
	else if (currentlySelected.entity == _finish) {
		delete _finish;
		_finish = nullptr;
	}
	// Delete the floor object
	if (currentlySelected.type == Placeables::floor) {
		std::vector<B2Entity*>::iterator itFloor = floors.begin();
		while (itFloor != floors.end()) {
			if ((*itFloor) == currentlySelected.entity) {
				delete (*itFloor);
				floors.erase(itFloor);
				break;
			}
			else {
				++itFloor;
			}
		}
		currentlySelected.entity = nullptr;
	}
	else {
		// Delete the editor object
		std::vector<EditorObject>::iterator itEditorObjects = editorObjects.begin();
		while (itEditorObjects != editorObjects.end()) {
			if ((*itEditorObjects).entity == currentlySelected.entity) {
				// If it is a door remove the link from that door
				if ((*itEditorObjects).type == Placeables::door) {
					std::vector<Link>::iterator itDoors = links.begin();
					while (itDoors != links.end()) {
						if ((*itDoors).door == currentlySelected.entity) {
							links.erase(itDoors);
							break;
						}
						else {
							++itDoors;
						}
					}
				}
				// If it is a crystal remove the link to that crystal if that link exists
				else if ((*itEditorObjects).type == Placeables::crystal) {
					std::vector<Link>::iterator itDoors = links.begin();
					while (itDoors != links.end()) {
						std::vector<Crystal*>::iterator itCrystals = (*itDoors).crystals.begin();
						while (itCrystals != (*itDoors).crystals.end()) {
							if (*itCrystals == currentlySelected.entity) {
								(*itDoors).crystals.erase(itCrystals);
								break;
							}
							else {
								++itCrystals;
							}
						}
						++itDoors;
					}
				}
				// Delete the currently selected
				delete (*itEditorObjects).entity;
				editorObjects.erase(itEditorObjects);
				break;
			}
			else {
				++itEditorObjects;
			}
		}
		currentlySelected.entity = nullptr;
		currentlySelected.type = Placeables::wall;
	}
}

void LevelEditor::Save()
{
	if (loading || warningState) { return; }
	if (_player == nullptr || _finish == nullptr) {
		if (warningState == false) {
			warning->SetText("You need atleast a player and a finish to save");
			AddChild(warning);
			warningState = true;
		}
		return;
	}
	if (saving == false || nameReceiver->GetString().size() > 0) {
		if (nameReceiver->GetString().size() == 0) {
			saving = true;
			AddChild(nameReceiverText);
			AddChild(nameReceiver);
			return;
		}
	}
	else {
		return;
	}
	if (mode != EditorMode::select) {
		DeleteCurrentlySeleceted();
	}
	std::cout << "save!" << std::endl;
	nameReceiver->SetText("levels/" + nameReceiver->GetString() + ".LEVEL");
	char *_levelName = new char[nameReceiver->GetString().length() + 1];
	strcpy(_levelName, nameReceiver->GetString().c_str());
	textfile->Create(_levelName);
	delete[] _levelName;
	nameReceiver->SetText("");

	for (int i = 0; i < floors.size(); i++) {
		std::string data = "floor ";
		data += std::to_string(floors[i]->localPosition.x) + " ";
		data += std::to_string(floors[i]->localPosition.y) + " ";
		data += std::to_string(floors[i]->localAngle) + " ";
		data += std::to_string(floors[i]->GetWidth()) + " ";
		data += std::to_string(floors[i]->GetHeight()) + " ";
		textfile->Write(data);
	}
	for (int i = 0; i < editorObjects.size(); i++) {
		std::string data = "";
		if (editorObjects[i].type == Placeables::wall) {
			B2Entity* _wall = dynamic_cast<B2Entity*>(editorObjects[i].entity);
			data += "wall ";
			data += std::to_string(_wall->localPosition.x) + " ";
			data += std::to_string(_wall->localPosition.y) + " ";
			data += std::to_string(_wall->localAngle) + " ";
			data += std::to_string(_wall->GetWidth()) + " ";
		}
		else if (editorObjects[i].type == Placeables::mirror) {
			Mirror* _mirror = dynamic_cast<Mirror*>(editorObjects[i].entity);
			data += "mirror ";
			data += std::to_string(_mirror->localPosition.x) + " ";
			data += std::to_string(_mirror->localPosition.y) + " ";
			data += std::to_string(_mirror->localAngle) + " ";
			data += std::to_string(_mirror->IsRotatable()) + " ";
		}
		else if (editorObjects[i].type == Placeables::crystal) {
			Crystal* _crystal = dynamic_cast<Crystal*>(editorObjects[i].entity);
			data += "crystal ";
			data += std::to_string(_crystal->localPosition.x) + " ";
			data += std::to_string(_crystal->localPosition.y) + " ";
			data += std::to_string(_crystal->localAngle) + " ";
			data += std::to_string(_crystal->GetUniqueID()) + " ";
		}
		else if (editorObjects[i].type == Placeables::door) {
			Door* _door = dynamic_cast<Door*>(editorObjects[i].entity);
			data += "door ";
			data += std::to_string(_door->localPosition.x) + " ";
			data += std::to_string(_door->localPosition.y) + " ";
			data += std::to_string(_door->localAngle) + " ";
			for (int i = 0; i < links.size(); i++) {
				if (links[i].door == _door) {
					data += std::to_string(links[i].crystals.size()) + " ";
					textfile->Write(data);
					for (int j = 0; j < links[i].crystals.size(); j++) {
						textfile->Write(std::to_string(links[i].crystals[j]->GetUniqueID()));
					}
					break;
				}
			}
			continue;
		}
		else if (editorObjects[i].type == Placeables::enemy) {
			Enemy* _enemy = dynamic_cast<Enemy*>(editorObjects[i].entity);
			data += "enemy ";
			data += std::to_string(_enemy->localPosition.x) + " ";
			data += std::to_string(_enemy->localPosition.y) + " ";
			data += std::to_string(_enemy->localAngle) + " ";
			data += std::to_string(_enemy->GetMaxHealth()) + " ";
			data += std::to_string(_enemy->GetDamage()) + " ";
			data += std::to_string(_enemy->GetSpeed()) + " ";
			data += std::to_string(_enemy->GetLineOfSight()) + " ";
		}
		textfile->Write(data);
	}
	std::string data = "player ";
	data += std::to_string(_player->localPosition.x) + " ";
	data += std::to_string(_player->localPosition.y) + " ";
	data += std::to_string(_player->localAngle) + " ";
	data += std::to_string(_player->GetMaxHealth()) + " ";
	data += std::to_string(_player->GetDamage()) + " ";
	data += std::to_string(_player->GetSpeed()) + " ";
	textfile->Write(data);
	data = "finish ";
	data += std::to_string(_finish->localPosition.x) + " ";
	data += std::to_string(_finish->localPosition.y) + " ";
	data += std::to_string(_finish->localAngle) + " ";
	data += std::to_string(_finish->GetWidth()) + " ";
	data += std::to_string(_finish->GetHeight()) + " ";
	textfile->Write(data);

	textfile->Close();
}

void LevelEditor::Load()
{
	if (saving || warningState) { return; }
	if (loading == false || nameReceiver->GetString().size() > 0) {
		if (nameReceiver->GetString().size() == 0) {
			loading= true;
			AddChild(nameReceiverText);
			AddChild(nameReceiver);
			return;
		}
	}
	else {
		return;
	}

	std::cout << "loading!" << std::endl;
	nameReceiver->SetText("levels/" + nameReceiver->GetString() + ".LEVEL");
	char *_levelName = new char[nameReceiver->GetString().length() + 1];
	strcpy(_levelName, nameReceiver->GetString().c_str());
	nameReceiver->SetText("");

	if (textfile->Open(_levelName)) {
		ClearScene();
		textfile->StartReading();
		while (!textfile->EndOfFile()) {
			std::string lineoftext = textfile->ReadLine();
			EditorObject eo;
			// FLOOR
			if (lineoftext[0] == 'f' && lineoftext[1] == 'l') {
				glm::vec2 _pos;
				float _angle;
				float _width;
				float _height;
				sscanf(lineoftext.c_str(), "floor %f %f %f %f %f %f", &_pos.x, &_pos.y, &_angle, &_width, &_height);
				B2Entity* _floor = new B2Entity(_width, _height, ResourceManager::GetTexture("floor")->GetId(), world);
				_floor->CreateBoxCollider(_width, _height, glm::vec2(0.0f, 0.0f), true, true);
				_floor->localPosition = _pos;
				_floor->localAngle = _angle;
				_floor->SetRepeatableUV(glm::vec2(_floor->GetWidth() / 200.0f, _floor->GetHeight() / 200.0f));
				floors.push_back(_floor);
				continue;
			}
			// WALL
			else if (lineoftext[0] == 'w') {
				glm::vec2 _pos;
				float _angle;
				float _width;
				sscanf(lineoftext.c_str(), "wall %f %f %f %f %f", &_pos.x, &_pos.y, &_angle, &_width);
				B2Entity* _wall = new B2Entity(_width, 750, ResourceManager::GetTexture("wall")->GetId(), world);
				_wall->CreateBoxCollider(_width, 100, glm::vec2(0.0f, 0.0f), false, false);
				_wall->localPosition = _pos;
				_wall->localAngle = _angle;
				_wall->SetRepeatableUV(glm::vec2(_wall->GetWidth() / 720.0f, _wall->GetHeight() / 750.0f));
				eo.entity = _wall;
				eo.type = Placeables::wall;
			}
			// MIRROR
			else if (lineoftext[0] == 'm') {
				glm::vec2 _pos;
				float _angle;
				int _rotatable;
				sscanf(lineoftext.c_str(), "mirror %f %f %f %f", &_pos.x, &_pos.y, &_angle, &_rotatable);
				Mirror* _mirror = new Mirror(_rotatable, 150.0F, 150.0f, ResourceManager::GetTexture("mirror")->GetId(), world);
				_mirror->CreateBoxCollider(100.0f, 110.0f, glm::vec2(0.15f, 0.0f), false, false);
				_mirror->localPosition = _pos;
				_mirror->localAngle = _angle;
				eo.entity = _mirror;
				eo.type = Placeables::mirror;
			}
			else if (lineoftext[0] == 'c') {
				glm::vec2 _pos;
				float _angle;
				float uniqueID;
				sscanf(lineoftext.c_str(), "crystal %f %f %f %f", &_pos.x, &_pos.y, &_angle, &uniqueID);
				Crystal* _crystal = new Crystal(uniqueID, 70, 70, ResourceManager::GetTexture("crystal")->GetId(), world);
				_crystal->CreateBoxCollider(70, 70, glm::vec2(0.0f, 0.0f), false, false);
				_crystal->localPosition = _pos;
				_crystal->localAngle = _angle;
				eo.entity = _crystal;
				eo.type = Placeables::crystal;
				crystalID = uniqueID;
				tmpCrystals.push_back(_crystal);
			}
			else if (lineoftext[0] == 'd') {
				glm::vec2 _pos;
				float _angle;
				float _crystals;
				sscanf(lineoftext.c_str(), "door %f %f %f %f", &_pos.x, &_pos.y, &_angle, &_crystals);
				Door* _door = new Door(550, 550, ResourceManager::GetTexture("door")->GetId(), world);
				_door->CreateBoxCollider(550, 100, glm::vec2(0, 0), false, false);
				_door->localPosition = _pos;
				_door->localAngle = _angle;
				eo.entity = _door;
				eo.type = Placeables::door;
				Link link;
				link.door = _door;
				for (int i = 0; i < _crystals; i++) {
					lineoftext = textfile->ReadLine();
 					int _crystalid;
					sscanf(lineoftext.c_str(), "%d", &_crystalid);
					link.crystalIDs.push_back(_crystalid);
				}
				links.push_back(link);
			}
			else if (lineoftext[0] == 'e') {
				glm::vec2 _pos;
				float _angle;
				float _health;
				float _damage;
				float _speed;
				float _LOS;//LOS short for LineOfSight
				sscanf(lineoftext.c_str(), "enemy %f %f %f %f %f %f %f", &_pos.x, &_pos.y, &_angle, &_health, &_damage, &_speed, &_LOS);
				Enemy* _enemy = new Enemy(nullptr, _LOS, 0.6f, 0.5f, _health, _speed, _damage, 70, 70, ResourceManager::GetTexture("enemy")->GetId(), world);
				_enemy->CreateBoxCollider(70, 70, glm::vec2(0, 0), true, false);
				_enemy->localPosition = _pos;
				_enemy->localAngle = _angle;
				eo.entity = _enemy;
				eo.type = Placeables::enemy;
			}
			else if (lineoftext[0] == 'p') {
				glm::vec2 _pos;
				float _angle;
				float _health;
				float _damage;
				float _speed;
				sscanf(lineoftext.c_str(), "player %f %f %f %f %f %f", &_pos.x, &_pos.y, &_angle, &_health, &_damage, &_speed);
				_player = new Player(camera, _health, _speed, _damage, 100, 100, ResourceManager::GetTexture("player")->GetId(), world);
				_player->CreateCircleCollider(40.0f, true, false);
				_player->localPosition = _pos;
				_player->localAngle = _angle;
				inputPlayerRotation.input->SetText(std::to_string((int)glm::degrees(_angle)));
				inputPlayerHealth.input->SetText(std::to_string((int)_health));
				inputPlayerDamage.input->SetText(std::to_string((int)_damage));
				inputPlayerSpeed.input->SetText(std::to_string((int)_speed));
				continue;
			}
			else if (lineoftext[0] == 'f' && lineoftext[1] == 'i') {
				glm::vec2 _pos;
				float _angle;
				float _width;
				float _height;
				sscanf(lineoftext.c_str(), "finish %f %f %f %f %f", &_pos.x, &_pos.y, &_angle, &_width, &_height);
				_finish = new B2Entity(_width, _height, 0, world);
				_finish->CreateBoxCollider(_width, _height, glm::vec2(0, 0), true, true);
				_finish->SetColor(glm::vec4(1, 0, 1, 0.5f));
				_finish->localPosition = _pos;
				_finish->localAngle = _angle;
				inputFinishRotation.input->SetText(std::to_string((int)glm::degrees(_angle)));
				inputFinishWidth.input->SetText(std::to_string((int)_width));
				inputFinishWidth.input->SetText(std::to_string((int)_width));
				continue;
			}
			if (eo.entity != nullptr) {
				editorObjects.push_back(eo);
			}
		}
		textfile->Close();
		currentlySelected.entity = nullptr;

		// Link all of the crystals with their doors
		for (int i = 0; i < links.size(); i++) {
			for (int j = 0; j < links[i].crystalIDs.size(); j++) {
				for (int k = 0; k < tmpCrystals.size(); k++) {
					if (links[i].crystalIDs[j] == tmpCrystals[k]->GetUniqueID()) {
						links[i].crystals.push_back(tmpCrystals[k]);
					}
				}
			}
		}
		tmpCrystals.clear();
		//currentlySelected.type = currentPlaceable;
	}
	else {
		std::cout << "could not open: " << _levelName << std::endl;
		std::string tmp_levelName = _levelName;
		warning->SetText("Could not load: " + tmp_levelName);
		AddChild(warning);
		warningState = true;
	}
	delete[] _levelName;
}

void LevelEditor::ClearScene()
{
	if (mode != EditorMode::select) {
		DeleteCurrentlySeleceted();
	}
	crystalID = 0;
	camera->SetPosition(glm::vec2(0, 0));
	if (_player != nullptr) {
		delete _player;
		_player = nullptr;
	}
	if (_finish != nullptr) {
		delete _finish;
		_finish = nullptr;
	}
	// Delete the floors
	std::vector<B2Entity*>::iterator itFloor = floors.begin();
	while (itFloor != floors.end()) {
		delete (*itFloor);
		itFloor = floors.erase(itFloor);
	}
	// Delete the editor objects
	std::vector<EditorObject>::iterator itEditorObjects = editorObjects.begin();
	while (itEditorObjects != editorObjects.end()) {
		delete (*itEditorObjects).entity;
		itEditorObjects = editorObjects.erase(itEditorObjects);
	}
	std::vector<Link>::iterator itDoors = links.begin();
	while (itDoors != links.end()) {
		itDoors = links.erase(itDoors);
	}
	currentlySelected.entity = nullptr;
	//currentlySelected.type = currentPlaceable;
}

bool LevelEditor::Menu()
{
	if (menu) {
		menu = false;
		return true;
	}
	return false;
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

void LevelEditor::CreateInputFloat(InputFloat& inputFloat, Sprite * canvas, std::string startValue, glm::vec2 position, std::string text)
{
	//InputFloat inputFloat;
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
	inputFloats.push_back(&inputFloat);
}

Tickbox* LevelEditor::CreateTickbox(Sprite * canvas, bool startValue, glm::vec2 position, std::string text)
{
	Tickbox* tb = new Tickbox(true, ResourceManager::GetTexture("tickboxNotActive")->GetId(), 25, 25, ResourceManager::GetTexture("tickboxActive")->GetId());
	tb->SetActive(startValue);
	tb->SetRenderer(RenderManager::GetSimpleRenderer("hud"));
	tb->localPosition = position;
	canvas->AddChild(tb);
	editorObjectsTickBoxes.push_back(tb);
	Text* t = new Text(text, ResourceManager::GetFont("fonts/arial.ttf", 512, 22), glm::vec3(1, 1, 1), Text::AlignmentX::centerX, Text::AlignmentY::centerY);
	t->localPosition = glm::vec2(position.x, position.y + 50);
	canvas->AddChild(t);
	textVector.push_back(t);
	return tb;
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
