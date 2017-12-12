#include "level2.h"

Level2::Level2(b2World * world, int screenWidthCamera, int screenHeightCamera) : Level::Level(world, screenWidthCamera, screenHeightCamera)
{
	CreateFinish(10000, 540, 400, 100);
	wall = new B2Entity(2000, 50, glm::vec2(0, 0), ResourceManager::GetTexture("wall"), camera, world);
	wall->localPosition = glm::vec2(450, 450);
	wall->CreateBoxCollider(2000, 50, glm::vec2(0, 0), false, false);
	this->AddChild(wall);
}

Level2::~Level2()
{
	/*delete enemy;
	delete enemy1;
	delete enemy2;*/
	delete wall;
}

void Level2::SetPlayer(Player * player)
{
	this->player = player;
	this->player->localPosition = glm::vec2(480.0f, 100.0f);
	// We need to update the player otherwise the position will not be set because of the player using velocity and the velocity overrride it's position
	this->player->UpdateChilderen(this, 0.0f);
	this->player->SetCamera(camera);

	enemy = new Enemy(player, 900.0f, 0.1f, 0.5f, 1, 5, 1, 100, 100, ResourceManager::GetTexture("enemy"), camera, world);
	enemy->localPosition = glm::vec2(0, -300);
	enemy->CreateBoxCollider(100, 100, glm::vec2(0, 0), true, false);
	enemy->EnableDebugRendering(glm::vec3(0, 1, 0));
	this->AddChild(enemy);

	enemy1 = new Enemy(player, 900.0f, 0.1f, 0.5f, 1, 5, 1, 100, 100, ResourceManager::GetTexture("enemy"), camera, world);
	enemy1->localPosition = glm::vec2(400, -300);
	enemy1->CreateBoxCollider(100, 100, glm::vec2(0, 0), true, false);
	enemy1->EnableDebugRendering(glm::vec3(0, 1, 0));
	this->AddChild(enemy1);

	enemy2 = new Enemy(player, 900.0f, 0.1f, 0.5f, 1, 5, 1, 100, 100, ResourceManager::GetTexture("enemy"), camera, world);
	enemy2->localPosition = glm::vec2(800, -300);
	enemy2->CreateBoxCollider(100, 100, glm::vec2(0, 0), true, false);
	enemy2->EnableDebugRendering(glm::vec3(0, 1, 0));
	this->AddChild(enemy2);
}
