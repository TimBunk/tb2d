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
#include "box2Dclasses/b2entity.h"
#include "button.h"
#include "renderManager.h"
#include "core.h"

#include <ft2build.h>
#include FT_FREETYPE_H

float B2Entity::m2p = 50.0f;
float B2Entity::p2m = 1.0f / B2Entity::m2p;

Core* core;

Scene* scene1;
const int amount = 10000;
Sprite* sprite[amount];
const int amount2 = 5;
Sprite* sprite2[amount2];
const int amount3 = 5;
Sprite* sprite3[amount3];

float scale = 1.0f;

int main() {
	std::cout << "hello world" << std::endl;

	core = new Core("testScene", false);
	core->ResizeWindow(800, 800);
	core->SetWindowBackgroundColor(glm::vec3(1, 1, 0));

	ResourceManager::CreateTexture("crate", "textures/container2.png", TextureWrap::repeat, TextureFilter::linear, MipmapFilter::linear_mipmap_linear);
	ResourceManager::CreateTexture("crate2", "textures/container.jpg", TextureWrap::repeat, TextureFilter::linear, MipmapFilter::linear_mipmap_linear);
	ResourceManager::CreateTexture("crate3", "textures/wall.jpg", TextureWrap::repeat, TextureFilter::linear, MipmapFilter::linear_mipmap_linear);

	scene1 = new Scene(800, 800);
	for (int i = 0; i < amount; i++) {
		sprite[i] = new Sprite(100, 100, ResourceManager::GetTexture("crate3")->GetId());
		sprite[i]->localPosition = glm::vec2((std::rand() % 400) * -1, std::rand() % 800 - 400);
		scene1->AddChild(sprite[i]);
	}

	for (int i = 0; i < amount2; i++) {
		sprite2[i] = new Sprite(100, 100, 0);
		sprite2[i]->localPosition = glm::vec2(std::rand() % 400, std::rand() % 800 - 400);
		sprite2[i]->SetColor(glm::vec4(std::rand() / double(RAND_MAX), std::rand() / double(RAND_MAX), std::rand() / double(RAND_MAX), 1.0f));
		scene1->AddChild(sprite2[i]);
	}

	for (int i = 0; i < amount3; i++) {
		sprite3[i] = new Sprite(100, 100, ResourceManager::GetTexture("crate")->GetId());
		sprite3[i]->localPosition = glm::vec2(std::rand() % 800 - 400, std::rand() % 800 - 400);
		sprite3[i]->SetColor(glm::vec4(1, 0, 0, 1));
		scene1->AddChild(sprite3[i]);
	}

	sprite3[0]->SetPivot(glm::vec2(-0.5f, -0.5f));
	sprite3[1]->SetRepeatableUV(glm::vec2(2, 2));

	while (core->IsActive()) {

		core->Run(scene1);

		if (Input::KeyPress(GLFW_KEY_ESCAPE)) {
			core->Close();
		}
		/*if (Input::KeyDown(GLFW_KEY_UP)) {
			scale += core->GetDeltaTime() / 2;
			scene1->GetCamera()->SetScale(scale);
		}
		else if (Input::KeyDown(GLFW_KEY_DOWN)) {
			scale -= core->GetDeltaTime() / 2;
			scene1->GetCamera()->SetScale(scale);
		}*/
		if (Input::KeyDown(GLFW_KEY_DOWN)) {
			scene1->GetCamera()->PositionAdd(glm::vec2(0.0f, -100.0f * core->GetDeltaTime()));
		}
		if (Input::KeyDown(GLFW_KEY_UP)) {
			scene1->GetCamera()->PositionAdd(glm::vec2(0.0f, 100.0f * core->GetDeltaTime()));
		}
		if (Input::KeyDown(GLFW_KEY_LEFT)) {
			scene1->GetCamera()->PositionAdd(glm::vec2(-100.0f * core->GetDeltaTime(), 0.0f));
		}
		if (Input::KeyDown(GLFW_KEY_RIGHT)) {
			scene1->GetCamera()->PositionAdd(glm::vec2(100.0f * core->GetDeltaTime(), 0.0f));
		}
	}


	for (int i = 0; i < amount; i++) {
		delete sprite[i];
	}
	for (int i = 0; i < amount2; i++) {
		delete sprite2[i];
	}
	for (int i = 0; i < amount3; i++) {
		delete sprite3[i];
	}
	delete scene1;
	delete core;
	std::cout << "Program succeeded" << std::endl;
	return 0;
}