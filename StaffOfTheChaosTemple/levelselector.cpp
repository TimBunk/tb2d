#include "levelselector.h"

Levelselector::Levelselector(int screenWidthCamera, int screenHeightCamera) : Scene::Scene(screenWidthCamera, screenHeightCamera)
{
	// Intialize the variables
	level = nullptr;
	CreateLevelButton("level: 1", "level1", glm::vec2(20, 400));
	CreateLevelButton("level: 2", "level2", glm::vec2(520, 400));
	CreateLevelButton("level: run", "run", glm::vec2(-480, 250));
	// Create a button for the tutorial level
	tutorial = new Button(400, 100, 0, true);
	tutorial->SetRenderer(RenderManager::GetSimpleRenderer("hud"));
	tutorial->SetColor(glm::vec4(0.505882353f, 0.411764706f, 0.458823529f, 1.0f));
	tutorial->CreateText("tutorial", ResourceManager::GetFont("fonts/arial.ttf", 512, 48), glm::vec3(0, 0, 0));
	tutorial->localPosition = glm::vec2(-480, 400);
	AddChild(tutorial);
	// nameReceiver for loading custom levels
	nameReceiver = new Textinput("", false, ResourceManager::GetFont("fonts/arial.ttf", 512, 48), glm::vec3(1, 1, 1), true, 550, 100, glm::vec4(0, 0, 0, 1));
	nameReceiver->SetRenderer(RenderManager::GetSimpleRenderer("hud"));
	nameReceiver->localPosition.y = -400;
	AddChild(nameReceiver);
	nameReceiverText = new Text("Load and play a custom level by name here:", ResourceManager::GetFont("fonts/arial.ttf", 512, 48), glm::vec3(1, 1, 1), Text::AlignmentX::centerX, Text::AlignmentY::bottomY);
	nameReceiverText->localPosition.y = -340;
	AddChild(nameReceiverText);
	// Load buttonf or loading cutom levels
	load = new Button(300, 100, 0, true);
	load->SetRenderer(RenderManager::GetSimpleRenderer("hud"));
	load->SetColor(glm::vec4(0.75f, 0.75f, 0.75f, 1));
	load->CreateText("load", ResourceManager::GetFont("fonts/arial.ttf", 512, 48), glm::vec3(1, 1, 1));
	load->localPosition.x = 450;
	load->localPosition.y = -400;
	AddChild(load);
	// Error that will popup whenever the user tried to load a file that does not exist
	error = new Button(800, 100, 0, true);
	error->SetRenderer(RenderManager::GetSimpleRenderer("hud"));
	error->SetColor(glm::vec4(0, 0, 0, 1));
	error->CreateText("", ResourceManager::GetFont("fonts/arial.ttf", 512, 30), glm::vec3(1, 1, 1));
	// A victory or defeat screen that will popup after playing a level
	victoryDefeat = new Button(800, 100, 0, true);
	victoryDefeat->SetRenderer(RenderManager::GetSimpleRenderer("hud"));
	victoryDefeat->SetColor(glm::vec4(0, 0, 0, 1));
	victoryDefeat->CreateText("", ResourceManager::GetFont("fonts/arial.ttf", 512, 48), glm::vec3(1, 1, 1));
}

Levelselector::~Levelselector()
{
	// Delete the allocated memory
	delete nameReceiver;
	delete nameReceiverText;
	delete tutorial;
	delete load;
	delete error;
	delete victoryDefeat;
	if (level != nullptr) {
		delete level;
	}
	std::vector<Button*>::iterator it = buttons.begin();
	while (it != buttons.end()) {
		delete (*it);
		it = buttons.erase(it);
	}
}

void Levelselector::Update(double deltaTime)
{
	for (int i = 0; i < buttons.size(); i++) {
		if (buttons[i]->Down()) {
			LoadLevel(levelname[i]);
		}
	}
	// Load the tutorial
	if (tutorial->Down()) {
		level = new Level(3840, 2160);
		level->LoadTutorial();
	}
	// Load custom level
	if (load->Down() && nameReceiver->GetString().length() > 0) {
		LoadLevel(nameReceiver->GetString());
	}
	// Set the color of the nameReceiever
	if (nameReceiver->IsActive()) {
		nameReceiver->SetColor(glm::vec4(0.5f, 0.5f, 0.5f, 1));
	}
	else {
		nameReceiver->SetColor(glm::vec4(0, 0, 0, 1));
	}
	// Remove erorr
	if (error->Down()) {
		error->Update(deltaTime);
		error->SetText("");
		RemoveChild(error);
	}
	// Remove victory defeat screen
	if (victoryDefeat->Down()) {
		victoryDefeat->Update(deltaTime);
		victoryDefeat->SetText("");
		RemoveChild(victoryDefeat);
	}
}

void Levelselector::FinishLevel()
{
	// Remove the victoryDefeat screen if it was already there
	if (victoryDefeat->GetText().length() != 0) {
		RemoveChild(victoryDefeat);
	}
	// Add the victory screen
	victoryDefeat->SetText("VICTORY");
	AddChild(victoryDefeat);
	ExitLevel();
}

void Levelselector::EndLevel()
{
	// Remove the victoryDefeat screen if it was already there
	if (victoryDefeat->GetText().length() != 0) {
		RemoveChild(victoryDefeat);
	}
	// Add the defeat screen
	victoryDefeat->SetText("YOU DIED");
	AddChild(victoryDefeat);
	ExitLevel();
}

void Levelselector::ExitLevel()
{
	// Delete the level and make it a nullptr
	delete level;
	level = nullptr;
}

void Levelselector::LoadLevel(std::string filename)
{
	// Get the filpepath
	std::string _filename = "levels/" + filename + ".LEVEL";
	// Create the level
	level = new Level(3840, 2160);
	// Load level data
	level->LoadFile(_filename);
	// If there were erorrs remove the level and show the error
	if (level->GetLoadingErrors().length() > 0) {
		if (error->GetText().length() == 0) {
			error->SetText(level->GetLoadingErrors());
			AddChild(error);
		}
		delete level;
		level = nullptr;
	}
}

void Levelselector::CreateLevelButton(std::string name, std::string level, glm::vec2 position)
{
	Button* b = new Button(400, 100, 0, true);
	b->SetRenderer(RenderManager::GetSimpleRenderer("hud"));
	b->SetColor(glm::vec4(0.505882353f, 0.411764706f, 0.458823529f, 1.0f));
	b->CreateText(name, ResourceManager::GetFont("fonts/arial.ttf", 512, 48), glm::vec3(0, 0, 0));
	b->localPosition = position;
	AddChild(b);
	buttons.push_back(b);
	levelname.push_back(level);
}
