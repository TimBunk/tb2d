#include "level2.h"

Level2::Level2(b2World * world, int screenWidthCamera, int screenHeightCamera) : Level::Level(world, screenWidthCamera, screenHeightCamera)
{
	CreateFinish(10000, 540, 400, 100);
	wall = new B2Entity(720, 750, glm::vec2(0, 0), ResourceManager::GetTexture("wall"), camera, world);
	wall->localPosition = glm::vec2(450, 450);
	wall->CreateBoxCollider(720, 100, glm::vec2(0, 0), false, false);
	AddChild(wall);

	mirror = new Mirror(true, 45.0f, 240.0f, ResourceManager::GetTexture("mirror"), camera, world);
	mirror->localPosition = glm::vec2(700.0f, 1000.0f);
	mirror->CreateBoxCollider(45.0f, 240.0f, glm::vec2(0.0f, 0.0f), false, false);
	mirror->SetRotation(-90.0f);
	AddChild(mirror);
}

Level2::~Level2()
{
	delete enemy;
	delete enemy1;
	delete enemy2;
	delete wall;
	delete mirror;
}

void Level2::SetPlayer(Player * player)
{
	this->player = player;
	this->player->localPosition = glm::vec2(480.0f, 100.0f);
	// We need to update the player otherwise the position will not be set because of the player using velocity and the velocity overrride it's position
	this->player->UpdateChilderen(this, 0.0f);
	this->player->SetCamera(camera);

	/*enemy = new Enemy(player, 900.0f, 0.1f, 0.5f, 1, 5, 1, 70, 70, ResourceManager::GetTexture("enemy"), camera, world);
	enemy->localPosition = glm::vec2(0, -300);
	enemy->CreateBoxCollider(70, 70, glm::vec2(0, 0), true, false);
	enemy->EnableDebugRendering(glm::vec3(1, 0, 1));
	enemy->UpdateChilderen(this, 0.0f);
	this->AddChild(enemy);

	enemy1 = new Enemy(player, 900.0f, 0.1f, 0.5f, 1, 5, 1, 70, 70, ResourceManager::GetTexture("enemy"), camera, world);
	enemy1->localPosition = glm::vec2(1, -300);
	enemy1->CreateBoxCollider(70, 70, glm::vec2(0, 0), true, false);
	enemy1->EnableDebugRendering(glm::vec3(0, 1, 0));
	enemy1->UpdateChilderen(this, 0.0f);
	this->AddChild(enemy1);

	enemy2 = new Enemy(player, 900.0f, 0.1f, 0.5f, 1, 5, 1, 70, 70, ResourceManager::GetTexture("enemy"), camera, world);
	enemy2->localPosition = glm::vec2(800, -300);
	enemy2->CreateBoxCollider(70, 70, glm::vec2(0, 0), true, false);
	enemy2->EnableDebugRendering(glm::vec3(0, 1, 0));
	enemy2->UpdateChilderen(this, 0.0f);
	this->AddChild(enemy2);*/
}
