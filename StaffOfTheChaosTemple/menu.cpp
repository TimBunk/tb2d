#include "menu.h"

Menu::Menu(int screenWidthCamera, int screenHeightCamera) : Scene::Scene(screenWidthCamera, screenHeightCamera) {
	// Initialize all of the variables
	init = false;
	start = false;
	restart = false;
	quit = false;
	this->input = input;
	// Initialize all of the buttons
	startButton = new Button(camera->GetWidth()/3, 150, true, glm::vec3(0.505882353f, 0.411764706f, 0.458823529f), camera);
	startButton->CreateText("start", 96, glm::vec3(0, 0, 0));
	startButton->localPosition = glm::vec2(camera->GetWidth() / 2, 750);
	this->AddChild(startButton);
	restartButton = new Button(camera->GetWidth()/3, 150, true, glm::vec3(0.505882353f, 0.411764706f, 0.458823529f), camera);
	restartButton->CreateText("restart", 96, glm::vec3(0, 0, 0));
	restartButton->localPosition = glm::vec2(camera->GetWidth() / 2, 500);
	quitButton = new Button(camera->GetWidth()/3, 150, true, glm::vec3(0.505882353f, 0.411764706f, 0.458823529f), camera);
	quitButton->CreateText("quit", 96, glm::vec3(0, 0, 0));
	quitButton->localPosition = glm::vec2(camera->GetWidth() / 2, 250);
	this->AddChild(quitButton);
}

Menu::~Menu() {
	delete startButton;
	delete restartButton;
	delete quitButton;
}

void Menu::Update(double deltaTime) {
	// Update the childeren of the menu
	this->UpdateChilderen(this, deltaTime);
	// If escape key is pressed or the start button is pressed switch to game state
	if (Input::KeyPress(GLFW_KEY_ESCAPE)) {
		start = true;
		// Check if the menu is not yet initialized
		if (!init) {
			InitMenu();
		}
	}
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
