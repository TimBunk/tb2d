#include "menu.h"

Menu::Menu(int screenWidthCamera, int screenHeightCamera) : Scene::Scene(screenWidthCamera, screenHeightCamera) {
	// Initialize all of the variables
	start = false;
	editor = false;
	quit = false;
	// Initialize all of the buttons
	startButton = new Button(camera->GetWidth()/3, 150, 0, true, camera);
	startButton->SetColor(glm::vec4(0.505882353f, 0.411764706f, 0.458823529f, 1.0f));
	startButton->CreateText("start", ResourceManager::GetFont("fonts/arial.ttf", 1024, 96), glm::vec3(0, 0, 0));
	startButton->localPosition = glm::vec2(0, 300);
	startButton->SetRenderer(RenderManager::GetSimpleRenderer("hud"));
	this->AddChild(startButton);
	editorButton = new Button(camera->GetWidth() / 3, 150, 0, true, camera);
	editorButton->SetColor(glm::vec4(0.505882353f, 0.411764706f, 0.458823529f, 1.0f));
	editorButton->CreateText("editor", ResourceManager::GetFont("fonts/arial.ttf", 1024, 96), glm::vec3(0, 0, 0));
	editorButton->localPosition = glm::vec2(0, 50);
	editorButton->SetRenderer(RenderManager::GetSimpleRenderer("hud"));
	this->AddChild(editorButton);
	quitButton = new Button(camera->GetWidth()/3, 150, 0, true, camera);
	quitButton->SetColor(glm::vec4(0.505882353f, 0.411764706f, 0.458823529f, 1.0f));
	quitButton->CreateText("quit", ResourceManager::GetFont("fonts/arial.ttf", 1024, 96), glm::vec3(0, 0, 0));
	quitButton->localPosition = glm::vec2(0, -200);
	quitButton->SetRenderer(RenderManager::GetSimpleRenderer("hud"));
	this->AddChild(quitButton);
}

Menu::~Menu() {
	delete startButton;
	delete editorButton;
	delete quitButton;
}

void Menu::Update(double deltaTime) {
	// If the start button is pressed set the menu to not active
	if (startButton->Hover()) {
		startButton->SetColor(glm::vec4(0.40f, 0.35f, 0.47f, 1.0f));
		if (startButton->Down()) {
			start = true;
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
	// If editor is true and the function is called set it to false automaticly
	if (editor) {
		editor = false;
		return true;
	}
	return false;
}

bool Menu::Quit() {
	return quit;
}
