#ifndef INPUT_H
#define INPUT_H

#include <iostream>
#include <vector>

#include <gl\glew.h>
#include <glfw3.h>

#include "camera.h"

class Input {
public:
	static void Init(GLFWwindow* window, float screenWidth, float screenHeight);
	static void Destroy();

	static glm::vec2 GetMousePositionScreenSpace(Camera* camera);
	static glm::vec2 GetMousePositionWorldSpace(Camera* camera);
	static bool MousePress(int mouse);
	static bool MouseDown(int mouse);
	static bool MouseUp(int mouse);

	static bool KeyPress(int key);
	static bool KeyDown(int key);
	static bool KeyUp(int key);
private:
	static Input* GetInstance();
	Input(GLFWwindow* window, float screenWidth, float screenHeight);
	~Input();

	void MouseCallback(GLFWwindow* window, double xpos, double ypos);
	void SetMouseState(int mouse);
	void SetKeyState(int key);

	static Input* _input;
	GLFWwindow* window;
	float screenWidth;
	float screenHeight;

	glm::vec2 mousePosition;
	bool mousePressed[8];
	bool mouseDown[8];
	bool mouseUp[8];

	bool keysPressed[348];
	bool keysDown[348];
	bool keysUp[348];
};

#endif // !INPUT_H
