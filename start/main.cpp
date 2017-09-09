#define GLEW_STATIC
#define _USE_MATH_DEFINES

#include <iostream>
#include <string>
#include <math.h>
#include <vector>

#include "shader.h"
#include "box.h"
#include "circle.h"
#include "texture.h"
#include "scene.h"
#include "camera.h"

#include <gl\glew.h>
#include <glfw3.h>
#include <glm-0.9.8.4\glm\glm.hpp>
#include <glm-0.9.8.4\glm\gtc\matrix_transform.hpp>
#include <glm-0.9.8.4\glm\gtc\type_ptr.hpp>
#include <Box2D\Box2D.h>

const float screenWidth = 800, screenHeight = 600;
b2World* world;
const float m2p = 50;
const float p2m = 1 / m2p;
std::vector<Box*> boxes;

double mouseX;
double mouseY;

Shader* shader;
glm::mat4 projection;
Camera* cam;

void FrameBufferSizeCallback(GLFWwindow* window, int width, int height);
void ProcessInput(GLFWwindow* window);

float deltaTime = 0.0f;
float _deltaTime = 0.0f;
float lastFrame = 0.0f;
float totalTime = 0.0f;
int fpsCount = 0;
float fps = 1.0f / 60.0f;
bool loop = true;
void CalculateFrameRate();

void MouseCallback(GLFWwindow * window, double xPos, double yPos);
void ScrollCallback(GLFWwindow* window, double xOffset, double yOffset);

int main() {
	// initialize and configure glfw
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	// glfw window creation
	GLFWwindow* window = glfwCreateWindow(screenWidth, screenHeight, "tbfw", NULL, NULL);
	if (window == NULL) {
		std::cout << "glfw window creation failed!" << std::endl;
		glfwTerminate();
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, FrameBufferSizeCallback);

	// set this to true so glew knows to use a modern approache to retrieving function pointers and extensions
	glewExperimental = GL_TRUE;

	// initialize glew
	if (GLEW_OK != glewInit()) {
		std::cout << "Error in initializing glew" << std::endl;
		glfwTerminate();
	}

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glfwSetCursorPosCallback(window, MouseCallback);
	glfwSetScrollCallback(window, ScrollCallback);








	world = new b2World(b2Vec2(0.0f, 9.91f));

	projection = glm::ortho(0.0f, screenWidth, screenHeight, 0.0f, -50.0f, 50.0f);

	shader = new Shader("shaders//shader.vs", "shaders//shader.fs");

	cam = new Camera(screenWidth, screenHeight);

	shader->Use();
	//shader->SetVec4Float("color", glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));
	shader->SetMatrix4("projection", projection);

	Texture texture = Tex::LoadTexture("textures/container.jpg", TextureWrap::repeat, TextureFilter::linear, TextureType::diffuse);
	glActiveTexture(GL_TEXTURE0 + texture.index);
	shader->SetInt("ourTexture", texture.id);
	glBindTexture(GL_TEXTURE_2D, texture.id);
	glActiveTexture(GL_TEXTURE0);

	Texture texture2 = Tex::LoadTexture("textures/awesomeface.png", TextureWrap::repeat, TextureFilter::linear, TextureType::diffuse);
	glActiveTexture(GL_TEXTURE0 + texture2.index);
	shader->SetInt("ourTexture", texture2.id);
	glBindTexture(GL_TEXTURE_2D, texture2.id);
	glActiveTexture(GL_TEXTURE0);

	Box* ground;
	ground = new Box(screenWidth / 2, screenHeight, screenWidth, 30, false, p2m, world, projection);

	Circle* circle;
	circle = new Circle(400, 0, 50, true, p2m, world, projection);

	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	// render/update loop
	while (!glfwWindowShouldClose(window)) {
		if (loop) {
			// input
			ProcessInput(window);

			// rendering commands
			glClearColor(0, 0.5, 0.5, 1);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			
			// draw the boxes
			shader->Use();

			glActiveTexture(GL_TEXTURE0 + texture2.index);
			shader->SetInt("ourTexture", texture2.id);
			glBindTexture(GL_TEXTURE_2D, texture2.id);
			glActiveTexture(GL_TEXTURE0);

			shader->Use();
			circle->Draw(cam->GetViewMatrix(), shader, m2p);
			for (int i = 0; i < boxes.size(); i++) {
				shader->Use();
				boxes[i]->Draw(cam->GetViewMatrix(), shader, m2p);
			}
			// draw the ground
			shader->Use();
			glActiveTexture(GL_TEXTURE0 + texture.index);
			shader->SetInt("ourTexture", texture.id);
			glBindTexture(GL_TEXTURE_2D, texture.id);
			glActiveTexture(GL_TEXTURE0);

			ground->Draw(cam->GetViewMatrix(), shader, m2p);

			// update box2D world
			world->Step(1.0f/60.0f, 8, 3);

			// reset the deltaTime
			deltaTime = 0;

			// check/call events and swap the buffers
			glfwSwapBuffers(window);
			glfwPollEvents();
		}
		// calculate the frameRate
		CalculateFrameRate();
	}
	delete ground;
	delete shader;
	delete circle;
	delete cam;
	while (boxes.size() > 0) {
		int i = boxes.size() - 1;
		delete boxes[i];
		boxes.pop_back();
	}
	// clear all allocated glfw resources
	glfwDestroyWindow(window);
	glfwTerminate();
	std::cout << "Program succeeded" << std::endl;
	return 0;
}

