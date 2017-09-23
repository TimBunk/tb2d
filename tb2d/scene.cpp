#include "scene.h"

Scene::Scene() : Entity::Entity() {
	deltaTime = 0.0f;
	lastFrame = 0.0f;
	totalTime = 0.0f;
	printFPS = true;
	std::cout << "totalTime: " << totalTime << std::endl;
	fpsCount = 0;
}

Scene::~Scene()
{

}

void Scene::CalculateDeltaTime()
{
	/*float currentFrame = glfwGetTime();
	deltaTime = currentFrame - lastFrame;
	lastFrame = currentFrame;
	std::cout << "deltaTime: " << deltaTime << std::endl;

	if (printFPS && totalTime < 1.0f) {
		totalTime += deltaTime;
		fpsCount++;
	}
	else if (totalTime >= 1.0f) {
		totalTime += deltaTime;
		fpsCount++;

		totalTime -= 1.0f;
		std::cout << "fps: " << fpsCount << std::endl;
		fpsCount = 0;
	}*/
}
