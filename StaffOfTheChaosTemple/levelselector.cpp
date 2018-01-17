#include "levelselector.h"

Levelselector::Levelselector(int screenWidthCamera, int screenHeightCamera) : Scene::Scene(screenWidthCamera, screenHeightCamera)
{
	level = nullptr;

	tutorial = new Button(400, 100, 0, true);
	tutorial->SetRenderer(RenderManager::GetSimpleRenderer("hud"));
	tutorial->SetColor(glm::vec4(0.505882353f, 0.411764706f, 0.458823529f, 1.0f));
	tutorial->CreateText("tutorial", ResourceManager::GetFont("fonts/arial.ttf", 512, 48), glm::vec3(0, 0, 0));
	tutorial->localPosition = glm::vec2(-480, 400);
	AddChild(tutorial);

	nameReceiver = new Textinput("", false, ResourceManager::GetFont("fonts/arial.ttf", 512, 48), glm::vec3(1, 1, 1), true, 550, 100, glm::vec4(0, 0, 0, 1));
	nameReceiver->SetRenderer(RenderManager::GetSimpleRenderer("hud"));
	nameReceiver->localPosition.y = -400;
	AddChild(nameReceiver);
	nameReceiverText = new Text("Type the name of the custom level you want to play here:", ResourceManager::GetFont("fonts/arial.ttf", 512, 48), glm::vec3(1, 1, 1), Text::AlignmentX::centerX, Text::AlignmentY::bottomY);
	nameReceiverText->localPosition.y = -340;
	AddChild(nameReceiverText);

	load = new Button(300, 100, 0, true);
	load->SetRenderer(RenderManager::GetSimpleRenderer("hud"));
	load->SetColor(glm::vec4(0.75f, 0.75f, 0.75f, 1));
	load->CreateText("load", ResourceManager::GetFont("fonts/arial.ttf", 512, 48), glm::vec3(1, 1, 1));
	load->localPosition.x = 450;
	load->localPosition.y = -400;
	AddChild(load);

	error = new Button(800, 100, 0, true);
	error->SetRenderer(RenderManager::GetSimpleRenderer("hud"));
	error->SetColor(glm::vec4(0, 0, 0, 1));
	error->CreateText("", ResourceManager::GetFont("fonts/arial.ttf", 512, 30), glm::vec3(1, 1, 1));

	victoryDefeat = new Button(800, 100, 0, true);
	victoryDefeat->SetRenderer(RenderManager::GetSimpleRenderer("hud"));
	victoryDefeat->SetColor(glm::vec4(0, 0, 0, 1));
	victoryDefeat->CreateText("", ResourceManager::GetFont("fonts/arial.ttf", 512, 48), glm::vec3(1, 1, 1));
}

Levelselector::~Levelselector()
{
	delete tutorial;
	delete nameReceiver;
	delete nameReceiverText;
	delete load;
	if (level != nullptr) {
		delete level;
	}
}

void Levelselector::Update(double deltaTime)
{
	if (tutorial->Down()) {
		level = new Level(3840, 2160);
		level->LoadTutorial();
	}
	if (load->Down() && nameReceiver->GetString().length() > 0) {
		LoadLevel(nameReceiver->GetString());
	}
	if (nameReceiver->IsActive()) {
		nameReceiver->SetColor(glm::vec4(0.5f, 0.5f, 0.5f, 1));
	}
	else {
		nameReceiver->SetColor(glm::vec4(0, 0, 0, 1));
	}
	if (error->Down()) {
		error->Update(deltaTime);
		error->SetText("");
		RemoveChild(error);
	}
	if (victoryDefeat->Down()) {
		victoryDefeat->Update(deltaTime);
		victoryDefeat->SetText("");
		RemoveChild(victoryDefeat);
	}
}

Level * Levelselector::GetLevel()
{
	return level;
}

void Levelselector::FinishLevel()
{
	if (victoryDefeat->GetText().length() != 0) {
		RemoveChild(victoryDefeat);
	}
	victoryDefeat->SetText("VICTORY");
	AddChild(victoryDefeat);
	ExitLevel();
}

void Levelselector::EndLevel()
{
	if (victoryDefeat->GetText().length() != 0) {
		RemoveChild(victoryDefeat);
	}
	victoryDefeat->SetText("YOU DIED");
	AddChild(victoryDefeat);
	ExitLevel();
}

void Levelselector::ExitLevel()
{
	delete level;
	level = nullptr;
}

void Levelselector::LoadLevel(std::string filename)
{
	std::string _filename = "levels/" + filename + ".LEVEL";
	level = new Level(3840, 2160);
	level->LoadFile(_filename);
	if (level->GetLoadingErrors().length() > 0) {
		if (error->GetText().length() == 0) {
			error->SetText(level->GetLoadingErrors());
			AddChild(error);
		}
		delete level;
		level = nullptr;
	}
}
