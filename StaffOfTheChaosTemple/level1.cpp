#include "level1.h"

Level1::Level1(int screenWidthCamera, int screenHeightCamera) : Scene::Scene(screenWidthCamera, screenHeightCamera)
{
	//this->player = player;
	//player->SetCamera(camera);
}

Level1::~Level1()
{

}

void Level1::Update(double deltaTime)
{
	this->UpdateChilderen(this, deltaTime);
}
