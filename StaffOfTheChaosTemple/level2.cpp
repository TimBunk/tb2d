#include "level2.h"

Level2::Level2(b2World * world, int screenWidthCamera, int screenHeightCamera) : Level::Level(world, screenWidthCamera, screenHeightCamera)
{
	CreateFinish(10000, 540, 400, 100);
	wall = new B2Entity(camera, world);
	wall->SetTexture(ResourceManager::GetTexture("wall"));
	wall->CreateBodyBox(450, 450, 2000, 50, glm::vec2(0, 0), false, false, true);
	this->AddChild(wall);
}

Level2::~Level2()
{
	delete enemy;
	//delete enemy1;
	delete enemy2;
	delete wall;
}

void Level2::SetPlayer(Player * player)
{
	this->player = player;
	this->player->localPosition = glm::vec2(480.0f, 100.0f);
	// We need to update the player otherwise the position will not be set because of the player using velocity and the velocity overrride it's position
	this->player->UpdateChilderen(this, 0.0f);
	this->player->SetCamera(camera);

	enemy = new Enemy(player, 900.0f, 1, 5, 1, camera, world);
	enemy->CreateBodyBox(0, -300, 100, 100, glm::vec2(0, 0), true, false, true);
	//enemy->CreateBodyCircle(0, 0, 50, true, false, true);
	enemy->SetTexture(ResourceManager::GetTexture("enemy"));
	enemy->EnableDebugRendering(glm::vec3(0, 1, 0));
	this->AddChild(enemy);

	/*enemy1 = new Enemy(player, 900.0f, 1, 5, 1, camera, world);
	enemy1->CreateBodyBox(150, -300, 100, 100, glm::vec2(0, 0), true, false, true);
	//enemy->CreateBodyCircle(0, 0, 50, true, false, true);
	enemy1->SetTexture(ResourceManager::GetTexture("enemy"));
	enemy1->EnableDebugRendering(glm::vec3(0, 1, 0));
	this->AddChild(enemy1);*/

	enemy2 = new Enemy(player, 1400.0f, 1, 5, 1, camera, world);
	enemy2->CreateBodyBox(800, -300, 100, 100, glm::vec2(0, 0), true, false, true);
	//enemy->CreateBodyCircle(0, 0, 50, true, false, true);
	enemy2->SetTexture(ResourceManager::GetTexture("enemy"));
	enemy2->EnableDebugRendering(glm::vec3(0, 1, 0));
	this->AddChild(enemy2);
}
