/**
* @file core.h
*
* @brief The Core header file.
*/


#ifndef CORE_H
#define CORE_H

#include "window.h"
#include "renderManager.h"
#include "debugRenderer.h"
#include "resourceManager.h"
#include "scene.h"

/**
* @brief The Core class
*/
class Core
{
public:
	/// @brief Constructor of the Core
	/// @param screenName is the name of the window
	/// @param fullscreen is a boolean to set fullscreen active or not
	Core(const char* screenName, bool fullscreen);
	/// @brief Destructor of the Core
	~Core();

	/// @brief Run will call of the rendering functions and updates the scene and after that the childeren of the scene. Also the deltaTime will be calculated and the Input will be updated
	/// @param scene the scene you want to update
	/// @return void
	void Run(Scene* scene);
	/// @brief IsWindowActive checks if the window is still running in case the user pressed the exit button of the window
	/// @return void
	bool IsWindowActive();
	/// @brief CloseWindow closes the window
	/// @return void
	void CloseWindow();
	/// @brief GetDeltaTime returns the deltaTime. Note that you need to run a scenne every frame for the deltaTime to be calculated correctly
	/// @return double
	double GetDeltaTime();

	/// @brief ResizeWindow resizes the window by a specified width and height
	/// @param width the new width of the window
	/// @param height the new height of the window
	/// @return void
	void ResizeWindow(int width, int height);

	/// @brief SetWindowBackgroundColor sets the background color of the window
	/// @param color the new color of the windows background
	/// @return void
	void SetWindowBackgroundColor(glm::vec3 color);

private:
	/// @brief CalculateFrameRate cout the fps and calculates the deltaTime
	/// @return void
	void CalculateFrameRate();
	Window* window; ///< @brief window is the window that will be used by the Core

	double deltaTime; ///< @brief deltaTime is the time in seconds to complete the last frame
	double lastFrame; ///< @brief lastFrame was the time at the lastframe
	double totalTime; ///< @brief totalTime keeps track if a second has passed and if so cout the totalTime
	int fpsCount; ///< @brief fpsCount is the amount of fps
};

#endif // !CORE_H
