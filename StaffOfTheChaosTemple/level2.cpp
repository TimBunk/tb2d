#include "level2.h"

Level2::Level2(b2World * world, int screenWidthCamera, int screenHeightCamera) : Level::Level(world, screenWidthCamera, screenHeightCamera)
{
	CreateFinish(10000, 540, 400, 100);
}

Level2::~Level2()
{
}

void Level2::SetPlayer(Player * player)
{
	this->player = player;
	this->player->localPosition = glm::vec2(480.0f, 0.0f);
	// We need to update the player otherwise the position will not be set because of the player using velocity and the velocity overrride it's position
	this->player->UpdateChilderen(this, 0.0f);
	this->player->SetCamera(camera);
}
