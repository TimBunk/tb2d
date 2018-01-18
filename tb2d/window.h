/**
* @file window.h
*
* @brief The Window header file.
*/

#ifndef WINDOW_H
#define WINDOW_H

#include <iostream>
#include <vector>

#include <GL/glew.h>
#include <glfw3.h>

#include "input.h"

/**
* @brief The Window class
*/
class Window {
public:
	/// @brief Constructor of the Window
	/// @param screenName is the name of the window
	/// @param fullScreen specifies if the window should be in fullscreen or not
	Window(const char* screenName, bool fullScreen);
	/// @brief Destructor of the Window
	~Window();

	/// @brief Clear clears all of the currently rendered pixels of the screen
	/// @return void
	void Clear();
	/// @brief SwapBuffers swap the buffers of the window
	/// @return void
	void SwapBuffers();
	/// @brief ShouldClose return a int that specifies wheter the window shoud close or not
	/// @return int
	int ShouldClose();
	/// @brief CloseWindow closes the window
	/// @return void
	void CloseWindow();
	/// @brief Resize resizes the window
	/// @param screenWidth is the new width of the window
	/// @param screenHeight is the new height of the window
	/// @return void
	void Resize(int screenWidth, int screenHeight);
	/// @brief SetBackgroundColor sets the background color of the window
	/// @param backgroundColor is the new background color of the window
	/// @return void
	void SetBackgroundColor(glm::vec3 backgroundColor);

private:

	GLFWwindow* window; ///< @brief window is the GLFWwindow
	glm::vec3 backgroundColor; ///< @brief backgroundColor is the background color of this window
};

#endif // !WINDOW_H
