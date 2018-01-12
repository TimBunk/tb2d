/*#include "level2.h"

Level2::Level2(int screenWidthCamera, int screenHeightCamera) : Level::Level(screenWidthCamera, screenHeightCamera)
{
	this->player->localPosition = glm::vec2(480.0f, 100.0f);
	// We need to update the player otherwise the position will not be set because of the player using velocity and the velocity overrride it's position
	this->player->UpdateChilderen(this, 0.0f);

	enemy = new Enemy(player, 3000.0f, 0.6f, 0.5f, 300.0f, 6.0f, 150.0f, 70, 70, ResourceManager::GetTexture("enemy")->GetId(), world);
	enemy->localPosition = glm::vec2(0, -300);
	enemy->CreateBoxCollider(70, 70, glm::vec2(0, 0), true, false);
	enemy->SetDebugColor(glm::vec3(1, 0, 1));
	enemy->UpdateChilderen(this, 0.0f);
	AddChild(enemy);
	AddEnemy(enemy);

	wall = new B2Entity(3840, 750, ResourceManager::GetTexture("wall")->GetId(), world);
	wall->localPosition = glm::vec2(450, 990);
	wall->CreateBoxCollider(3840, 100, glm::vec2(0, 0), false, false);
	AddChild(wall);

	wall2 = new B2Entity(2160, 750, ResourceManager::GetTexture("wall")->GetId(), world);
	wall2->localAngle = glm::radians(90.0f);
	wall2->localPosition = glm::vec2(-1470, -165);
	wall2->CreateBoxCollider(2160, 100, glm::vec2(0, 0), false, false);
	AddChild(wall2);

	wall3 = new B2Entity(3840, 750, ResourceManager::GetTexture("wall")->GetId(), world);
	wall3->localPosition = glm::vec2(450, -1170);
	wall3->CreateBoxCollider(3840, 100, glm::vec2(0, 0), false, false);
	AddChild(wall3);

	wall4 = new B2Entity(2160, 750, ResourceManager::GetTexture("wall")->GetId(), world);
	wall4->localAngle = glm::radians(90.0f);
	wall4->localPosition = glm::vec2(2370, -165);
	wall4->CreateBoxCollider(2160, 100, glm::vec2(0, 0), false, false);
	AddChild(wall4);

	door1 = new Door(Direction::west, 550, 550, ResourceManager::GetTexture("door")->GetId(), world);
	door1->localPosition = glm::vec2(175, 990);
	door1->CreateBoxCollider(550, 100, glm::vec2(0, 0), false, false);
	door1->Link(enemy);
	AddChild(door1);
	door2 = new Door(Direction::east, 550, 550, ResourceManager::GetTexture("door")->GetId(), world);
	door2->localPosition = glm::vec2(725, 990);
	door2->localAngle = glm::radians(180.0f);
	door2->CreateBoxCollider(550, 100, glm::vec2(0, 0), false, false);
	door2->Link(door1);
	AddChild(door2);

	mirror = new Mirror(true, 45.0f, 240.0f, ResourceManager::GetTexture("mirror")->GetId(), world);
	mirror->localPosition = glm::vec2(700.0f, 750.0f);
	mirror->CreateBoxCollider(45.0f, 240.0f, glm::vec2(0.0f, 0.0f), false, false);
	mirror->SetRotation(-90.0f);
	AddChild(mirror);

	mirror2 = new Mirror(true, 45.0f, 240.0f, ResourceManager::GetTexture("mirror")->GetId(), world);
	mirror2->localPosition = glm::vec2(100.0f, 325.0f);
	mirror2->CreateBoxCollider(45.0f, 240.0f, glm::vec2(0.0f, 0.0f), false, false);
	mirror2->SetRotation(-90.0f);
	AddChild(mirror2);

	mirror3 = new Mirror(true, 45.0f, 240.0f, ResourceManager::GetTexture("mirror")->GetId(), world);
	mirror3->localPosition = glm::vec2(1300.0f, 325.0f);
	mirror3->CreateBoxCollider(45.0f, 240.0f, glm::vec2(0.0f, 0.0f), false, false);
	mirror3->SetRotation(-90.0f);
	AddChild(mirror3);

	CreateFinish(10000, 540, 400, 100);
}

Level2::~Level2()
{
	delete wall;
	delete wall2;
	delete wall3;
	delete wall4;
	delete door1;
	delete door2;
	delete mirror;
	delete mirror2;
	delete mirror3;
}
*/