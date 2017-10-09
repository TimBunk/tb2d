#include "scene.h"

Scene::Scene(Camera* camera) : Entity::Entity() {
	this->camera = camera;
}

Scene::~Scene()
{

}

void Scene::Update(float deltaTime) {
	this->UpdateChilderen(this, deltaTime);
}
