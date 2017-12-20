#include "level2.h"

Level2::Level2(int screenWidthCamera, int screenHeightCamera) : Level::Level(screenWidthCamera, screenHeightCamera)
{
	this->player->localPosition = glm::vec2(480.0f, 100.0f);
	// We need to update the player otherwise the position will not be set because of the player using velocity and the velocity overrride it's position
	this->player->UpdateChilderen(this, 0.0f);

	enemy = new Enemy(player, 900.0f, 0.1f, 0.5f, 1, 5, 1, 70, 70, nullptr, camera, world);
	enemy->localPosition = glm::vec2(0, -300);
	enemy->SetInstancedRenderer("enemy");
	enemy->CreateBoxCollider(70, 70, glm::vec2(0, 0), true, false);
	enemy->EnableDebugRendering(glm::vec3(1, 0, 1));
	enemy->UpdateChilderen(this, 0.0f);
	this->AddChild(enemy);

	enemy1 = new Enemy(player, 900.0f, 0.1f, 0.5f, 1, 5, 1, 70, 70, nullptr, camera, world);
	enemy1->localPosition = glm::vec2(1, -300);
	enemy1->SetInstancedRenderer("enemy");
	enemy1->CreateBoxCollider(70, 70, glm::vec2(0, 0), true, false);
	enemy1->EnableDebugRendering(glm::vec3(0, 1, 0));
	enemy1->UpdateChilderen(this, 0.0f);
	this->AddChild(enemy1);

	enemy2 = new Enemy(player, 900.0f, 0.1f, 0.5f, 1, 5, 1, 70, 70, nullptr, camera, world);
	enemy2->localPosition = glm::vec2(800, -300);
	enemy2->SetInstancedRenderer("enemy");
	enemy2->CreateBoxCollider(70, 70, glm::vec2(0, 0), true, false);
	enemy2->EnableDebugRendering(glm::vec3(0, 1, 0));
	enemy2->UpdateChilderen(this, 0.0f);
	this->AddChild(enemy2);

	wall = new B2Entity(720, 750, glm::vec2(0, 0), nullptr, camera, world);
	wall->localPosition = glm::vec2(450, 450);
	wall->SetInstancedRenderer("wall");
	wall->CreateBoxCollider(720, 100, glm::vec2(0, 0), false, false);
	AddChild(wall);

	mirror = new Mirror(true, 45.0f, 240.0f, nullptr, camera, world);
	mirror->localPosition = glm::vec2(700.0f, 1000.0f);
	mirror->SetInstancedRenderer("mirror");
	mirror->CreateBoxCollider(45.0f, 240.0f, glm::vec2(0.0f, 0.0f), false, false);
	mirror->SetRotation(-90.0f);
	AddChild(mirror);

	CreateFinish(10000, 540, 400, 100);
}

Level2::~Level2()
{
	if (player != nullptr) {
		delete enemy;
		delete enemy1;
		delete enemy2;
	}
	delete wall;
	delete mirror;
}