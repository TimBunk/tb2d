#ifndef INPUT_H
#define INPUT_H

#include <iostream>
#include <vector>

#include <gl\glew.h>
#include <glfw3.h>

#include "camera.h"

class Input {
public:
	Input(GLFWwindow* window, float screenWidth, float screenHeight);
	virtual ~Input();
	void Update();

	void SetScreenWidthAndHeight(float screenWidth, float screenHeight);
	void MouseCallback(GLFWwindow* window, double xpos, double ypos);

	glm::vec2 GetMousePositionScreenSpace(Camera* camera);
	glm::vec2 GetMousePositionWorldSpace(Camera* camera);
	bool MousePress(int mouse);
	bool MouseDown(int mouse);
	bool MouseUp(int mouse);

	bool KeyPress(int key);
	bool KeyDown(int key);
	bool KeyUp(int key);
private:
	void SetMouseState(int mouse);
	void SetKeyState(int key);
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
	bool quit;
};

#endif // !INPUT_H
