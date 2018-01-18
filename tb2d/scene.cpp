#include "scene.h"

Scene::Scene(int screenWidthCamera, int screenHeightCamera) : Entity::Entity() {
	// Create the camera
	camera = new Camera(screenWidthCamera, screenHeightCamera);
}

Scene::~Scene()
{
	// Delete the camera
	delete camera;
}