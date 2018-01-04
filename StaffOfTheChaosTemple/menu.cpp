#include "menu.h"

Menu::Menu(int screenWidthCamera, int screenHeightCamera) : Scene::Scene(screenWidthCamera, screenHeightCamera) {
	// Initialize all of the variables
	init = false;
	start = false;
	editor = false;
	restart = false;
	quit = false;
	this->input = input;
	// Initialize all of the buttons
	startButton = new Button(camera->GetWidth()/3, 150, 0, true, camera);
	startButton->SetColor(glm::vec4(0.505882353f, 0.411764706f, 0.458823529f, 1.0f));
	startButton->CreateText("start", ResourceManager::GetFont("fonts/arial.ttf", 1024, 96), glm::vec3(0, 0, 0));
	startButton->localPosition = glm::vec2(0, 390);
	startButton->SetRenderer(RenderManager::GetSimpleRenderer("hud"));
	this->AddChild(startButton);
	editorButton = new Button(camera->GetWidth() / 3, 150, 0, true, camera);
	editorButton->SetColor(glm::vec4(0.505882353f, 0.411764706f, 0.458823529f, 1.0f));
	editorButton->CreateText("editor", ResourceManager::GetFont("fonts/arial.ttf", 1024, 96), glm::vec3(0, 0, 0));
	editorButton->localPosition = glm::vec2(0, 140);
	editorButton->SetRenderer(RenderManager::GetSimpleRenderer("hud"));
	this->AddChild(editorButton);
	restartButton = new Button(camera->GetWidth()/3, 150, 0, true, camera);
	restartButton->SetColor(glm::vec4(0.505882353f, 0.411764706f, 0.458823529f, 1.0f));
	restartButton->CreateText("restart", ResourceManager::GetFont("fonts/arial.ttf", 1024, 96), glm::vec3(0, 0, 0));
	restartButton->localPosition = glm::vec2(0, -110);
	restartButton->SetRenderer(RenderManager::GetSimpleRenderer("hud"));
	quitButton = new Button(camera->GetWidth()/3, 150, 0, true, camera);
	quitButton->SetColor(glm::vec4(0.505882353f, 0.411764706f, 0.458823529f, 1.0f));
	quitButton->CreateText("quit", ResourceManager::GetFont("fonts/arial.ttf", 1024, 96), glm::vec3(0, 0, 0));
	quitButton->localPosition = glm::vec2(0, -360);
	quitButton->SetRenderer(RenderManager::GetSimpleRenderer("hud"));
	this->AddChild(quitButton);
}

Menu::~Menu() {
	delete startButton;
	delete editorButton;
	delete restartButton;
	delete quitButton;
}

void Menu::Update(double deltaTime) {
	// If the start button is pressed set the menu to not active
	if (startButton->Hover()) {
		startButton->SetColor(glm::vec4(0.40f, 0.35f, 0.47f, 1.0f));
		if (startButton->Down()) {
			start = true;
			// Check if the menu is not yet initialized
			if (!init) {
				InitMenu();
			}
		}
	}
	else {
		startButton->SetColor(glm::vec4(0.505882353f, 0.411764706f, 0.458823529f, 1.0f));
	}
	if (editorButton->Hover()) {
		editorButton->SetColor(glm::vec4(0.40f, 0.35f, 0.47f, 1.0f));
		if (editorButton->Down()) {
			editor = true;
		}
	}
	else {
		editorButton->SetColor(glm::vec4(0.505882353f, 0.411764706f, 0.458823529f, 1.0f));
	}
	// If the restart button is pressed restart the game and launch the game
	if (restartButton->Hover()) {
		restartButton->SetColor(glm::vec4(0.40f, 0.35f, 0.47f, 1.0f));
		if (restartButton->Down()) {
			restart = true;
		}
	}
	else {
		restartButton->SetColor(glm::vec4(0.505882353f, 0.411764706f, 0.458823529f, 1.0f));
	}
	// If the quit button is pressed exit the application
	if (quitButton->Hover()) {
		quitButton->SetColor(glm::vec4(0.40f, 0.35f, 0.47f, 1.0f));
		if (quitButton->Down()) {
			quit = true;
		}
	}
	else {
		quitButton->SetColor(glm::vec4(0.505882353f, 0.411764706f, 0.458823529f, 1.0f));
	}
}

void Menu::InitMenu() {
	startButton->SetText("continue");
	this->AddChild(restartButton);
	init = true;
}

bool Menu::Start() {
	// If start is true and the function is called set it to false automaticly
	if (start) {
		start = false;
		return true;
	}
	return false;
}

bool Menu::Editor()
{
	if (editor) {
		editor = false;
		return true;
	}
	return false;
}

bool Menu::Restart() {
	// If restart is true and the function is called set it to false automaticly
	if (restart) {
		restart = false;
		return true;
	}
	return false;
}
bool Menu::Quit() {
	return quit;
}
