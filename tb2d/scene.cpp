#include "scene.h"

Scene::Scene(int screenWidthCamera, int screenHeightCamera, ResourceManager* rm) : Entity::Entity() {
	camera = new Camera(screenWidthCamera, screenHeightCamera);
	this->rm = rm;
}

Scene::~Scene()
{
	delete camera;
}

void Scene::Update(double deltaTime) {
	this->UpdateChilderen(this, deltaTime);
}

Camera * Scene::GetCamera()
{
	return camera;
}
