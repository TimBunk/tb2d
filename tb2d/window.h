#ifndef WINDOW_H
#define WINDOW_H

#define _USE_MATH_DEFINES

#include <iostream>
#include <string>
#include <math.h>
#include <vector>

#include <GL/glew.h>
#include <glfw3.h>

#include "input.h"

class Window {
public:
	Window(const char* screenName, bool fullScreen);
	virtual ~Window();

	void Clear();
	void SwapBuffers();
	int ShouldClose();
	void CloseWindow();
	void Resize(int screenWidth, int screenHeight);

	void SetBackgroundColor(glm::vec3 backgroundColor);

private:

	GLFWwindow* window;
	glm::vec3 backgroundColor;
};

#endif // !WINDOW_H
