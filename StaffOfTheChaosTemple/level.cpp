#include "level.h"

Level::Level(b2World * world, int screenWidthCamera, int screenHeightCamera, ResourceManager * rm) : Scene::Scene(screenWidthCamera, screenHeightCamera, rm)
{
	this->world = world;
	finish = nullptr;
	finished = false;
	player = nullptr;
}

Level::~Level()
{
	delete finish;
}

void Level::Update(double deltaTime)
{
	this->UpdateChilderen(this, deltaTime);
	if (finish->Contact(player)) {
		std::cout << "FINISH" << std::endl;
		finished = true;
	}
}

void Level::SetPlayer(Player * player)
{
	this->player = player;
}

bool Level::IsFinished()
{
	if (finished) {
		finished = false;
		return true;
	}
	return false;
}

void Level::CreateFinish(int x, int y, int width, int height)
{
	finish = new B2Entity(camera, rm->GetShader("defaultShader"), world);
	finish->CreateBodyBox(x, y, width, height, glm::vec2(0, 0), false, true, true);
	finish->EnableDebugRendering(glm::vec3(0.0f, 1.0f, 0.0f));
	this->AddChild(finish);
}
