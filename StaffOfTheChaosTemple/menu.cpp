#include "menu.h"

Menu::Menu(int screenWidthCamera, int screenHeightCamera) : Scene::Scene(screenWidthCamera, screenHeightCamera) {
	// Initialize all of the variables
	start = false;
	editor = false;
	quit = false;
	background = new Sprite(screenWidthCamera, screenHeightCamera, ResourceManager::GetTexture("menu")->GetId());
	AddChild(background);
	creditsProgrammer = new Text("Programmed by: Tim Bunk", ResourceManager::GetFont("fonts/arial.ttf", 1024, 70), glm::vec3(0, 0, 0), Text::AlignmentX::leftX, Text::AlignmentY::centerY);
	creditsProgrammer->localPosition = glm::vec2(-800, -300);
	AddChild(creditsProgrammer);
	creditsArtist = new Text("Art by: Merel Wormmeester", ResourceManager::GetFont("fonts/arial.ttf", 1024, 70), glm::vec3(0, 0, 0), Text::AlignmentX::leftX, Text::AlignmentY::centerY);
	creditsArtist->localPosition = glm::vec2(-800, -200);
	AddChild(creditsArtist);
	// Initialize all of the buttons
	startButton = new Button(camera->GetWidth()/3, 150, 0, true);
	startButton->SetColor(glm::vec4(0.505882353f, 0.411764706f, 0.458823529f, 0.5f));
	startButton->CreateText("start", ResourceManager::GetFont("fonts/arial.ttf", 1024, 96), glm::vec3(0, 0, 0));
	startButton->localPosition = glm::vec2(500, 100);
	startButton->SetRenderer(RenderManager::GetSimpleRenderer("hud"));
	this->AddChild(startButton);
	editorButton = new Button(camera->GetWidth() / 3, 150, 0, true);
	editorButton->SetColor(glm::vec4(0.505882353f, 0.411764706f, 0.458823529f, 0.5f));
	editorButton->CreateText("editor", ResourceManager::GetFont("fonts/arial.ttf", 1024, 96), glm::vec3(0, 0, 0));
	editorButton->localPosition = glm::vec2(500, -150);
	editorButton->SetRenderer(RenderManager::GetSimpleRenderer("hud"));
	this->AddChild(editorButton);
	quitButton = new Button(camera->GetWidth()/3, 150, 0, true);
	quitButton->SetColor(glm::vec4(0.505882353f, 0.411764706f, 0.458823529f, 0.5f));
	quitButton->CreateText("quit", ResourceManager::GetFont("fonts/arial.ttf", 1024, 96), glm::vec3(0, 0, 0));
	quitButton->localPosition = glm::vec2(500, -400);
	quitButton->SetRenderer(RenderManager::GetSimpleRenderer("hud"));
	this->AddChild(quitButton);
}

Menu::~Menu() {
	// Delete the allocated memory
	delete background;
	delete creditsProgrammer;
	delete creditsArtist;
	delete startButton;
	delete editorButton;
	delete quitButton;
}

void Menu::Update(double deltaTime) {
	// If hovering over the startbutton make it a differnt color
	if (startButton->Hover()) {
		startButton->SetColor(glm::vec4(0.40f, 0.35f, 0.47f, 0.5f));
		// If start button is down set statrt tot true
		if (startButton->Down()) {
			start = true;
		}
	}
	else {
		startButton->SetColor(glm::vec4(0.505882353f, 0.411764706f, 0.458823529f, 0.5f));
	}
	// If hovering over the editorbutton make it a differnt color
	if (editorButton->Hover()) {
		editorButton->SetColor(glm::vec4(0.40f, 0.35f, 0.47f, 0.5f));
		// If editor button is down set statrt tot true
		if (editorButton->Down()) {
			editor = true;
		}
	}
	else {
		editorButton->SetColor(glm::vec4(0.505882353f, 0.411764706f, 0.458823529f, 0.5f));
	}
	// If hovering over the quitbutton make it a differnt color
	if (quitButton->Hover()) {
		quitButton->SetColor(glm::vec4(0.40f, 0.35f, 0.47f, 0.5f));
		// If quit button is down set statrt tot true
		if (quitButton->Down()) {
			quit = true;
		}
	}
	else {
		quitButton->SetColor(glm::vec4(0.505882353f, 0.411764706f, 0.458823529f, 0.5f));
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
