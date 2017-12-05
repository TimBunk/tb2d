#include "level1.h"

Level1::Level1(b2World* world, int screenWidthCamera, int screenHeightCamera, ResourceManager* rm) : Scene::Scene(screenWidthCamera, screenHeightCamera, rm)
{
	finish = new B2Entity(camera, rm->GetShader("defaultShader"), world);
}

Level1::~Level1()
{
	delete finish;
}

void Level1::Update(double deltaTime)
{
	this->UpdateChilderen(this, deltaTime);
	if (finish->Contact(player)) {
		std::cout << "FINISH" << std::endl;
	}
}

void Level1::SetFinish(Player * player, int x, int y, int width, int height)
{
	this->player = player;
	this->player->SetCamera(camera);
	finish->CreateBody(x, y, width, height, glm::vec2(0, 0), false, true, true);
	finish->EnableDebugRendering(glm::vec3(0.0f, 1.0f, 0.0f));
	this->AddChild(finish);
}
