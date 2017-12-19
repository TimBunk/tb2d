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
const int amount2 = 10000;
Sprite* sprite2[amount2];

float scale = 1.0f;

int main() {
	std::cout << "hello world" << std::endl;

	core = new Core("testScene", false);
	core->ResizeWindow(800, 800);
	core->SetWindowBackgroundColor(glm::vec3(1, 1, 0));

	ResourceManager::CreateTexture("crate", "textures/container2.png", TextureWrap::repeat, TextureFilter::linear, TextureType::diffuse);
	ResourceManager::CreateTexture("crate2", "textures/container.jpg", TextureWrap::repeat, TextureFilter::linear, TextureType::diffuse);
	ResourceManager::CreateShader("defaultShaderInstancing", "shaders\\defaultShaderInstancing.vs", "shaders\\defaultShader.fs");

	scene1 = new Scene(800, 800);
	for (int i = 0; i < amount; i++) {
		sprite[i] = new Sprite(20, 20, glm::vec2(0, 0), ResourceManager::GetTexture("crate"), scene1->GetCamera(), false);
		sprite[i]->SetShader(ResourceManager::GetShader("defaultShaderInstancing"));
		sprite[i]->SetInstancedRenderer("crate");
		sprite[i]->localPosition = glm::vec2((std::rand() % 400) * -1, std::rand() % 800 - 400);
		//std::cout << "sprite[" << i << "]->localPosition.x = " << sprite[i]->localPosition.x << " .y = " << sprite[i]->localPosition.y << std::endl;
		scene1->AddChild(sprite[i]);
	}
	for (int i = 0; i < amount2; i++) {
		sprite2[i] = new Sprite(20, 20, glm::vec2(0, 0), ResourceManager::GetTexture("crate2"), scene1->GetCamera(), false);
		sprite2[i]->SetShader(ResourceManager::GetShader("defaultShaderInstancing"));
		sprite2[i]->SetInstancedRenderer("crate2");
		sprite2[i]->localPosition = glm::vec2(std::rand() % 400, std::rand() % 800 - 400);
		//std::cout << "sprite[" << i << "]->localPosition.x = " << sprite[i]->localPosition.x << " .y = " << sprite[i]->localPosition.y << std::endl;
		scene1->AddChild(sprite2[i]);
	}

	while (core->IsActive()) {

		core->Run(scene1);

		if (Input::KeyPress(GLFW_KEY_ESCAPE)) {
			core->Close();
		}
		if (Input::KeyDown(GLFW_KEY_UP)) {
			scale += core->GetDeltaTime() / 2;
			scene1->GetCamera()->SetScale(scale);
		}
		else if (Input::KeyDown(GLFW_KEY_DOWN)) {
			scale -= core->GetDeltaTime() / 2;
			scene1->GetCamera()->SetScale(scale);
		}
	}


	for (int i = 0; i < amount; i++) {
		delete sprite[i];
	}
	for (int i = 0; i < amount2; i++) {
		delete sprite2[i];
	}
	delete scene1;
	delete core;
	std::cout << "Program succeeded" << std::endl;
	return 0;
}