#include "leveleditor.h"

LevelEditor::LevelEditor(int screenWidthCamera, int screenHeightCamera) : Scene::Scene(screenWidthCamera, screenHeightCamera)
{
	// Initialize all of the variables
	// Textfile is used to read and write files
	textfile = new Textfile();
	// We need a world for the objects and for selecting the objects in the scene
	world = new b2World(b2Vec2(0.0f, 0.0f));
	world->SetAllowSleeping(false);
	// canvasEditor will be the parent of all the editor options
	canvasEditor = new Sprite(800, 2160, glm::vec4(0.0f, 0.5f, 0.5f, 0.5f));
	canvasEditor->SetRenderer(RenderManager::GetSimpleRenderer("hud"));
	canvasEditor->localPosition.x = -1520;
	this->AddChild(canvasEditor);
	// Properties text
	Text* properties = new Text("properties:", ResourceManager::GetFont("fonts/arial.ttf", 1024, 96), glm::vec3(1,1,1), Text::AlignmentX::leftX, Text::AlignmentY::centerY);
	properties->localPosition = glm::vec2(properties->GetWidth() * -1 + 50, 1030);
	canvasEditor->AddChild(properties);
	textVector.push_back(properties);
	// NameReceiver for receiving a name when saving or loading a file
	nameReceiver = new Textinput("", false, ResourceManager::GetFont("fonts/arial.ttf", 1024, 96), glm::vec3(1, 1, 1), true, 1100, 200, glm::vec4(0, 0, 0, 1));
	nameReceiver->SetRenderer(RenderManager::GetSimpleRenderer("hud"));
	nameReceiverText = new Text("Type the name of the file here", ResourceManager::GetFont("fonts/arial.ttf", 1024, 96), glm::vec3(1, 1, 1), Text::AlignmentX::centerX, Text::AlignmentY::bottomY);
	nameReceiverText->localPosition.y = 200;
	textVector.push_back(nameReceiverText);
	// Cancel button for canceling the saving or or loading
	cancel = new Button(300, 150, 0, true);
	cancel->SetColor(glm::vec4(0.8f, 0.2f, 0.2f, 0.9f));
	cancel->CreateText("cancel", ResourceManager::GetFont("fonts/arial.ttf", 1024, 96), glm::vec3(1, 1, 1));
	cancel->localPosition = glm::vec2(825, 0);
	cancel->SetRenderer(RenderManager::GetSimpleRenderer("hud"));
	// save button
	saveButton = new Button(800/3, 150, 0, true);
	saveButton->SetColor(glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));
	saveButton->CreateText("save", ResourceManager::GetFont("fonts/arial.ttf", 1024, 96), glm::vec3(1, 1, 1));
	saveButton->localPosition = glm::vec2(-400 + saveButton->GetWidth()/2 * 1, -1080 + 150 / 2);
	saveButton->SetRenderer(RenderManager::GetSimpleRenderer("hud"));
	saving = false;
	canvasEditor->AddChild(saveButton);
	// load button
	loadButton = new Button(800/3, 150, 0, true);
	loadButton->SetColor(glm::vec4(0.4f, 0.4f, 0.4f, 1.0f));
	loadButton->CreateText("load", ResourceManager::GetFont("fonts/arial.ttf", 1024, 96), glm::vec3(1, 1, 1));
	loadButton->localPosition = glm::vec2(-400 + loadButton->GetWidth() / 2 + saveButton->GetWidth(), -1080 + 150 / 2);
	loadButton->SetRenderer(RenderManager::GetSimpleRenderer("hud"));
	loading = false;
	canvasEditor->AddChild(loadButton);
	// Clear button
	clearButton = new Button(800 / 3, 150, 0, true);
	clearButton->SetColor(glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));
	clearButton->CreateText("clear", ResourceManager::GetFont("fonts/arial.ttf", 1024, 96), glm::vec3(1, 1, 1));
	clearButton->localPosition = glm::vec2(-400 + clearButton->GetWidth() /2 + loadButton->GetWidth() + saveButton->GetWidth(), -1080 + 150 / 2);
	clearButton->SetRenderer(RenderManager::GetSimpleRenderer("hud"));
	canvasEditor->AddChild(clearButton);
	// Warning button that will pop up whenever you do something that is not allowed
	warning = new Button(1100, 200, 0, true);
	warning->SetColor(glm::vec4(0.8f, 0, 0, 1));
	warning->CreateText("", ResourceManager::GetFont("fonts/arial.ttf", 512, 44), glm::vec3(1, 1, 1));
	warning->SetRenderer(RenderManager::GetSimpleRenderer("hud"));
	warningState = false;

	// Player options
	playerCanvas = CreateCanvasPlaceable("player");
	CreateInputFloat(inputPlayerRotation, playerCanvas, "0", glm::vec2(-200, 500), "rotation");
	CreateInputFloat(inputPlayerHealth, playerCanvas, "800", glm::vec2(100, 500), "health");
	CreateInputFloat(inputPlayerDamage, playerCanvas, "10", glm::vec2(-200, 250), "damage");
	CreateInputFloat(inputPlayerSpeed, playerCanvas, "10", glm::vec2(100, 250), "speed");
	_player = nullptr;
	// Wall options
	wallCanvas = CreateCanvasPlaceable("wall");
	CreateInputFloat(inputWallWidth, wallCanvas, "720", glm::vec2(-200, 500), "width");
	CreateInputFloat(inputWallRotation, wallCanvas, "0", glm::vec2(100, 500), "rotation");
	// Mirror options
	mirrorCanvas = CreateCanvasPlaceable("mirror");
	CreateInputFloat(inputMirrorRotation, mirrorCanvas, "0", glm::vec2(-200, 500), "rotation");
	inputMirrorRotator = CreateTickbox(mirrorCanvas, true, glm::vec2(100, 500), "rotator");
	// Crystal options
	crystalCanvas = CreateCanvasPlaceable("crystal");
	CreateInputFloat(inputCrystalRotation, crystalCanvas, "0", glm::vec2(-200, 500), "rotation");
	CreateColorPicker(colorPickerCrystal, crystalCanvas, 200);
	// Floor options
	floorCanvas = CreateCanvasPlaceable("floor");
	CreateInputFloat(inputFloorRotation, floorCanvas, "0", glm::vec2(-200, 500), "rotation");
	CreateInputFloat(inputFloorWidth, floorCanvas, "200", glm::vec2(100, 500), "width");
	CreateInputFloat(inputFloorHeight, floorCanvas, "200", glm::vec2(-200, 250), "height");
	// Door options
	doorCanvas = CreateCanvasPlaceable("door");
	CreateInputFloat(inputDoorRotation, doorCanvas, "0", glm::vec2(-200, 500), "rotation");
	CreateColorPicker(colorPickerDoor, doorCanvas, 200);
	inputDoorLink = CreateTickbox(doorCanvas, false, glm::vec2(100, 500), "link");
	// Enemy options
	enemyCanvas = CreateCanvasPlaceable("enemy");
	CreateInputFloat(inputEnemyRotation, enemyCanvas, "0", glm::vec2(-200, 500), "rotation");
	CreateInputFloat(inputEnemyHealth, enemyCanvas, "300", glm::vec2(100, 500), "health");
	CreateInputFloat(inputEnemyDamage, enemyCanvas, "6", glm::vec2(-200, 250), "speed");
	CreateInputFloat(inputEnemySpeed, enemyCanvas, "150", glm::vec2(100, 250), "damage");
	CreateInputFloat(inputEnemyLOS, enemyCanvas, "3000", glm::vec2(-200, 0), "line of sight");
	// Finish options
	finishCanvas = CreateCanvasPlaceable("finish");
	CreateInputFloat(inputFinishRotation, finishCanvas, "0", glm::vec2(-200, 500), "rotation");
	CreateInputFloat(inputFinishWidth, finishCanvas, "400", glm::vec2(100, 500), "width");
	CreateInputFloat(inputFinishHeight, finishCanvas, "100", glm::vec2(-200, 250), "height");
	_finish = nullptr;

	// Create the tickboxes for all the different editor modes
	CreateEditorModeTickbox("select", glm::vec2(-300, -520));
	CreateEditorModeTickbox("place", glm::vec2(-150, -520));
	CreateEditorModeTickbox("move", glm::vec2(0, -520));
	// set the mode to select and active the tickboxes for select
	mode = EditorMode::select;
	tickboxesMode[0]->SetActive(true);
	// Create a tickbox for every placeable and added to the canvasObject
	canvasObjects = new Entity();
	canvasObjects->localPosition = glm::vec2(0,-600);
	CreatePlaceablesTickbox("player", glm::vec2(-300, -75));
	CreatePlaceablesTickbox("wall", glm::vec2(-150, -75));
	CreatePlaceablesTickbox("mirror", glm::vec2(0, -75));
	CreatePlaceablesTickbox("crystal", glm::vec2(150, -75));
	CreatePlaceablesTickbox("floor", glm::vec2(300, -75));
	CreatePlaceablesTickbox("door", glm::vec2(-300, -190));
	CreatePlaceablesTickbox("enemy", glm::vec2(-150, -190));
	CreatePlaceablesTickbox("finish", glm::vec2(0, -190));
	// Because the player is the first tickbox addChild it and set currentplaceable to player
	canvasEditor->AddChild(playerCanvas);
	currentPlaceable = Placeables::player;
	currentlySelected.type = currentPlaceable;
	tickboxesPlaceable[0]->SetActive(true);
	// Buttont that can remove objects from scene
	remove = new Button(800 / 3, 150, 0, true);
	remove->SetRenderer(RenderManager::GetSimpleRenderer("hud"));
	remove->CreateText("Remove", ResourceManager::GetFont("fonts/arial.ttf", 512, 44), glm::vec3(1, 1, 1));
	remove->SetColor(glm::vec4(1, 0, 0, 1));
	remove->localPosition.y = -750;
	canvasEditor->AddChild(remove);
	// This are the variables I need for linking doors with crystals
	crystalID = 0;
	linking = false;
	linkingText = new Text("Press left mouse button on a crystal to link it with the door or right mouse button to cancel the linking", ResourceManager::GetFont("fonts/arial.ttf", 512, 48), glm::vec3(1,1,1), Text::AlignmentX::centerX, Text::AlignmentY::centerY);
	linkingText->localPosition.y = 500;
	textVector.push_back(linkingText);
	// The guide
	Text* openGuideText = new Text("To open or close the guide press g", ResourceManager::GetFont("fonts/arial.ttf", 512, 44), glm::vec3(1, 1, 1), Text::AlignmentX::centerX, Text::AlignmentY::centerY);
	openGuideText->localPosition.y = 1000;
	AddChild(openGuideText);
	textVector.push_back(openGuideText);
	guide = false;
	canvasGuide = new Sprite(3000, 1800, glm::vec4(0.0f, 0.5f, 0.5f, 0.5f));
	canvasGuide->localPosition.x = 400;
	canvasGuide->SetRenderer(RenderManager::GetSimpleRenderer("hud"));
	AddTextToGuide("Editor guide", 120, glm::vec2(-300, 800));
	AddTextToGuide("Place mode", 70, glm::vec2(-1400, 700));
	AddTextToGuide("In place mode you can place any of the object showns in the bottom left corner.", 50, glm::vec2(-1400, 650));
	AddTextToGuide("If you press right mouse button you can place the object in to the scene.", 50, glm::vec2(-1400, 600));
	AddTextToGuide("Also you can edit their properties that are shown all the way on the left.", 50, glm::vec2(-1400, 550));
	AddTextToGuide("Select mode", 70, glm::vec2(-1400, 450));
	AddTextToGuide("In select mode you can edit the properties of already placed objects in place mode.", 50, glm::vec2(-1400, 400));
	AddTextToGuide("To select a object press left mouse button to deselect press right mouse button.", 50, glm::vec2(-1400, 350));
	AddTextToGuide("Also you can delete the object by pressing the remove button once you selected something.", 50, glm::vec2(-1400, 300));
	AddTextToGuide("Move mode", 70, glm::vec2(-1400, 200));
	AddTextToGuide("Move mode is the same as select mode only you can then also move the objects around.", 50, glm::vec2(-1400, 150));
	AddTextToGuide("Camera movement", 70, glm::vec2(-1400, 50));
	AddTextToGuide("You can move the camera around using the arrow keys or holding the middle mouse button and moving the mouse.", 50, glm::vec2(-1400, 0));
	AddTextToGuide("Saving and loading", 70, glm::vec2(-1400, -100));
	AddTextToGuide("You can press the save or load button in the bottom left corner and then type a name for the file to save to or load from.", 50, glm::vec2(-1400, -150));
}

