#include "level1.h"

Level1::Level1(b2World* world, int screenWidthCamera, int screenHeightCamera, ResourceManager* rm) : Level::Level(world, screenWidthCamera, screenHeightCamera, rm)
{
	CreateFinish(960, -200, 400, 100);
}

Level1::~Level1()
{
}

void Level1::SetPlayer(Player * player)
{
	this->player = player;
	this->player->localPosition = glm::vec2(2000.0f, 0.0f);
	// We need to update the player otherwise the position will not be set because of the player using velocity and the velocity overrride it's position
	this->player->UpdateChilderen(this, 0.0f);
	this->player->SetCamera(camera);
}
