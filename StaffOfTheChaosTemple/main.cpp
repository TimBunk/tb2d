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
#include "button.h"
#include "b2entity.h"
#include "player.h"
#include "level1.h"
#include "mirror.h"
#include "rotator.h"

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

Rotator* rotator;

Sprite* parent;
Sprite* child;

float B2Entity::m2p = 50.0f;
float B2Entity::p2m = 1.0f / B2Entity::m2p;

int main() {
	std::cout << "hello world" << std::endl;
	window = new Window("Staff of the Chaos Temple", true);
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

	contactListener = new ContactListener();
	world = new b2World(b2Vec2(0.0f, 0.0f));
	world->SetContactListener(contactListener);
	world->SetAllowSleeping(false);

	level1 = new Level1(1920, 1080);

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

	player = new Player(input, rm, level1->GetCamera(), rm->GetShader("defaultShader"), world);
	player->CreateBody(960, 0, 100, 100, glm::vec2(0.0f, 0.0f), true, false, false);
	player->GiveTexture(rm->GetTexture("player"));

	wall = new B2Entity(level1->GetCamera(), rm->GetShader("defaultShader"), world);
	wall->CreateBody(960, 1080, 1920, 100, glm::vec2(0.0f, 0.0f), false, false, true);
	wall->GiveTexture(rm->GetTexture("wall"));
	level1->AddChild(wall);
	wall2 = new B2Entity(level1->GetCamera(), rm->GetShader("defaultShader"), world);
	wall2->CreateBody(0, 540, 100, 1080, glm::vec2(0.0f, 0.0f), false, false, true);
	wall2->GiveTexture(rm->GetTexture("wall"));
	level1->AddChild(wall2);
	wall3 = new B2Entity(level1->GetCamera(), rm->GetShader("defaultShader"), world);
	wall3->CreateBody(1920, 540, 100, 1080, glm::vec2(0.0f, 0.0f), false, false, true);
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

	level1->AddChild(player);

	/*level1->GetCamera()->PositionAdd(glm::vec2(500.0f, 0.0f));
	glm::vec3 scale;
	glm::quat rotation;
	glm::vec3 translation;
	glm::vec3 skew;
	glm::vec4 perspective;
	glm::decompose(level1->GetCamera()->GetViewMatrix(), scale, rotation, translation, skew, perspective);
	std::cout << "translation.x = " << translation.x << std::endl;*/

	while (!window->ShouldClose()) {
		// rendering commands
		window->Clear();
		window->Update();

		level1->Update(window->GetDeltaTime());
		
		world->Step(window->GetDeltaTime(), 8, 3);
		window->SwapBuffers();
	}
	//delete parent;
	//delete child;
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