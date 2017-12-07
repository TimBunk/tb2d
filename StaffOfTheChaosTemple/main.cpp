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

ContactListener* contactListener;
b2World* world;
Player* player;
B2Entity* wall;
B2Entity* wall2;
B2Entity* wall3;
Mirror* mirror;
Mirror* mirror2;
Mirror* mirror3;

Crystal* crystal;
Crystal* crystal2;
Door* door;
Door* door2;

Menu* menu;

float B2Entity::m2p = 50.0f;
float B2Entity::p2m = 1.0f / B2Entity::m2p;

enum GameState
{
	_game,
	_menu
};

GameState gameState;

int main() {
	std::cout << "hello world" << std::endl;
	window = new Window("Staff of the Chaos Temple", false);
	window->Resize(800, 600);

	rm = window->GetResourceManager();
	rm->CreateTexture("awesome", "textures/awesomeface.png", TextureWrap::repeat, TextureFilter::linear, TextureType::diffuse);
	rm->CreateTexture("player", "textures/container.jpg", TextureWrap::repeat, TextureFilter::linear, TextureType::diffuse);
	rm->CreateTexture("wall", "textures/wall.jpg", TextureWrap::repeat, TextureFilter::linear, TextureType::diffuse);
	rm->CreateTexture("staff", "textures/matrix.jpg", TextureWrap::repeat, TextureFilter::linear, TextureType::diffuse);
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

	player = new Player(input, rm, 10, 10.0f, 1, level1->GetCamera(), rm->GetShader("defaultShader"), world);
	player->CreateBodyBox(960, 0, 100, 100, glm::vec2(0.0f, 0.0f), true, false, false);
	player->GiveTexture(rm->GetTexture("player"));
	level1->SetFinish(player, 960, -200, 400, 100);

	/*parent = new Sprite(rm->GetTexture("player"), rm->GetShader("defaultShader"), level1->GetCamera(), false);
	parent->CreateBody(300, 300, glm::vec2(0.0f, 0.0f));
	parent->localPosition = glm::vec2(960.0f, 540.0f);
	parent->localAngle = glm::radians(90.0f);
	level1->AddChild(parent);

	child = new Sprite(rm->GetTexture("awesome"), rm->GetShader("defaultShader"), level1->GetCamera(), false);
	child->CreateBody(150, 150, glm::vec2(0.0f, 0.0f));
	child->localPosition = glm::vec2(300.0f, 300.0f);
	child->localAngle = glm::radians(90.0f);
	parent->AddChild(child);*/

	wall = new B2Entity(level1->GetCamera(), rm->GetShader("defaultShader"), world);
	wall->CreateBodyBox(960, 1080, 1920, 100, glm::vec2(0.0f, 0.0f), false, false, true);
	wall->GiveTexture(rm->GetTexture("wall"));
	level1->AddChild(wall);
	wall2 = new B2Entity(level1->GetCamera(), rm->GetShader("defaultShader"), world);
	wall2->CreateBodyBox(0, 540, 100, 1080, glm::vec2(0.0f, 0.0f), false, false, true);
	wall2->GiveTexture(rm->GetTexture("wall"));
	level1->AddChild(wall2);
	wall3 = new B2Entity(level1->GetCamera(), rm->GetShader("defaultShader"), world);
	wall3->CreateBodyBox(1920, 540, 100, 1080, glm::vec2(0.0f, 0.0f), false, false, true);
	wall3->GiveTexture(rm->GetTexture("wall"));
	level1->AddChild(wall3);

	mirror = new Mirror(true, rm, level1->GetCamera(), rm->GetShader("defaultShader"), world);
	mirror->localPosition = glm::vec2(960.0f, 540.0f);
	mirror->GiveTexture(rm->GetTexture("laser"));
	level1->AddChild(mirror);

	mirror2 = new Mirror(true, rm, level1->GetCamera(), rm->GetShader("defaultShader"), world);
	mirror2->localPosition = glm::vec2(1440.0f, 700.0f);
	mirror2->SetRotation(-90.0f);
	mirror2->GiveTexture(rm->GetTexture("laser"));
	level1->AddChild(mirror2);

	mirror3 = new Mirror(true, rm, level1->GetCamera(), rm->GetShader("defaultShader"), world);
	mirror3->localPosition = glm::vec2(1440.0f, 380.0f);
	mirror3->SetRotation(90.0f);
	mirror3->GiveTexture(rm->GetTexture("laser"));
	level1->AddChild(mirror3);

	crystal = new Crystal(level1->GetCamera(), rm->GetShader("crystal"), world);
	crystal->CreateBodyBox(1400, 540, 70, 70, glm::vec2(0, 0), false, false, true);
	crystal->GiveTexture(rm->GetTexture("crystal"));
	level1->AddChild(crystal);

	crystal2 = new Crystal(level1->GetCamera(), rm->GetShader("crystal"), world);
	crystal2->CreateBodyBox(1300, 640, 70, 70, glm::vec2(0, 0), false, false, true);
	crystal2->GiveTexture(rm->GetTexture("crystal"));
	level1->AddChild(crystal2);

	door = new Door(Direction::west, level1->GetCamera(), rm->GetShader("defaultShader"), world);
	door->CreateBodyBox(960, 900, 100, 50, glm::vec2(0, 0), false, false, true);
	door->GiveTexture(rm->GetTexture("player"));
	door->Link(crystal);
	door->Link(crystal2);
	level1->AddChild(door);

	door2 = new Door(Direction::east, level1->GetCamera(), rm->GetShader("defaultShader"), world);
	door2->CreateBodyBox(1060, 900, 100, 50, glm::vec2(0, 0), false, false, true);
	door2->GiveTexture(rm->GetTexture("player"));
	door2->Link(crystal);
	door2->Link(crystal2);
	level1->AddChild(door2);

	level1->AddChild(player);

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
			level1->Update(window->GetDeltaTime());
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
	delete door;
	delete door2;
	delete crystal;
	delete crystal2;
	delete mirror;
	delete mirror2;
	delete mirror3;
	delete wall;
	delete wall2;
	delete wall3;
	delete player;
	delete level1;
	delete contactListener;
	delete window;
	std::cout << "Program succeeded" << std::endl;
	return 0;
}