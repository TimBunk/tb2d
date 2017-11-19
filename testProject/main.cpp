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

#include <ft2build.h>
#include FT_FREETYPE_H

Window* window;
ResourceManager* rm;
Texture* texture;
Shader* shaderFreetype;
Shader* shader;
Scene* scene;
Sprite* sprite;
Input* input;
Button* button;

Text* text;


int main() {
	std::cout << "hello world" << std::endl;
	window = new Window("testProject", false);
	window->Resize(800, 600);

	rm = window->GetResourceManager();
	rm->CreateTexture("awesome", "textures/awesomeface.png", TextureWrap::repeat, TextureFilter::linear, TextureType::diffuse);

	scene = new Scene(1920, 1080);
	sprite = new Sprite(250, 250, rm->GetTexture("awesome"), rm->GetShader("defaultShader"), scene->GetCamera(), false);
	sprite->localPosition = glm::vec2(125.0f, 540.0f);
	scene->AddChild(sprite);
	text = new Text("This is sample text", 96, "fonts/OpenSans-Regular.ttf", glm::vec3(0.5f, 0.8f, 0.2f), rm->GetShader("defaultFreetype"), scene->GetCamera(), false);
	text->localPosition = glm::vec2(0.0f, 540.0f);
	scene->AddChild(text);

	//scene->GetCamera()->SetPosition(glm::vec2(-960.0f, -540.0f));

	input = window->GetInput();
	button = new Button(500, 100, true, glm::vec3(1.0f, 0.0f, 0.0f), input, scene->GetCamera(), rm);
	button->localPosition = glm::vec2(960, 540);
	scene->AddChild(button);
	window->SetBackgroundColor(glm::vec3(0.0f, 0.4f, 0.8f));

	while (!window->ShouldClose()) {
		// rendering commands
		window->Clear();
		window->Update();

		// Draw the texture on the screen
		scene->UpdateChilderen(NULL, 0.0f);

		if (button->Hover()) {
			button->SetColor(glm::vec3(0.0f, 1.0f, 0.0f));
		}
		else {
			button->SetColor(glm::vec3(1.0f, 0.0f, 0.0f));
		}

		if (input->KeyPress(GLFW_KEY_SPACE)) {
			//text->localPosition = glm::vec2(text->GetGlobalPosition().x, text->GetGlobalPosition().y - (text->GetHeight() / 2));
			//text->localScale = glm::vec2(0.8f, 0.8f);
			scene->GetCamera()->PositionAdd(glm::vec2(50.0f, 0.0f));
			button->CreateText("Start", 48, glm::vec3(0.0f, 0.0f, 1.0f));
		}

		window->SwapBuffers();
	}
	delete button;
	delete text;
	delete scene;
	delete sprite;
	delete window;
	std::cout << "Program succeeded" << std::endl;
	return 0;
}