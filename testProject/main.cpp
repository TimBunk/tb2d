#include <iostream>
#include <string>

#include <gl\glew.h>
#include <glfw3.h>
#include <glm-0.9.8.4\glm\glm.hpp>
#include <glm-0.9.8.4\glm\gtc\matrix_transform.hpp>
#include <glm-0.9.8.4\glm\gtc\type_ptr.hpp>

#include "resourceManager.h"
#include "text.h"

#include <ft2build.h>
#include FT_FREETYPE_H

ResourceManager* rm;
Shader* shader;
Texture texture;
glm::mat4 projection;

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
	//GL_LEQUAL: Passes if the incoming depth value is less than or equal to the stored depth value.
	glDepthFunc(GL_LEQUAL);


	projection = glm::ortho(0.0f, 800.0f, 0.0f, 600.0f, -50.0f, 50.0f);
	rm = new ResourceManager();
	rm->CreateTexture("awesome", "textures/awesomeface.png", TextureWrap::repeat, TextureFilter::linear, TextureType::diffuse);
	texture = rm->GetTexture("awesome");
	rm->CreateShader("shader", "shaders\\freetype.vs", "shaders\\freetype.fs");
	shader = rm->GetShader("shader");
	shader->SetMatrix4("projection", projection);
	text = new Text("This is sample text", shader, "fonts/OpenSans-Regular.ttf", glm::vec3(0.5f, 0.8f, 0.2f));
	text->localPosition = glm::vec3(400.0f, 300.0f, 1.0f);
	text->localScale.x = 1.0f;
	text->localScale.y = 1.0f;


	while (!glfwWindowShouldClose(window)) {
		// rendering commands
		glClearColor(0, 0.5, 0.5, 1);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Draw the texture on the screen
		text->UpdateChilderen(NULL, 0.0f);
		text->Draw(projection);

		// if escaped is pressed exit the program
		if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
			glfwSetWindowShouldClose(window, true);
		}
			
		// check/call events and swap the buffers
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	delete text;
	delete rm;
	glfwDestroyWindow(window);
	glfwTerminate();
	std::cout << "Program succeeded" << std::endl;
	return 0;
}