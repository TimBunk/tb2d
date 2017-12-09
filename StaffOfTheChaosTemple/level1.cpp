#include "level1.h"

Level1::Level1(b2World* world, int screenWidthCamera, int screenHeightCamera) : Level::Level(world, screenWidthCamera, screenHeightCamera)
{
	// Set the finish
	CreateFinish(960, 1200, 480, 100);

	// Intialize all of the variables
	wall = new B2Entity(camera, world);
	wall->CreateBodyBox(360, 1080, 720, 100, glm::vec2(0.0f, 0.0f), false, false, true);
	wall->GiveTexture(ResourceManager::GetTexture("wall"));
	AddChild(wall);
	wall2 = new B2Entity(camera, world);
	wall2->CreateBodyBox(0, 540, 100, 1080, glm::vec2(0.0f, 0.0f), false, false, true);
	wall2->GiveTexture(ResourceManager::GetTexture("wall"));
	AddChild(wall2);
	wall3 = new B2Entity(camera, world);
	wall3->CreateBodyBox(1920, 540, 100, 1080, glm::vec2(0.0f, 0.0f), false, false, true);
	wall3->GiveTexture(ResourceManager::GetTexture("wall"));
	AddChild(wall3);
	wall4 = new B2Entity(camera, world);
	wall4->CreateBodyBox(960, 0, 1920, 100, glm::vec2(0.0f, 0.0f), false, false, true);
	wall4->GiveTexture(ResourceManager::GetTexture("wall"));
	AddChild(wall4);
	wall5 = new B2Entity(camera, world);
	wall5->CreateBodyBox(1530, 540, 700, 100, glm::vec2(0.0f, 0.0f), false, false, true);
	wall5->GiveTexture(ResourceManager::GetTexture("wall"));
	AddChild(wall5);
	wall6 = new B2Entity(camera, world);
	wall6->CreateBodyBox(1560, 1080, 720, 100, glm::vec2(0.0f, 0.0f), false, false, true);
	wall6->GiveTexture(ResourceManager::GetTexture("wall"));
	AddChild(wall6);

	mirror = new Mirror(true, camera, world);
	mirror->localPosition = glm::vec2(700.0f, 540.0f);
	mirror->SetRotation(-90.0f);
	mirror->GiveTexture(ResourceManager::GetTexture("laser"));
	AddChild(mirror);

	crystal = new Crystal(camera, world);
	crystal->CreateBodyBox(1530, 270, 70, 70, glm::vec2(0, 0), false, false, true);
	crystal->GiveTexture(ResourceManager::GetTexture("crystal"));
	crystal->SetShader(ResourceManager::GetShader("crystal"));
	AddChild(crystal);
	crystal2 = new Crystal(camera, world);
	crystal2->CreateBodyBox(1530, 810, 70, 70, glm::vec2(0, 0), false, false, true);
	crystal2->GiveTexture(ResourceManager::GetTexture("crystal"));
	crystal2->SetShader(ResourceManager::GetShader("crystal"));
	AddChild(crystal2);

	door = new Door(Direction::west, camera, world);
	door->CreateBodyBox(840, 1080, 240, 100, glm::vec2(0, 0), false, false, true);
	door->GiveTexture(ResourceManager::GetTexture("player"));
	door->Link(crystal);
	door->Link(crystal2);
	AddChild(door);
	door2 = new Door(Direction::east, camera, world);
	door2->CreateBodyBox(1080, 1080, 240, 100, glm::vec2(0, 0), false, false, true);
	door2->GiveTexture(ResourceManager::GetTexture("player"));
	door2->Link(door);
	AddChild(door2);
}

Level1::~Level1()
{
	delete wall;
	delete wall2;
	delete wall3;
	delete wall4;
	delete wall5;
	delete door;
	delete door2;
	delete crystal;
	delete crystal2;
	delete mirror;
}

void Level1::SetPlayer(Player * player)
{
	this->player = player;
	this->player->localPosition = glm::vec2(1000.0f, 100.0f);
	// We need to update the player otherwise the position will not be set because of the player using velocity and the velocity overrride it's position
	this->player->UpdateChilderen(this, 0.0f);
	this->player->SetCamera(camera);
}
