#include "scene.h"

Scene::Scene(Camera* camera) : Entity::Entity() {
	this->camera = camera;
}

Scene::~Scene()
{

}

void Scene::Update(double deltaTime) {
	this->UpdateChilderen(this, deltaTime);
}
