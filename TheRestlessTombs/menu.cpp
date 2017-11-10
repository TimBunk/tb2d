#include "menu.h"

Menu::Menu(ResourceManager* rm, Input* input, Camera* camera) : Scene::Scene(camera) {
	// Initialize all of the variables
	active = true;
	restart = false;
	quit = false;
	this->input = input;
	titleGame = new Text("fonts/OpenSans-Regular.ttf", "The Restless Tombs", 90, glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), true, camera, rm->GetShader("textHud"));
	titleGame->localPosition = glm::vec3(camera->screenWidth/2 - titleGame->GetWidth()/4, 100, 1.0f);
	this->AddChild(titleGame);
	startButton = new Button(camera->screenWidth/2, 200, 125, 75, true, "start", glm::vec4(0.505882353f, 0.411764706f, 0.458823529f, 1.0f), input, camera, rm);
	this->AddChild(startButton);
	restartButton = new Button(camera->screenWidth/2, 300, 125, 75, true, "restart", glm::vec4(0.505882353f, 0.411764706f, 0.458823529f, 1.0f), input, camera, rm);
	quitButton = new Button(camera->screenWidth/2, 400, 125, 75, true, "quit", glm::vec4(0.505882353f, 0.411764706f, 0.458823529f, 1.0f), input, camera, rm);
	this->AddChild(quitButton);
	credits = new Text("fonts/OpenSans-Regular.ttf", "Credits\nProgrammed by Tim Bunk\nArt done by https://0x72.itch.io", 60, glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), true, camera, rm->GetShader("textHud"));
	credits->localPosition = glm::vec3(0.0f, camera->screenHeight - credits->GetHeight()/2, 1.0f);
	this->AddChild(credits);
}

Menu::~Menu() {
	delete titleGame;
	delete startButton;
	delete restartButton;
	delete quitButton;
	delete credits;
}

void Menu::Update(double deltaTime) {
	// Update the childeren of the menu
	this->UpdateChilderen(this, deltaTime);
	// If escape key is down or the start button is pressed switch to game state
	if (input->KeyPress(SDL_SCANCODE_ESCAPE)) {
		active = false;
	}
	// If the start button is pressed set the menu to not active
	if (startButton->Hover()) {
		startButton->SetColor(glm::vec4(0.40f, 0.35f, 0.47f, 1.0f));
		if (startButton->Down()) {
			active = false;
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
			active = false;
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
}

void Menu::SetActive(bool active) {
	this->active = active;
}

bool Menu::IsActive() {
	return active;
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
