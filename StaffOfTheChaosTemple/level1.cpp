#include "level1.h"

Level1::Level1(b2World* world, int screenWidthCamera, int screenHeightCamera) : Level::Level(world, screenWidthCamera, screenHeightCamera)
{
	// Set the finish
	CreateFinish(960, 1200, 480, 100);

	// Intialize all of the variables
	wall = new B2Entity(720, 100, glm::vec2(0,0), ResourceManager::GetTexture("wall"), camera, world);
	wall->localPosition = glm::vec2(360, 1080);
	wall->CreateBoxCollider(720, 100, glm::vec2(0.0f, 0.0f), false, false);
	AddChild(wall);
	wall2 = new B2Entity(100, 1080, glm::vec2(0, 0), ResourceManager::GetTexture("wall"), camera, world);
	wall2->localPosition = glm::vec2(0, 540);
	wall2->CreateBoxCollider(100, 1080, glm::vec2(0.0f, 0.0f), false, false);
	AddChild(wall2);
	wall3 = new B2Entity(100, 1080, glm::vec2(0.0f, 0.0f), ResourceManager::GetTexture("wall"), camera, world);
	wall3->localPosition = glm::vec2(1920, 540);
	wall3->CreateBoxCollider(100, 1080, glm::vec2(0.0f, 0.0f), false, false);
	AddChild(wall3);
	wall4 = new B2Entity(1920, 100, glm::vec2(0.0f, 0.0f), ResourceManager::GetTexture("wall"), camera, world);
	wall4->localPosition = glm::vec2(960, 0);
	wall4->CreateBoxCollider(1920, 100, glm::vec2(0.0f, 0.0f), false, false);
	AddChild(wall4);
	wall5 = new B2Entity(700, 100, glm::vec2(0.0f, 0.0f), ResourceManager::GetTexture("wall"), camera, world);
	wall5->localPosition = glm::vec2(1530, 540);
	wall5->CreateBoxCollider(700, 100, glm::vec2(0.0f, 0.0f), false, false);
	AddChild(wall5);
	wall6 = new B2Entity(720, 100, glm::vec2(0.0f, 0.0f), ResourceManager::GetTexture("wall"), camera, world);
	wall6->localPosition = glm::vec2(1560, 1080);
	wall6->CreateBoxCollider(720, 100, glm::vec2(0.0f, 0.0f), false, false);
	AddChild(wall6);

	mirror = new Mirror(true, 45.0f, 240.0f, ResourceManager::GetTexture("laser"), camera, world);
	mirror->localPosition = glm::vec2(700.0f, 540.0f);
	mirror->CreateBoxCollider(45.0f, 240.0f, glm::vec2(0.0f, 0.0f), false, false);
	mirror->SetRotation(-90.0f);
	AddChild(mirror);

	crystal = new Crystal(70, 70, ResourceManager::GetTexture("crystal"), camera, world);
	crystal->localPosition = glm::vec2(1530, 270);
	crystal->CreateBoxCollider(70, 70, glm::vec2(0, 0), false, false);
	crystal->SetShader(ResourceManager::GetShader("crystal"));
	AddChild(crystal);
	crystal2 = new Crystal(70, 70, ResourceManager::GetTexture("crystal"), camera, world);
	crystal2->localPosition = glm::vec2(1530, 810);
	crystal2->CreateBoxCollider(70, 70, glm::vec2(0, 0), false, false);
	crystal2->SetShader(ResourceManager::GetShader("crystal"));
	AddChild(crystal2);

	door = new Door(Direction::west, 240, 100, ResourceManager::GetTexture("player"), camera, world);
	door->localPosition = glm::vec2(840, 1080);
	door->CreateBoxCollider(240, 100, glm::vec2(0, 0), false, false);
	door->Link(crystal);
	door->Link(crystal2);
	AddChild(door);
	door2 = new Door(Direction::east, 240, 100, ResourceManager::GetTexture("player"), camera, world);
	door2->localPosition = glm::vec2(1080, 1080);
	door2->CreateBoxCollider(240, 100, glm::vec2(0, 0), false, false);
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
