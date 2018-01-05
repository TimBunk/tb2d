#include "leveleditor.h"

LevelEditor::LevelEditor(int screenWidthCamera, int screenHeightCamera) : Scene::Scene(screenWidthCamera, screenHeightCamera)
{
	levelLoader = new Loadlevel();
	level = nullptr;
	textfile = new Textfile();

	world = new b2World(b2Vec2(0.0f, 0.0f));
	world->SetAllowSleeping(false);

	currentlySelected = nullptr;

	canvasEditor = new Sprite(400, 1080, glm::vec4(0.0f, 0.5f, 0.5f, 0.5f));
	canvasEditor->SetRenderer(RenderManager::GetSimpleRenderer("hud"));
	canvasEditor->localPosition.x = -760;
	this->AddChild(canvasEditor);

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

	CreatePlaceablesTickbox("player", glm::vec2(-150, 500));
	CreatePlaceablesTickbox("wall", glm::vec2(-75, 500));
	CreatePlaceablesTickbox("mirror", glm::vec2(0, 500));
	CreatePlaceablesTickbox("crystal", glm::vec2(75, 500));
	CreatePlaceablesTickbox("floor", glm::vec2(150, 500));
	CreatePlaceablesTickbox("door", glm::vec2(-150, 425));
	CreatePlaceablesTickbox("finish", glm::vec2(-75, 425));

	currentPlaceable = Placeables::player;
	tickboxes[0]->SetActive(true);

	inputtest = new Textinput(true, ResourceManager::GetFont("fonts/arial.ttf", 512, 22), glm::vec3(1, 1, 1), true, 100, 75, glm::vec4(0, 0, 0, 1));
	inputtest->SetMaxLength(5);
	inputtest->SetMaxDecimals(2);
	this->AddChild(inputtest);
}

LevelEditor::~LevelEditor()
{
	delete inputtest;
	delete textfile;
	delete saveButton;
	delete loadButton;
	delete menuButton;

	delete canvasEditor;
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
	// Delete the walls
	std::vector<B2Entity*>::iterator itWall = walls.begin();
	while (itWall != walls.end()) {
		delete (*itWall);
		itWall = walls.erase(itWall);
	}

	delete world;
	delete levelLoader;
	if (level != nullptr) {
		delete level;
	}
}

void LevelEditor::Update(double deltaTime)
{
	if (inputtest->IsActive()) {
		inputtest->SetColor(glm::vec4(0, 1, 0, 1));
	}
	else {
		inputtest->SetColor(glm::vec4(1, 0, 0, 1));
	}
	if (UpdateTickboxes()) {
		// If true that means one of the tickboxes has been pressed so we skip one frame to avoid conflicts
		std::cout << "updated tick boxes" << std::endl;
	}

	if (Input::MousePress(1)) {
		std::cout << "click" << std::endl;
		currentlySelected = nullptr;
	}

	if (currentlySelected != nullptr) {
		currentlySelected->localPosition = Input::GetMousePositionWorldSpace();
	}
	else if (mode == EditorMode::place) {
		currentlySelected = GetPlaceable();
	}

	if (saveButton->Down() && currentlySelected == nullptr) {
		Save("level3.bin");
	}
	if (loadButton->Down() && currentlySelected == nullptr) {
		level = levelLoader->LoadFromFile("level3.bin");
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
			DeleteCurrentlySeleceted();
			tickboxes[currentPlaceable]->SetActive(false);
			currentPlaceable = static_cast<Placeables>(i);
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
	textfile->Create(levelname);
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
	textfile->Close();
}

Entity * LevelEditor::GetPlaceable()
{
	if (currentPlaceable == Placeables::player) {

	}
	else if (currentPlaceable == Placeables::wall) {
		std::cout << "wall" << std::endl;
		B2Entity* _wall = new B2Entity(400, 750, ResourceManager::GetTexture("wall")->GetId(), world);
		_wall->CreateBoxCollider(400, 100, glm::vec2(0.0f, 0.0f), false, false);
		AddChild(_wall);
		walls.push_back(_wall);
		return _wall;
	}
	else if (currentPlaceable == Placeables::mirror) {

	}
	else if (currentPlaceable == Placeables::crystal) {

	}
	else if (currentPlaceable == Placeables::floor) {

	}
	else if (currentPlaceable == Placeables::door) {

	}
	else if (currentPlaceable == Placeables::finish) {

	}
	return nullptr;
}

void LevelEditor::DeleteCurrentlySeleceted()
{
	if (currentlySelected == nullptr) {
		return;
	}
	RemoveChild(currentlySelected);

	if (currentPlaceable == Placeables::player) {

	}
	else if (currentPlaceable == Placeables::wall) {
		std::vector<B2Entity*>::iterator it = walls.begin();
		for (std::vector<B2Entity*>::iterator it = walls.begin(); it != walls.end(); ++it) {
			if ((*it) == currentlySelected) {
				std::cout << "deleting walls is fun" << std::endl;
				walls.erase(it);
				delete currentlySelected;
				currentlySelected = nullptr;
				return;
			}
		}
	}
	else if (currentPlaceable == Placeables::mirror) {

	}
	else if (currentPlaceable == Placeables::crystal) {

	}
	else if (currentPlaceable == Placeables::floor) {

	}
	else if (currentPlaceable == Placeables::door) {

	}
	else if (currentPlaceable == Placeables::finish) {

	}
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

