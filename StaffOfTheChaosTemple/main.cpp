#include <iostream>
#include <string>

#include <gl\glew.h>
#include <glfw3.h>
#include <glm-0.9.8.4\glm\glm.hpp>
#include <glm-0.9.8.4\glm\gtc\matrix_transform.hpp>
#include <glm-0.9.8.4\glm\gtc\type_ptr.hpp>
#include <glm-0.9.8.4\glm\gtx\matrix_decompose.hpp>

#include "window.h"
#include "contactListener.h"
#include "sprite.h"
#include "scene.h"
#include "menu.h"
#include "button.h"
#include "b2entity.h"
#include "player.h"
#include "level1.h"
#include "level2.h"
#include "mirror.h"
#include "rotator.h"
#include "crystal.h"
#include "door.h"

#include <ft2build.h>
#include FT_FREETYPE_H

Window* window;
ResourceManager* rm;
Input* input;

Texture* texture;

Level1* level1;
Level2* level2;

ContactListener* contactListener;
b2World* world;
Player* player;

Menu* menu;

float B2Entity::m2p = 50.0f;
float B2Entity::p2m = 1.0f / B2Entity::m2p;

enum GameState
{
	_game,
	_menu
};

GameState gameState;

int levelCounter = 0;
std::vector<Level*> levels;

int main() {
	std::cout << "hello world" << std::endl;
	window = new Window("Staff of the Chaos Temple", false);
	window->Resize(800, 600);

	rm = window->GetResourceManager();
	rm->CreateTexture("awesome", "textures/awesomeface.png", TextureWrap::repeat, TextureFilter::linear, TextureType::diffuse);
	rm->CreateTexture("player", "textures/container.jpg", TextureWrap::repeat, TextureFilter::linear, TextureType::diffuse);
	rm->CreateTexture("wall", "textures/wall.jpg", TextureWrap::repeat, TextureFilter::linear, TextureType::diffuse);
	rm->CreateTexture("staff", "textures/magic.png", TextureWrap::repeat, TextureFilter::linear, TextureType::diffuse);
	rm->CreateTexture("laser", "textures/container2.png", TextureWrap::repeat, TextureFilter::linear, TextureType::diffuse);
	rm->CreateTexture("crystal", "textures/container2_specular.png", TextureWrap::repeat, TextureFilter::linear, TextureType::diffuse);

	rm->CreateShader("debug", "shaders\\debugRenderer.vs", "shaders\\debugRenderer.fs");
	rm->CreateShader("crystal", "shaders\\defaultShader.vs", "shaders\\crystal.fs");

	input = window->GetInput();
	window->SetBackgroundColor(glm::vec3(0.0f, 0.4f, 0.8f));

	contactListener = new ContactListener();
	world = new b2World(b2Vec2(0.0f, 0.0f));
	world->SetContactListener(contactListener);
	world->SetAllowSleeping(false);

	level1 = new Level1(world, 1920, 1080, rm);
	level2 = new Level2(world, 1920, 1080, rm);

	player = new Player(input, rm, 10, 10.0f, 1, level1->GetCamera(), rm->GetShader("defaultShader"), world);
	player->CreateBodyBox(960, 0, 100, 100, glm::vec2(0.0f, 0.0f), true, false, false);
	player->GiveTexture(rm->GetTexture("player"));

	level1->AddChild(player);
	level2->AddChild(player);

	levels.push_back(level1);
	levels.push_back(level2);
	level1->SetPlayer(player);

	gameState = _menu;
	menu = new Menu(input, 1920, 1080, rm);

	while (!window->ShouldClose()) {
		// rendering commands
		window->Clear();
		// You have to update the window because the window will calculate the deltaTime and it updates the input
		window->Update();

		switch (gameState)
		{
		case _game:
			levels[levelCounter]->Update(window->GetDeltaTime());
			if (levels[levelCounter]->IsFinished()) {
				levelCounter++;
				if (levelCounter == levels.size()) {
					levelCounter = 0;
				}
				levels[levelCounter]->SetPlayer(player);
			}
			// if escaped is pressed go back in to the menu
			if (input->KeyPress(GLFW_KEY_ESCAPE)) {
				gameState = _menu;
			}
			break;
		case _menu:
			menu->Update(window->GetDeltaTime());
			// If start is pressed start the game
			if (menu->Start()) {
				gameState = _game;
			}
			else if (menu->Restart()) {
				// TODO: restart level
			}
			else if (menu->Quit()) {
				// exit the application
				window->CloseWindow();
			}
			break;
		}
		
		// Update the box2D world by the deltaTime
		world->Step(window->GetDeltaTime(), 8, 3);
		// Swap buffers
		window->SwapBuffers();
	}
	delete menu;
	delete player;
	delete level1;
	delete level2;
	delete contactListener;
	delete window;
	std::cout << "Program succeeded" << std::endl;
	return 0;
}