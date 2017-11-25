#include <iostream>
#include <string>

#include <gl\glew.h>
#include <glfw3.h>
#include <glm-0.9.8.4\glm\glm.hpp>
#include <glm-0.9.8.4\glm\gtc\matrix_transform.hpp>
#include <glm-0.9.8.4\glm\gtc\type_ptr.hpp>

#include "window.h"
#include "sprite.h"
#include "scene.h"
#include "button.h"
#include "b2entity.h"
#include "player.h"
#include "level1.h"

#include <ft2build.h>
#include FT_FREETYPE_H

Window* window;
ResourceManager* rm;
Input* input;

Texture* texture;

Level1* level1;

b2World* world;
Player* player;
B2Entity* wall;
B2Entity* wall2;
B2Entity* wall3;

float B2Entity::m2p = 50.0f;
float B2Entity::p2m = 1.0f / B2Entity::m2p;

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

	rm->CreateShader("debug", "shaders\\debugRenderer.vs", "shaders\\debugRenderer.fs");

	input = window->GetInput();
	window->SetBackgroundColor(glm::vec3(0.0f, 0.4f, 0.8f));

	world = new b2World(b2Vec2(0.0f, 0.0f));

	level1 = new Level1(1920, 1080);

	player = new Player(input, rm, level1->GetCamera(), rm->GetShader("defaultShader"), world);
	player->CreateBody(960, 540, 250, 250, true, false);
	player->GiveTexture(rm->GetTexture("player"));

	wall = new B2Entity(level1->GetCamera(), rm->GetShader("defaultShader"), world);
	wall->CreateBody(960, 1080, 1920, 100, false, false);
	wall->GiveTexture(rm->GetTexture("wall"));
	level1->AddChild(wall);
	wall2 = new B2Entity(level1->GetCamera(), rm->GetShader("defaultShader"), world);
	wall2->CreateBody(0, 540, 100, 1080, false, false);
	wall2->GiveTexture(rm->GetTexture("wall"));
	level1->AddChild(wall2);
	wall3 = new B2Entity(level1->GetCamera(), rm->GetShader("defaultShader"), world);
	wall3->CreateBody(1920, 540, 100, 1080, false, false);
	wall3->GiveTexture(rm->GetTexture("wall"));
	level1->AddChild(wall3);

	level1->AddChild(player);

	while (!window->ShouldClose()) {
		// rendering commands
		window->Clear();
		window->Update();

		level1->Update(window->GetDeltaTime());
		
		world->Step(window->GetDeltaTime(), 8, 3);
		window->SwapBuffers();
	}
	delete wall;
	delete wall2;
	delete wall3;
	delete player;
	delete level1;
	delete window;
	std::cout << "Program succeeded" << std::endl;
	return 0;
}