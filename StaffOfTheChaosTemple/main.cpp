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

#include <ft2build.h>
#include FT_FREETYPE_H

Window* window;
ResourceManager* rm;
Input* input;

Texture* texture;

Scene* scene;
b2World* world;
Player* player;
B2Entity* wall;
B2Entity* wall2;
B2Entity* wall3;
B2Entity* wall4;
B2Entity* wall5;
float angle;
RaycastCallBack* raycast;

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

	rm->CreateShader("debug", "shaders\\debugRenderer.vs", "shaders\\debugRenderer.fs");

	input = window->GetInput();
	window->SetBackgroundColor(glm::vec3(0.0f, 0.4f, 0.8f));

	scene = new Scene(1920, 1080);
	world = new b2World(b2Vec2(0.0f, 0.0f));
	wall = new B2Entity(scene->GetCamera(), rm->GetShader("defaultShader"), world);
	wall->CreateBody(960, 1080, 1920, 100, false, false);
	wall->GiveTexture(rm->GetTexture("wall"));
	scene->AddChild(wall);
	wall2 = new B2Entity(scene->GetCamera(), rm->GetShader("defaultShader"), world);
	wall2->CreateBody(0, 540, 100, 1080, false, false);
	wall2->GiveTexture(rm->GetTexture("wall"));
	scene->AddChild(wall2);
	wall3 = new B2Entity(scene->GetCamera(), rm->GetShader("defaultShader"), world);
	wall3->CreateBody(1920, 540, 100, 1080, false, false);
	wall3->GiveTexture(rm->GetTexture("wall"));
	scene->AddChild(wall3);
	wall4 = new B2Entity(scene->GetCamera(), rm->GetShader("defaultShader"), world);
	wall4->CreateBody(960, 0, 1920, 100, false, false);
	wall4->GiveTexture(rm->GetTexture("wall"));
	scene->AddChild(wall4);

	angle = 0.0f;
	wall5 = new B2Entity(scene->GetCamera(), rm->GetShader("defaultShader"), world);
	wall5->CreateBody(960, 0, 1920, 100, false, false);
	wall5->GiveTexture(rm->GetTexture("wall"));
	scene->AddChild(wall5);

	player = new Player(input, rm, scene->GetCamera(), rm->GetShader("defaultShader"), world);
	player->CreateBody(960, 540, 250, 250, true, false);
	player->GiveTexture(rm->GetTexture("player"));
	scene->AddChild(player);

	raycast = new RaycastCallBack();
	raycast->CreateLine(1000.0f, 25.0f, scene->GetCamera(), rm->GetShader("debug"), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));

	while (!window->ShouldClose()) {
		// rendering commands
		window->Clear();
		window->Update();

		scene->UpdateChilderen(scene, 0.0f);
		
		angle += (2.5f * window->GetDeltaTime());
		wall5->localAngle = glm::radians(angle);
		/*if (input->KeyDown(GLFW_KEY_SPACE)) {
			raycast->Draw(glm::vec2(960.0f, 540.0f), glm::atan(2000.0f, 0.0f));
			world->RayCast(raycast, b2Vec2(960.0f * B2Entity::p2m, 540.0f * B2Entity::p2m), b2Vec2(960.0f * B2Entity::p2m, -1000.0f * B2Entity::p2m));
			RaycastOutput ro = raycast->GetOutput();
			if (ro.fixture != nullptr && static_cast<Player*>(ro.fixture->GetUserData()) != NULL) {
				std::cout << "hit is true and the fraction = " << ro.fraction << std::endl;
			}
		}
		*/
		world->Step(window->GetDeltaTime(), 8, 3);
		window->SwapBuffers();
	}
	delete wall;
	delete wall2;
	delete wall3;
	delete wall4;
	delete wall5;
	delete raycast;
	delete player;
	delete scene;
	delete window;
	std::cout << "Program succeeded" << std::endl;
	return 0;
}