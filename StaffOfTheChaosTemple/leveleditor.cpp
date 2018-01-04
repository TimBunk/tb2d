#include "leveleditor.h"

LevelEditor::LevelEditor(int screenWidthCamera, int screenHeightCamera) : Scene::Scene(screenWidthCamera, screenHeightCamera)
{
	levelLoader = new Loadlevel();
	level = nullptr;
	textfile = new Textfile();

	world = new b2World(b2Vec2(0.0f, 0.0f));
	world->SetAllowSleeping(false);

	currentlySeleceted = nullptr;

	saveButton = new Button(300, 100, 0, true, camera);
	saveButton->SetColor(glm::vec4(0.505882353f, 0.411764706f, 0.458823529f, 1.0f));
	saveButton->CreateText("save", ResourceManager::GetFont("fonts/arial.ttf", 1024, 96), glm::vec3(0, 0, 0));
	saveButton->localPosition = glm::vec2(camera->GetWidth() / 2 - 150, camera->GetHeight() / 2 - 50);
	saveButton->SetRenderer(RenderManager::GetSimpleRenderer("hud"));
	this->AddChild(saveButton);

	loadButton = new Button(300, 100, 0, true, camera);
	loadButton->SetColor(glm::vec4(0.505882353f, 0.411764706f, 0.458823529f, 1.0f));
	loadButton->CreateText("load", ResourceManager::GetFont("fonts/arial.ttf", 1024, 96), glm::vec3(0, 0, 0));
	loadButton->localPosition = glm::vec2(camera->GetWidth() / 2 - 150, camera->GetHeight() / 2 - 125);
	loadButton->SetRenderer(RenderManager::GetSimpleRenderer("hud"));
	this->AddChild(loadButton);

	wallButton = new Button(300, 100, 0, true, camera);
	wallButton->SetColor(glm::vec4(0.505882353f, 0.411764706f, 0.458823529f, 1.0f));
	wallButton->CreateText("wall", ResourceManager::GetFont("fonts/arial.ttf", 1024, 96), glm::vec3(0, 0, 0));
	wallButton->localPosition = glm::vec2(camera->GetWidth()/2 * -1 + 150, camera->GetHeight()/2 - 50);
	wallButton->SetRenderer(RenderManager::GetSimpleRenderer("hud"));
	this->AddChild(wallButton);
}

LevelEditor::~LevelEditor()
{
	delete textfile;
	delete saveButton;
	delete loadButton;
	delete wallButton;

	std::vector<B2Entity*>::iterator it = walls.begin();
	while (it != walls.end()) {
		delete (*it);
		it = walls.erase(it);
	}

	delete world;
	delete levelLoader;
	if (level != nullptr) {
		delete level;
	}
}

void LevelEditor::Update(double deltaTime)
{
	if (currentlySeleceted != nullptr) {
		currentlySeleceted->localPosition = Input::GetMousePositionWorldSpace(camera);
	}
	if (Input::MousePress(0)) {
		std::cout << "click" << std::endl;
		currentlySeleceted = nullptr;

	}
	if (wallButton->Down() && currentlySeleceted == nullptr) {
		std::cout << "test" << std::endl;
		B2Entity* _wall = new B2Entity(400, 750, ResourceManager::GetTexture("wall")->GetId(), world);
		_wall->CreateBoxCollider(400, 100, glm::vec2(0.0f, 0.0f), false, false);
		AddChild(_wall);
		walls.push_back(_wall);
		currentlySeleceted = _wall;
	}
	if (saveButton->Down() && currentlySeleceted == nullptr) {
		Save("level3.bin");
	}
	if (loadButton->Down() && currentlySeleceted == nullptr) {
		level = levelLoader->LoadFromFile("level3.bin");
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