LevelEditor::~LevelEditor()
{
	// Delete all allocated memory
	ClearScene();
	delete canvasObjects;
	delete textfile;
	delete saveButton;
	delete nameReceiver;
	delete cancel;
	delete warning;
	delete loadButton;
	delete clearButton;
	delete canvasEditor;

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
	std::vector<Tickbox*>::iterator itTickbox = tickboxesPlaceable.begin();
	while (itTickbox != tickboxesPlaceable.end()) {
		delete (*itTickbox);
		itTickbox = tickboxesPlaceable.erase(itTickbox);
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
	// Delete the colorPickers
	std::vector<ColorPicker>::iterator itColorPicker = colorPickers.begin();
	while (itColorPicker != colorPickers.end()) {
		delete (*itColorPicker).text;
		delete (*itColorPicker).r;
		delete (*itColorPicker).g;
		delete (*itColorPicker).b;
		delete (*itColorPicker).colorExample;
		itColorPicker = colorPickers.erase(itColorPicker);
	}
	// Delete the world
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
			camera->PositionAdd(glm::vec2(-700.0f * deltaTime, 0.0f));
		}
		if (Input::KeyDown(GLFW_KEY_UP)) {
			camera->PositionAdd(glm::vec2(0.0f, 700.0f * deltaTime));
		}
		if (Input::KeyDown(GLFW_KEY_RIGHT)) {
			camera->PositionAdd(glm::vec2(700.0f * deltaTime, 0.0f));
		}
		if (Input::KeyDown(GLFW_KEY_DOWN)) {
			camera->PositionAdd(glm::vec2(0.0f, -700.0f * deltaTime));
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
	if (currentlySelected.entity != nullptr) {
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

	// Update the tickboxes for the modes and for the placeables
	UpdateTickboxes();
	// Update all of the input received by the user
	UpdateInputFloats();
	// Updata all of the color pickers
	UpdateColorPickers();
	// Update the currentlyselected placeable
	UpdateCurrentlySelected();

	// If saving or loading wait for the user to enter a name to load or save to
	if (saving || loading) {
		if (cancel->Down()) {
			RemoveChild(nameReceiver);
			RemoveChild(nameReceiverText);
			cancel->Update(deltaTime);
			RemoveChild(cancel);
			nameReceiver->SetText("");
			saving = false;
			loading = false;
		}
		else if (nameReceiver->IsActive() == false) {
			if (nameReceiver->GetString().size() == 0) {
				nameReceiver->SetActive(true);
			}
			else {
				RemoveChild(nameReceiver);
				RemoveChild(nameReceiverText);
				RemoveChild(cancel);
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

	// If the user pressed g open or close the guide
	if (Input::KeyPress(GLFW_KEY_G)) {
		if (guide == false) {
			AddChild(canvasGuide);
			guide = true;
		}
		else {
			RemoveChild(canvasGuide);
			guide = false;
		}
	}
	// If the user is linking a door with a crystal wait for him to be done
	if (linking) { return; }
	// Update the selected mode
	if (mode == EditorMode::place) {
		UpdatePlaceMode();
	}
	else {
		UpdateSelectMode();
	}
	// Save
	if (saveButton->Down()) {
		Save();
	}
	// Load
	if (loadButton->Down()) {
		Load();
	}
	// Clear
	if (clearButton->Down()) {
		ClearScene();
	}
	// If warning is down make it dissappear
	if (warning->Down()) {
		warning->Update(deltaTime);
		RemoveChild(warning);
		warningState = false;
	}
	// Remove currentlyselected
	if (remove->Down()) {
		DeleteCurrentlySeleceted();
	}
}

void LevelEditor::UpdateSelectMode()
{
	// If the user pressed mouse and is hovering over the editorCanvas
	if (Input::MousePress(0) && Input::GetMousePositionScreenSpace().x > -1120) {
		// Get a list of bodies from the world
		b2Body* bodylist = world->GetBodyList();
		// Get mousePosition
		glm::vec2 _mousePos = Input::GetMousePositionWorldSpace();
		// Convert mousePosition from pixels to meters
		b2Vec2 mousePos = b2Vec2(_mousePos.x * B2Entity::p2m, _mousePos.y * B2Entity::p2m);
		// Foundfloor is for in case the user pressed a floor
		bool foundFloor = false;
		// Loop through the bodies
		while (bodylist != NULL) {
			// Check if the mouse hitted a fixture of a body
			if (bodylist->GetFixtureList()->TestPoint(mousePos)) {
				// Convert the seleceted body to a b2entity
				B2Entity* _selected = static_cast<B2Entity*>(bodylist->GetFixtureList()->GetUserData());
				// Check if it was a player
				if (_player == _selected) {
					// If something was already selected place that one first
					if (currentlySelected.entity != nullptr) {
						Place();
					}
					// Set the player as currentlySelected
					currentlySelected.entity = _player;
					currentlySelected.type = Placeables::player;
					Select();
					return;
				}
				else if (_finish == _selected) {
					// If something was already selected place that one first
					if (currentlySelected.entity != nullptr) {
						Place();
					}
					// Set the finish as currentlySelected
					currentlySelected.entity = _finish;
					currentlySelected.type = Placeables::finish;
					Select();
					return;
				}
				// Check if is any of the other placeables
				for (int i = 0; i < editorObjects.size(); i++) {
					if (editorObjects[i].entity == _selected) {
						// If something was already selected place that one first
						if (currentlySelected.entity != nullptr) {
							Place();
						}
						// Set the selected editorObject as currentlySelected
						currentlySelected = editorObjects[i];
						Select();
						return;
					}
				}
				// Check if it is any of the floors
				for (int i = 0; i < floors.size(); i++) {
					if (floors[i] == _selected) {
						// If something was already selected place that one first
						if (currentlySelected.entity != nullptr) {
							Place();
						}
						// Make foundfloor true and set floor as currentlySeleced
						foundFloor = true;
						currentlySelected.entity = floors[i];
						currentlySelected.type = Placeables::floor;
						// Continue looping because something might be on to top of the floor and we rather select what is on top of it
						continue;
					}
				}
			}
			// Get the next body out of the list
			bodylist = bodylist->GetNext();
		}
		// If a floor was found select it
		if (foundFloor) {
			Select();
		}
	}
	// Check if something is currentlySelected
	if (currentlySelected.entity != nullptr) {
		// If move mode is on, move the currentlyselected object to the mouse
		if (mode == EditorMode::move) {
			currentlySelected.entity->localPosition = Input::GetMousePositionWorldSpace();
		}
		// If right mouse button was pressed deselect the currentlyselected by placing it into the scene
		if (Input::MousePress(1)) {
			Place();
			currentlySelected.entity = nullptr;
		}
	}
}

void LevelEditor::UpdatePlaceMode()
{
	// If right mouse button has been pressed drop the currently selected in to the scene
	if (currentlySelected.entity != nullptr && Input::MousePress(1)) {
		Place();
		currentlySelected.entity = nullptr;
	}
	// If something is currentlysleceted move it towards the mouseposition
	else if (currentlySelected.entity != nullptr) {
		currentlySelected.entity->localPosition = Input::GetMousePositionWorldSpace();
	}
	// If nothing is currentlyselected get the a new object
	if (currentlySelected.entity == nullptr) {
		GetPlaceable();
	}
}

void LevelEditor::UpdateTickboxes()
{
	// Update the tickboxes
	for (int i = 0; i < tickboxesPlaceable.size(); i++) {
		// If you try to deactive the tickbox that is active make it active again because that is not allowed
		if (i == currentPlaceable) {
			tickboxesPlaceable[i]->SetActive(true);
		}
		// If a new tickbox has been activated
		if (tickboxesPlaceable[i]->IsActive() && i != currentPlaceable) {
			// If in place mode make sure to delete the currently selected so we can get a new instance of the new currentplaceable
			if (mode == EditorMode::place) {
				DeleteCurrentlySeleceted();
			}
			// Deactive the previous tickbox
			tickboxesPlaceable[currentPlaceable]->SetActive(false);
			// Remove the propertiesCanvas of the previous placeable
			canvasEditor->RemoveChild(propertiesCanvas[currentPlaceable]);
			// Set the new currentPLaceable
			currentPlaceable = static_cast<Placeables>(i);
			canvasEditor->AddChild(propertiesCanvas[currentPlaceable]);
		}
	}
	// Update the tickboxes of the modes
	for (int i = 0; i < tickboxesMode.size(); i++) {
		// If you try to deactive the tickbox that is active make it active again because that is not allowed
		if (i == mode) {
			tickboxesMode[i]->SetActive(true);
		}
		// If a new mode has been selected
		if (tickboxesMode[i]->IsActive() && i != mode) {
			// If the previous mode was selected and something was currentlyselected place that first in to the scene
			if (mode == EditorMode::select) {
				if (currentlySelected.entity != nullptr) {
					Place();
					currentlySelected.entity = nullptr;
				}
			}
			// If the previous mode was not selected then delete whatever was selected at that time
			if (mode != EditorMode::select) {
				DeleteCurrentlySeleceted();
			}
			// deactive the old mode
			tickboxesMode[mode]->SetActive(false);
			// If the old mode was place mode then remove the canvas of objects and add the remove button
			if (mode == EditorMode::place) {
				canvasEditor->RemoveChild(canvasObjects);
				canvasEditor->AddChild(remove);
			}
			// If the old mode does not equals place mode but the new mode equals place mode then add the canvas object and remove the remove button
			else if (mode != EditorMode::place && static_cast<EditorMode>(i) == EditorMode::place) {
				canvasEditor->AddChild(canvasObjects);
				canvasEditor->RemoveChild(remove);
			}
			// Replace the old mode with the new one
			mode = static_cast<EditorMode>(i);
		}
	}
}

void LevelEditor::UpdateInputFloats()
{
	// Update all of the inputFloats by setting the output values and switch color if one is activated
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

void LevelEditor::UpdateColorPickers()
{
	for (int i = 0; i < colorPickers.size(); i++) {
		colorPickers[i].colorExample->SetColor(colorPickers[i].GetColor());
	}
}

void LevelEditor::Place()
{
	// Player
	if (currentlySelected.type == Placeables::player) {
		// If a new player is placed in to the scene delete the old one and repleace it with the new one because we only need 1 player
		if (mode == EditorMode::place && _player != nullptr && _player != currentlySelected.entity) {
			delete _player;
		}
		_player = dynamic_cast<Player*>(currentlySelected.entity);
		_player->SetColor(glm::vec4(0,0,0,0));
		_player->CreateCircleCollider(40.0f, true, false);
	}
	// Wall
	else if (currentlySelected.type == Placeables::wall) {
		B2Entity* _wall = dynamic_cast<B2Entity*>(currentlySelected.entity);
		_wall->SetColor(glm::vec4(0, 0, 0, 0));
		_wall->CreateBoxCollider(_wall->GetWidth(), 100, glm::vec2(0, 0), false, false);
	}
	// Mirror
	else if (currentlySelected.type == Placeables::mirror) {
		Mirror* _mirror = dynamic_cast<Mirror*>(currentlySelected.entity);
		_mirror->SetColor(glm::vec4(0, 0, 0, 0));
		_mirror->CreateBoxCollider(100.0f, 110.0f, glm::vec2(0.15f, 0.0f), false, false);
	}
	// Crystal
	else if (currentlySelected.type == Placeables::crystal) {
		Crystal* _crystal = dynamic_cast<Crystal*>(currentlySelected.entity);
		_crystal->SetColor(colorPickerCrystal.GetColor());
		_crystal->CreateBoxCollider(70, 70, glm::vec2(0.0f, 0.0f), false, false);
	}
	// Floor
	else if (currentlySelected.type == Placeables::floor) {
		B2Entity* _floor = dynamic_cast<B2Entity*>(currentlySelected.entity);
		_floor->SetColor(glm::vec4(0, 0, 0, 0));
		_floor->CreateBoxCollider(_floor->GetWidth(), _floor->GetHeight(), glm::vec2(0, 0), true, true);
	}
	// Door
	else if (currentlySelected.type == Placeables::door) {
		Door* _door = dynamic_cast<Door*>(currentlySelected.entity);
		_door->SetColor(colorPickerDoor.GetColor());
		_door->CreateBoxCollider(550, 100, glm::vec2(0, 0), false, false);
	}
	// Enemy
	else if (currentlySelected.type == Placeables::enemy) {
		Enemy* _enemy = dynamic_cast<Enemy*>(currentlySelected.entity);
		_enemy->SetColor(glm::vec4(0, 0, 0, 0));
		_enemy->CreateBoxCollider(70, 70, glm::vec2(0, 0), true, false);
	}
	// Finish
	else if (currentlySelected.type == Placeables::finish) {
		// If a new finish has been place in to the scene delete the old one and replace it with the new one
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
	// Player
	if (currentlySelected.type == Placeables::player) {
		_player = dynamic_cast<Player*>(currentlySelected.entity);
		_player->SetColor(glm::vec4(0, 0.5f, 1, 0.5f));
	}
	// Wall
	else if (currentlySelected.type == Placeables::wall) {
		B2Entity* _wall = dynamic_cast<B2Entity*>(currentlySelected.entity);
		_wall->SetColor(glm::vec4(0, 0.5f, 1, 0.5f));
		// replace the input values with the wall's data
		std::string s = std::to_string(_wall->GetWidth());
		inputWallWidth.input->SetText(s);
		s = std::to_string((int)glm::degrees(_wall->localAngle));
		inputWallRotation.input->SetText(s);
	}
	// Mirror
	else if (currentlySelected.type == Placeables::mirror) {
		Mirror* _mirror = dynamic_cast<Mirror*>(currentlySelected.entity);
		_mirror->SetColor(glm::vec4(0, 0.5f, 1, 0.5f));
		// replace the input values with the mirror's data
		std::string s = std::to_string((int)glm::degrees(_mirror->localAngle));
		inputMirrorRotation.input->SetText(s);
		inputMirrorRotator->SetActive(_mirror->IsRotatable());
	}
	// Crystal
	else if (currentlySelected.type == Placeables::crystal) {
		Crystal* _crystal = dynamic_cast<Crystal*>(currentlySelected.entity);
		// replace the input values with the crystal's data
		std::string s = std::to_string((int)glm::degrees(_crystal->localAngle));
		inputCrystalRotation.input->SetText(s);
		colorPickerCrystal.SetColor(_crystal->GetColor());
	}
	// floor
	else if (currentlySelected.type == Placeables::floor) {
		B2Entity* _floor = dynamic_cast<B2Entity*>(currentlySelected.entity);
		_floor->SetColor(glm::vec4(0, 0.5f, 1, 0.5f));
		// replace the input values with the floor's data
		std::string s = std::to_string((int)glm::degrees(_floor->localAngle));
		inputFloorRotation.input->SetText(s);
		s = std::to_string((int)_floor->GetWidth());
		inputFloorWidth.input->SetText(s);
		s = std::to_string((int)_floor->GetHeight());
		inputFloorHeight.input->SetText(s);
	}
	// door
	else if (currentlySelected.type == Placeables::door) {
		Door* _door = dynamic_cast<Door*>(currentlySelected.entity);
		// replace the input values with the door data
		std::string s = std::to_string((int)glm::degrees(_door->localAngle));
		inputDoorRotation.input->SetText(s);
		colorPickerDoor.SetColor(_door->GetColor());
	}
	// enemy
	else if (currentlySelected.type == Placeables::enemy) {
		Enemy* _enemy = dynamic_cast<Enemy*>(currentlySelected.entity);
		_enemy->SetColor(glm::vec4(0, 0.5f, 1, 0.5f));
		// replace the input values with the enemy's data
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
	// finish
	else if (currentlySelected.type == Placeables::finish) {
		_finish = dynamic_cast<B2Entity*>(currentlySelected.entity);
		_finish->SetColor(glm::vec4(0, 0.5f, 1, 0.5f));
	}
	// Set the currentlyselected type's tickbox active
	tickboxesPlaceable[currentlySelected.type]->SetActive(true);
}

void LevelEditor::GetPlaceable()
{
	// Player
	if (currentPlaceable == Placeables::player) {
		Player* thePlayer = new Player(camera, 800.0f, 10.0f, 50.0f, 100, 100, ResourceManager::GetTexture("player")->GetId(), world);
		thePlayer->SetColor(glm::vec4(0, 0.5f, 1, 0.5f));
		currentlySelected.entity = thePlayer;
		currentlySelected.type = Placeables::player;
		// Return because we only need 1 instance of the player and it does not need to be in the editorobjects vector
		return;
	}
	// Wall
	else if (currentPlaceable == Placeables::wall) {
		B2Entity* _wall = new B2Entity(720, 750, ResourceManager::GetTexture("wall")->GetId(), world);
		_wall->SetColor(glm::vec4(0, 0.5f, 1, 0.5f));
		currentlySelected.entity = _wall;
		currentlySelected.type = Placeables::wall;
	}
	// Mirror
	else if (currentPlaceable == Placeables::mirror) {
		Mirror* _mirror = new Mirror(true, 150.0f, 150.0f, ResourceManager::GetTexture("mirror")->GetId(), world);
		_mirror->SetColor(glm::vec4(0, 0.5f, 1, 0.5f));
		currentlySelected.entity = _mirror;
		currentlySelected.type = Placeables::mirror;
	}
	// Crystal
	else if (currentPlaceable == Placeables::crystal) {
		// Increase the id of the crystal so that it stays unique
		crystalID++;
		Crystal* _crystal = new Crystal(crystalID, 70, 70, ResourceManager::GetTexture("crystal")->GetId(), world);
		currentlySelected.entity = _crystal;
		currentlySelected.type = Placeables::crystal;
	}
	// Floor
	else if (currentPlaceable == Placeables::floor) {
		B2Entity* _floor = new B2Entity(200, 200, ResourceManager::GetTexture("floor")->GetId(), world);
		_floor->SetColor(glm::vec4(0, 0.5f, 1, 0.5f));
		currentlySelected.entity = _floor;
		currentlySelected.type = Placeables::floor;
		// Return and add floor to the floors vector because we want the floor to be seperated from the other objects
		floors.push_back(_floor);
		return;
	}
	// Door
	else if (currentPlaceable == Placeables::door) {
		Door* _door = new Door(550, 550, ResourceManager::GetTexture("door")->GetId(), world);
		currentlySelected.entity = _door;
		currentlySelected.type = Placeables::door;
		Link link;
		link.door = _door;
		links.push_back(link);
	}
	// Enemy
	else if (currentPlaceable == Placeables::enemy) {
		Enemy* _enemy = new Enemy(nullptr, 3000.0f, 0.6f, 0.5f, 300.0f, 6.0f, 150.0f, 70, 70, ResourceManager::GetTexture("enemy")->GetId(), world);
		_enemy->SetColor(glm::vec4(0, 0.5f, 1, 0.5f));
		currentlySelected.entity = _enemy;
		currentlySelected.type = Placeables::enemy;
	}
	// Finish
	else if (currentPlaceable == Placeables::finish) {
		B2Entity* theFinish = new B2Entity(400, 100, 0, world);
		theFinish->SetColor(glm::vec4(0, 0.5f, 1, 0.5f));
		currentlySelected.entity = theFinish;
		currentlySelected.type = Placeables::finish;
		// Return because we dont need this to be inside of the editorobject because we only need 1 finish
		return;
	}
	// Push back the currenlty selected in to the editorObjects
	editorObjects.push_back(currentlySelected);
}

void LevelEditor::UpdateCurrentlySelected()
{
	// If nothing is currently selected return
	if (currentlySelected.entity == nullptr) { return; }
	// Update the player by their input values
	if (currentlySelected.type == Placeables::player) {
		Player* _player = dynamic_cast<Player*>(currentlySelected.entity);
		_player->localAngle = glm::radians(inputPlayerRotation.output);
		_player->SetMaxHealth(inputPlayerHealth.output);
		_player->SetDamage(inputPlayerDamage.output);
		_player->SetSpeed(inputPlayerSpeed.output);
	}
	// Update the wall by their input values
	else if (currentlySelected.type == Placeables::wall) {
		B2Entity* _wall = dynamic_cast<B2Entity*>(currentlySelected.entity);
		_wall->SetWidth(inputWallWidth.output);
		_wall->SetUV(glm::vec4(0, 0, _wall->GetWidth() / 720.0f, _wall->GetHeight() / 750.0f));
		_wall->localAngle = glm::radians(inputWallRotation.output);
	}
	// Update the mirror by their input values
	else if (currentlySelected.type == Placeables::mirror) {
		Mirror* _mirror = dynamic_cast<Mirror*>(currentlySelected.entity);
		_mirror->localAngle = glm::radians(inputMirrorRotation.output);
		if (_mirror->IsRotatable() != inputMirrorRotator->IsActive()) {
			_mirror->Rotatable(inputMirrorRotator->IsActive());
		}
	}
	// Update the crystal by their input values
	else if (currentlySelected.type == Placeables::crystal) {
		Crystal* _crystal = dynamic_cast<Crystal*>(currentlySelected.entity);
		_crystal->localAngle = glm::radians(inputCrystalRotation.output);
		_crystal->SetColor(colorPickerCrystal.GetColor());
	}
	// Update the floor by their input values
	else if (currentlySelected.type == Placeables::floor) {
		Sprite* _floor = dynamic_cast<Sprite*>(currentlySelected.entity);
		_floor->localAngle = glm::radians(inputFloorRotation.output);
		_floor->SetWidth(inputFloorWidth.output);
		_floor->SetHeight(inputFloorHeight.output);
		_floor->SetUV(glm::vec4(0, 0, _floor->GetWidth() / 200.0f, _floor->GetHeight() / 200.0f));
	}
	// Update the door by their input values
	else if (currentlySelected.type == Placeables::door) {
		Door* _door = dynamic_cast<Door*>(currentlySelected.entity);
		_door->localAngle = glm::radians(inputDoorRotation.output);
		_door->SetColor(colorPickerDoor.GetColor());
		// Call the linking function in case it has been activated
		Linking();
	}
	// Update the enemy by their input values
	else if (currentlySelected.type == Placeables::enemy) {
		Enemy* _enemy = dynamic_cast<Enemy*>(currentlySelected.entity);
		_enemy->localAngle = glm::radians(inputEnemyRotation.output);
		_enemy->SetMaxHealth(inputEnemyHealth.output);
		_enemy->SetDamage(inputEnemyDamage.output);
		_enemy->SetSpeed(inputEnemySpeed.output);
		_enemy->SetLineOfSight(inputEnemyLOS.output);
	}
	// Update the finish by their input values
	else if (currentlySelected.type == Placeables::finish) {
		B2Entity* _finish = dynamic_cast<B2Entity*>(currentlySelected.entity);
		_finish->localAngle = glm::radians(inputFinishRotation.output);
		_finish->SetWidth(inputFinishWidth.output);
		_finish->SetHeight(inputFinishHeight.output);
	}
}

void LevelEditor::DeleteCurrentlySeleceted()
{
	// Return if nothing was currently selected
	if (currentlySelected.entity == nullptr) { return; }
	// If the currently selected was the player remove it
	if (currentlySelected.entity == _player) {
		delete _player;
		_player = nullptr;
	}
	// If the currently selected was the finish delete it
	else if (currentlySelected.entity == _finish) {
		delete _finish;
		_finish = nullptr;
	}
	// If currently selected is a floor
	if (currentlySelected.type == Placeables::floor) {
		// Delete the currently selected floor object
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
				// If it is a crystal remove any links made to that crystals
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
		// Set the currently selected entity to nullptr
		currentlySelected.entity = nullptr;
	}
}

void LevelEditor::Save()
{
	// If loading or a warningState is active return
	if (loading || warningState) { return; }
	// Return if there is no player or no finish in the scene because those are required to play the level
	if (_player == nullptr || _finish == nullptr) {
		if (warningState == false) {
			warning->SetText("You need atleast a player and a finish to save");
			AddChild(warning);
			warningState = true;
		}
		return;
	}
	if (saving == false || nameReceiver->GetString().size() > 0) {
		// If namereceiver hass not yet received charaters add the namereceiver to the scene
		if (nameReceiver->GetString().size() == 0) {
			saving = true;
			nameReceiverText->SetText("Type the name of the file you want to save to here");
			AddChild(nameReceiverText);
			AddChild(nameReceiver);
			AddChild(cancel);
			return;
		}
	}
	else {
		// Return if saving is true or not characters where entered in to the namereceiver
		return;
	}
	// If mode does not equals select, delte the currently selected first
	if (mode != EditorMode::select) {
		DeleteCurrentlySeleceted();
	}
	// Start saving
	// Create the localFilepath string inside of the namereceiver
	nameReceiver->SetText("levels/" + nameReceiver->GetString() + ".LEVEL");
	// Create the savefile or overwrite it if it already exists
	textfile->Create(nameReceiver->GetString().c_str());
	// Reset the text of the namreceiever
	nameReceiver->SetText("");
	// First save all of the floors
	for (int i = 0; i < floors.size(); i++) {
		std::string data = "floor ";
		data += std::to_string(floors[i]->localPosition.x) + " ";
		data += std::to_string(floors[i]->localPosition.y) + " ";
		data += std::to_string(floors[i]->localAngle) + " ";
		data += std::to_string(floors[i]->GetWidth()) + " ";
		data += std::to_string(floors[i]->GetHeight()) + " ";
		textfile->Write(data);
	}
	// Then save all of the editorobjects
	for (int i = 0; i < editorObjects.size(); i++) {
		std::string data = "";
		// Wall
		if (editorObjects[i].type == Placeables::wall) {
			B2Entity* _wall = dynamic_cast<B2Entity*>(editorObjects[i].entity);
			data += "wall ";
			data += std::to_string(_wall->localPosition.x) + " ";
			data += std::to_string(_wall->localPosition.y) + " ";
			data += std::to_string(_wall->localAngle) + " ";
			data += std::to_string(_wall->GetWidth()) + " ";
		}
		// Mirrors
		else if (editorObjects[i].type == Placeables::mirror) {
			Mirror* _mirror = dynamic_cast<Mirror*>(editorObjects[i].entity);
			data += "mirror ";
			data += std::to_string(_mirror->localPosition.x) + " ";
			data += std::to_string(_mirror->localPosition.y) + " ";
			data += std::to_string(_mirror->localAngle) + " ";
			data += std::to_string(_mirror->IsRotatable()) + " ";
		}
		// Crystal
		else if (editorObjects[i].type == Placeables::crystal) {
			Crystal* _crystal = dynamic_cast<Crystal*>(editorObjects[i].entity);
			data += "crystal ";
			data += std::to_string(_crystal->localPosition.x) + " ";
			data += std::to_string(_crystal->localPosition.y) + " ";
			data += std::to_string(_crystal->localAngle) + " ";
			data += std::to_string(_crystal->GetUniqueID()) + " ";
		}
		// Door
		else if (editorObjects[i].type == Placeables::door) {
			Door* _door = dynamic_cast<Door*>(editorObjects[i].entity);
			data += "door ";
			data += std::to_string(_door->localPosition.x) + " ";
			data += std::to_string(_door->localPosition.y) + " ";
			data += std::to_string(_door->localAngle) + " ";
			// Checking for any links the door might have
			for (int i = 0; i < links.size(); i++) {
				// If the correct links has been found
				if (links[i].door == _door) {
					// Also save the amount of crystals linked to the door this makes it easier to load the save file
					data += std::to_string(links[i].crystals.size()) + " ";
					textfile->Write(data);
					// Save all of the linked crystals by their uniqueID to this door
					for (int j = 0; j < links[i].crystals.size(); j++) {
						textfile->Write(std::to_string(links[i].crystals[j]->GetUniqueID()));
					}
					break;
				}
			}
			continue;
		}
		// Enemy
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
	// Save the player
	std::string data = "player ";
	data += std::to_string(_player->localPosition.x) + " ";
	data += std::to_string(_player->localPosition.y) + " ";
	data += std::to_string(_player->localAngle) + " ";
	data += std::to_string(_player->GetMaxHealth()) + " ";
	data += std::to_string(_player->GetDamage()) + " ";
	data += std::to_string(_player->GetSpeed()) + " ";
	textfile->Write(data);
	// Save the finish
	data = "finish ";
	data += std::to_string(_finish->localPosition.x) + " ";
	data += std::to_string(_finish->localPosition.y) + " ";
	data += std::to_string(_finish->localAngle) + " ";
	data += std::to_string(_finish->GetWidth()) + " ";
	data += std::to_string(_finish->GetHeight()) + " ";
	textfile->Write(data);
	// Close the save file
	textfile->Close();
}

void LevelEditor::Load()
{
	// saving or a warning is up return
	if (saving || warningState) { return; }
	// If loading is false
	if (loading == false || nameReceiver->GetString().size() > 0) {
		// If the namereceiver's size is 0 that means the namereceiver has not yet been added to scene so add it
		if (nameReceiver->GetString().size() == 0) {
			loading= true;
			nameReceiverText->SetText("Type the name of the save file you want to load here");
			AddChild(nameReceiverText);
			AddChild(nameReceiver);
			AddChild(cancel);
			return;
		}
	}
	else {
		// Return if loading is true or no characters have been entered yet
		return;
	}
	// Set the filepath to the loaded file
	nameReceiver->SetText("levels/" + nameReceiver->GetString() + ".LEVEL");
	// Try to open the save file
	if (textfile->Open(nameReceiver->GetString().c_str())) {
		// Remove everything that is currently in the scene
		ClearScene();
		// Start reading the save file
		textfile->StartReading();
		// Loop through every line of text
		while (!textfile->EndOfFile()) {
			// Save the readed line in to a string
			std::string lineoftext = textfile->ReadLine();
			// EditorObject
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
				_floor->SetUV(glm::vec4(0, 0, _floor->GetWidth() / 200.0f, _floor->GetHeight() / 200.0f));
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
				_wall->SetUV(glm::vec4(0, 0, _wall->GetWidth() / 720.0f, _wall->GetHeight() / 750.0f));
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
			// CRYSTALs
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
				// Tmp save the crystals so that we can link them at the end of the loading
				tmpCrystals.push_back(_crystal);
			}
			// DOOR
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
				// Create all the links that belong to that door
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
			// ENEMY
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
			// Player
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
			}
			// FINISH
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
			}
			// If the loaded editor object does not equal a nullptr continue, it can be a nullptr when it is a player, floor or finish that has been currently loaded
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
		// Get rid of all the tmp crystals
		tmpCrystals.clear();
	}
	else {
		// The save file could not be opened so throw a warning 
		warning->SetText("Could not load: " + nameReceiver->GetString());
		AddChild(warning);
		warningState = true;
	}
	nameReceiver->SetText("");
}

void LevelEditor::ClearScene()
{
	// Set the crystal id back to 0
	crystalID = 0;
	// Set camera position back to 0,0
	camera->SetPosition(glm::vec2(0, 0));
	// delete the player if it exists
	if (_player != nullptr) {
		delete _player;
		_player = nullptr;
	}
	// delete the finsih if it exists
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
	// Delete all of the links
	std::vector<Link>::iterator itDoors = links.begin();
	while (itDoors != links.end()) {
		itDoors = links.erase(itDoors);
	}
	// Currentlyselected = nullptr
	currentlySelected.entity = nullptr;
}

void LevelEditor::Linking()
{
	// If the user actived linking and is in select mode
	if (inputDoorLink->IsActive() && linking == false && mode == EditorMode::select) {
		// Remove the editor canvas and add the linkingText that provides instructions on how to procceed
		linking = true;
		RemoveChild(canvasEditor);
		AddChild(linkingText);
	}
	// If linking was already active
	else if (linking) {
		// If the user pressed left or right mouse button
		if (Input::MousePress(0) || Input::MousePress(1)) {
			// Get list of bodies from the b2world
			b2Body* bodylist = world->GetBodyList();
			// Get the mousePosition
			glm::vec2 _mousePos = Input::GetMousePositionWorldSpace();
			// ConverMouseposition from pixels to meters
			b2Vec2 mousePos = b2Vec2(_mousePos.x * B2Entity::p2m, _mousePos.y * B2Entity::p2m);
			// Loop through all of the bodies
			while (bodylist != NULL) {
				// If a body was found at the mouse position
				if (bodylist->GetFixtureList()->TestPoint(mousePos)) {
					// Conver the body to a b2entity
					B2Entity* _selected = static_cast<B2Entity*>(bodylist->GetFixtureList()->GetUserData());
					// Go through all of the editorobjects and see which on matches with the selected
					for (int i = 0; i < editorObjects.size(); i++) {
						// Look if the selected type is a crystal
						if (editorObjects[i].entity == _selected && editorObjects[i].type == Placeables::crystal) {
							for (int j = 0; j < links.size(); j++) {
								// Look for the correct link
								if (links[j].door == currentlySelected.entity) {
									if (Input::MousePress(0)) {
										// Check if it was not already linked otherwise remove that one first
										std::vector<Crystal*>::iterator itCrystals = links[j].crystals.begin();
										while (itCrystals != links[j].crystals.end()) {
											if ((*itCrystals) == dynamic_cast<Crystal*>(editorObjects[i].entity)) {
												links[j].crystals.erase(itCrystals);
												break;
											}
											else {
												++itCrystals;
											}
										}
										// Link the crystal with the door
										links[j].crystals.push_back(dynamic_cast<Crystal*>(editorObjects[i].entity));
										inputDoorLink->SetActive(false);
										AddChild(canvasEditor);
										RemoveChild(linkingText);
										linking = false;
									}
									else {
										// Delete the crystal link if right mouse button was clicked on it and it was linked with that door
										std::vector<Crystal*>::iterator itCrystals = links[j].crystals.begin();
										while (itCrystals != links[j].crystals.end()) {
											if ((*itCrystals) == dynamic_cast<Crystal*>(editorObjects[i].entity)) {
												links[j].crystals.erase(itCrystals);
												break;
											}
											else {
												++itCrystals;
											}
										}
									}
								}
							}
						}
					}
				}
				// Get the next body
				bodylist = bodylist->GetNext();
			}
		}
		// If right mouse button was pressed leave linking mode and add the canvasEditor again
		if (Input::MousePress(1)) {
			inputDoorLink->SetActive(false);
			AddChild(canvasEditor);
			RemoveChild(linkingText);
			linking = false;
		}
	}
	// If inputDoorlink is active and the mode is not select then throw a warning
	else if (inputDoorLink->IsActive()) {
		inputDoorLink->SetActive(false);
		if (warningState == false) {
			AddChild(warning);
			warning->SetText("Linking can only be done in select mode");
			warningState = true;
		}
	}
}

void LevelEditor::CreatePlaceablesTickbox(std::string text, glm::vec2 position)
{
	// Create a new tickbox
	Tickbox* tb = new Tickbox(true, ResourceManager::GetTexture("tickboxNotActive")->GetId(), 50, 50, ResourceManager::GetTexture("tickboxActive")->GetId());
	tb->SetRenderer(RenderManager::GetSimpleRenderer("hud"));
	tb->localPosition = position;
	// Save reference to this tickbox
	tickboxesPlaceable.push_back(tb);
	// Add the tickbox to the canvas
	canvasObjects->AddChild(tb);
	// Add a text for the tickbox
	Text* t = new Text(text, ResourceManager::GetFont("fonts/arial.ttf", 512, 44), glm::vec3(1, 1, 1), Text::AlignmentX::centerX, Text::AlignmentY::bottomY);
	t->localPosition = glm::vec2(position.x, position.y + 50);
	textVector.push_back(t);
	canvasObjects->AddChild(t);
}

void LevelEditor::CreateEditorModeTickbox(std::string text, glm::vec2 position)
{
	// Create a new tickbox for the modes
	Tickbox* tb = new Tickbox(true, ResourceManager::GetTexture("tickboxNotActive")->GetId(), 50, 50, ResourceManager::GetTexture("tickboxActive")->GetId());
	tb->SetRenderer(RenderManager::GetSimpleRenderer("hud"));
	tb->localPosition = position;
	// Save reference to thiss tickbox
	tickboxesMode.push_back(tb);
	canvasEditor->AddChild(tb);
	// Create a text for the tickbox
	Text* t = new Text(text, ResourceManager::GetFont("fonts/arial.ttf", 512, 44), glm::vec3(1, 1, 1), Text::AlignmentX::centerX, Text::AlignmentY::bottomY);
	t->localPosition = glm::vec2(position.x, position.y + 50);
	canvasEditor->AddChild(t);
	textVector.push_back(t);
}

void LevelEditor::CreateInputFloat(InputFloat& inputFloat, Sprite * canvas, std::string startValue, glm::vec2 position, std::string text)
{
	// Set all of the values of the tickbox by the given information
	inputFloat.text = new Text(text, ResourceManager::GetFont("fonts/arial.ttf", 512, 44), glm::vec3(1, 1, 1), Text::AlignmentX::centerX, Text::AlignmentY::centerY);
	inputFloat.text->localPosition = glm::vec2(position.x, position.y + 100);
	inputFloat.input = new Textinput(startValue, true, ResourceManager::GetFont("fonts/arial.ttf", 512, 44), glm::vec3(1, 1, 1), true, 200, 80, ResourceManager::GetTexture("textinput")->GetId());
	inputFloat.input->SetMaxLength(7);
	inputFloat.input->SetMaxDecimals(2);
	inputFloat.input->SetRenderer(RenderManager::GetSimpleRenderer("hud"));
	inputFloat.input->localPosition = position;
	inputFloat.output = 0.0f;
	// Add and save the inputfloat
	canvas->AddChild(inputFloat.text);
	canvas->AddChild(inputFloat.input);
	inputFloats.push_back(&inputFloat);
}

void LevelEditor::CreateColorPicker(ColorPicker & colorPicker, Sprite * canvas, float yPos)
{
	colorPicker.text = new Text("RGB color picker", ResourceManager::GetFont("fonts/arial.ttf", 512, 44), glm::vec3(1, 1, 1), Text::AlignmentX::centerX, Text::AlignmentY::centerY);
	colorPicker.text->localPosition.y = 200 + yPos;
	canvas->AddChild(colorPicker.text);
	colorPicker.r = new Slider(100, 50, glm::vec4(0.5f, 0.5f, 0.5f, 1), true, 25, 300, ResourceManager::GetTexture("slider")->GetId());
	colorPicker.r->SetRenderer(RenderManager::GetSimpleRenderer("hud"));
	colorPicker.r->localPosition = glm::vec2(-300, yPos);
	canvas->AddChild(colorPicker.r);
	colorPicker.g = new Slider(100, 50, glm::vec4(0.5f, 0.5f, 0.5f, 1), true, 25, 300, ResourceManager::GetTexture("slider")->GetId());
	colorPicker.g->SetRenderer(RenderManager::GetSimpleRenderer("hud"));
	colorPicker.g->localPosition = glm::vec2(-175, yPos);
	canvas->AddChild(colorPicker.g);
	colorPicker.b = new Slider(100, 50, glm::vec4(0.5f, 0.5f, 0.5f, 1), true, 25, 300, ResourceManager::GetTexture("slider")->GetId());
	colorPicker.b->SetRenderer(RenderManager::GetSimpleRenderer("hud"));
	colorPicker.b->localPosition = glm::vec2(-50, yPos);
	canvas->AddChild(colorPicker.b);
	colorPicker.colorExample = new Sprite(225, 300, glm::vec4(0,0,0,1));
	colorPicker.colorExample->SetRenderer(RenderManager::GetSimpleRenderer("hud"));
	colorPicker.colorExample->localPosition = glm::vec2(143, yPos);
	canvas->AddChild(colorPicker.colorExample);
	colorPickers.push_back(colorPicker);
}

Tickbox* LevelEditor::CreateTickbox(Sprite * canvas, bool startValue, glm::vec2 position, std::string text)
{
	// Create a single tickbox and add it to the provided canvas
	Tickbox* tb = new Tickbox(true, ResourceManager::GetTexture("tickboxNotActive")->GetId(), 50, 50, ResourceManager::GetTexture("tickboxActive")->GetId());
	tb->SetActive(startValue);
	tb->SetRenderer(RenderManager::GetSimpleRenderer("hud"));
	tb->localPosition = position;
	canvas->AddChild(tb);
	editorObjectsTickBoxes.push_back(tb);
	Text* t = new Text(text, ResourceManager::GetFont("fonts/arial.ttf", 512, 44), glm::vec3(1, 1, 1), Text::AlignmentX::centerX, Text::AlignmentY::centerY);
	t->localPosition = glm::vec2(position.x, position.y + 100);
	canvas->AddChild(t);
	textVector.push_back(t);
	return tb;
}

Sprite * LevelEditor::CreateCanvasPlaceable(std::string name)
{
	// Create a canvas for the placeables
	Sprite* canvas = new Sprite(800, 1300, glm::vec4(0.0f, 0.5f, 0.5f, 0.5f));
	canvas->localPosition.y = 280;
	canvas->SetRenderer(RenderManager::GetSimpleRenderer("hud"));
	propertiesCanvas.push_back(canvas);
	// Create a text for the placeable canvas
	Text* t = new Text(name, ResourceManager::GetFont("fonts/arial.ttf", 1024, 88), glm::vec3(1, 1, 1), Text::AlignmentX::leftX, Text::AlignmentY::centerY);
	t->localPosition.x = 70;
	t->localPosition.y = 750;
	textVector.push_back(t);
	canvas->AddChild(t);

	return canvas;
}

void LevelEditor::AddTextToGuide(std::string text, int fontsize, glm::vec2 position)
{
	// Add a new text to the guide
	Text* _text = new Text(text, ResourceManager::GetFont("fonts/arial.ttf", 1024, fontsize), glm::vec3(1, 1, 1), Text::AlignmentX::leftX, Text::AlignmentY::centerY);
	_text->localPosition = position;
	canvasGuide->AddChild(_text);
	textVector.push_back(_text);
}