void FrameBufferSizeCallback(GLFWwindow * window, int width, int height)
{
	// this makes sure the screen width/height always fits even if the window is resized
	glViewport(0, 0, width, height);
}

void ProcessInput(GLFWwindow * window)
{
	// if escaped is pressed exit the program
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	}
	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
		
	}
	else if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
		
	}
	if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS) {
		cam->AngleAdd(1.0f);
	}
	else if (glfwGetKey(window, GLFW_KEY_R) == GLFW_RELEASE) {
		
	}
	if (glfwGetKey(window, GLFW_KEY_T) == GLFW_PRESS) {
		Box* box;
		box = new Box(mouseX, mouseY, 50, 50, true, p2m, world, projection);
		boxes.push_back(box);
	}
	else if (glfwGetKey(window, GLFW_KEY_T) == GLFW_RELEASE) {
		//AddRect(mouseX, mouseY, 20, 20, true);
	}

	float speed = 2.0f*deltaTime;
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
		glm::vec2 pos;
		pos = glm::vec2(0.0f, -3.0f);
		cam->PositionAdd(pos);
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
		glm::vec2 pos;
		pos = glm::vec2(0.0f, 3.0f);
		cam->PositionAdd(pos);
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
		glm::vec2 pos;
		pos = glm::vec2(-3.0f, 0.0f);
		cam->PositionAdd(pos);
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
		glm::vec2 pos;
		pos = glm::vec2(3.0f, 0.0f);
		cam->PositionAdd(pos);
	}
}

void CalculateFrameRate()
{
	float currentFrame = glfwGetTime();
	_deltaTime = currentFrame - lastFrame;
	lastFrame = currentFrame;

	deltaTime += _deltaTime;

	totalTime += _deltaTime;
	if (totalTime - fpsCount * fps >= fps) {
		fpsCount++;
		loop = true;
	}
	else {
		loop = false;
	}
	if (totalTime >= 1.0f) {
		totalTime -= 1.0f;
		std::cout << "fps: " << fpsCount << std::endl;
		fpsCount = 0;
	}
}

void MouseCallback(GLFWwindow * window, double xPos, double yPos)
{
	mouseX = xPos;
	mouseY = yPos;
}

void ScrollCallback(GLFWwindow * window, double xOffset, double yOffset)
{
	
}
