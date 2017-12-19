#ifndef CORE_H
#define CORE_H

#include "window.h"
#include "renderManager.h"
#include "resourceManager.h"
#include "scene.h"

class Core
{
public:
	Core(const char* screenName, bool fullscreen);
	~Core();

	void Run(Scene* scene);
	bool IsActive();
	void Close();
	double GetDeltaTime();

	void ResizeWindow(int width, int height);
	void SetWindowBackgroundColor(glm::vec3 color);

private:
	void CalculateFrameRate();
	Window* window;

	// deltaTime
	double deltaTime;
	double lastFrame;
	double totalTime;
	int fpsCount;
};

#endif // !CORE_H
