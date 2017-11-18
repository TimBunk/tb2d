#include <iostream>
#include <string>

#include <gl\glew.h>
#include <glfw3.h>
#include <glm-0.9.8.4\glm\glm.hpp>
#include <glm-0.9.8.4\glm\gtc\matrix_transform.hpp>
#include <glm-0.9.8.4\glm\gtc\type_ptr.hpp>

#include "resourceManager.h"
#include "sprite.h"
#include "text.h"
#include "scene.h"

#include <ft2build.h>
#include FT_FREETYPE_H

ResourceManager* rm;
Texture* texture;
Shader* shaderFreetype;
Shader* shader;
Scene* scene;
Sprite* sprite;

Text* text;


int main() {
	std::cout << "hello world" << std::endl;

	// initialize and configure glfw
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	// glfw window creation
	GLFWwindow* window = glfwCreateWindow(800, 600, "testProject", NULL, NULL);
	if (window == NULL) {
		std::cout << "glfw window creation failed!" << std::endl;
		glfwTerminate();
	}
	glfwMakeContextCurrent(window);

	// set this to true so glew knows to use a modern approache to retrieving function pointers and extensions
	glewExperimental = GL_TRUE;

	// initialize glew
	if (GLEW_OK != glewInit()) {
		std::cout << "Error in initializing glew" << std::endl;
		glfwTerminate();
	}

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


	rm = new ResourceManager();
	rm->CreateTexture("awesome", "textures/awesomeface.png", TextureWrap::repeat, TextureFilter::linear, TextureType::diffuse);

	scene = new Scene(1920, 1080);
	sprite = new Sprite(250, 250, rm->GetTexture("awesome"), rm->GetShader("defaultHUD"), scene->GetCamera(), true);
	sprite->localPosition = glm::vec2(125.0f, 125.0f);
	scene->AddChild(sprite);
	text = new Text("This is sample text", 96, "fonts/OpenSans-Regular.ttf", glm::vec3(0.5f, 0.8f, 0.2f), rm->GetShader("defaultFreetype"), scene->GetCamera(), false);
	text->localPosition = glm::vec2(960.0f, 540.0f);
	scene->AddChild(text);


	while (!glfwWindowShouldClose(window)) {
		// rendering commands
		glClearColor(0, 0.5, 0.5, 1);
		glClear(GL_COLOR_BUFFER_BIT);

		// Draw the texture on the screen
		scene->UpdateChilderen(NULL, 0.0f);

		// if escaped is pressed exit the program
		if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
			glfwSetWindowShouldClose(window, true);
		}
		if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
			scene->GetCamera()->PositionAdd(glm::vec2(0.0f, -0.1f));
		}
			
		// check/call events and swap the buffers
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	delete text;
	delete scene;
	delete sprite;
	delete rm;
	glfwDestroyWindow(window);
	glfwTerminate();
	std::cout << "Program succeeded" << std::endl;
	return 0;
}