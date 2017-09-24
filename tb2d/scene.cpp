#include "scene.h"

Scene::Scene(Camera* camera) : Entity::Entity() {
	deltaTime = 0.0f;
	lastFrame = 0.0f;
	totalTime = 0.0f;
	fpsCount = 0;
	this->camera = camera;
}

Scene::~Scene()
{

}

void Scene::Update() {
	CalculateDeltaTime();
	this->position = glm::vec3(camera->GetPosition(), 0.0f);
	this->angle = camera->GetAngle();
	this->UpdateChilderen(this, deltaTime);
}

void Scene::CalculateDeltaTime()
{
	float currentFrame = SDL_GetTicks();
	deltaTime = ((currentFrame - lastFrame) / 1000.0f);
	lastFrame = currentFrame;
	fpsCount++;
	totalTime += deltaTime;
	if (totalTime >= 1.0f) {
		totalTime -= 1.0f;
		std::cout << "fps: " << fpsCount << std::endl;
		fpsCount = 0;
	}
}
