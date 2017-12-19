#include "scene.h"

Scene::Scene(int screenWidthCamera, int screenHeightCamera) : Entity::Entity() {
	camera = new Camera(screenWidthCamera, screenHeightCamera);
}

Scene::~Scene()
{
	delete camera;
}

Camera * Scene::GetCamera()
{
	return camera;
}
