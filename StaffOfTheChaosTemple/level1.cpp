#include "level1.h"

Level1::Level1(b2World* world, int screenWidthCamera, int screenHeightCamera, ResourceManager* rm) : Level::Level(world, screenWidthCamera, screenHeightCamera, rm)
{
	// Set the finish
	CreateFinish(960, -200, 400, 100);

	// Intialize all of the variables
	wall = new B2Entity(camera, rm->GetShader("defaultShader"), world);
	wall->CreateBodyBox(960, 1080, 1920, 100, glm::vec2(0.0f, 0.0f), false, false, true);
	wall->GiveTexture(rm->GetTexture("wall"));
	AddChild(wall);
	wall2 = new B2Entity(camera, rm->GetShader("defaultShader"), world);
	wall2->CreateBodyBox(0, 540, 100, 1080, glm::vec2(0.0f, 0.0f), false, false, true);
	wall2->GiveTexture(rm->GetTexture("wall"));
	AddChild(wall2);
	wall3 = new B2Entity(camera, rm->GetShader("defaultShader"), world);
	wall3->CreateBodyBox(1920, 540, 100, 1080, glm::vec2(0.0f, 0.0f), false, false, true);
	wall3->GiveTexture(rm->GetTexture("wall"));
	AddChild(wall3);

	mirror = new Mirror(true, rm, camera, rm->GetShader("defaultShader"), world);
	mirror->localPosition = glm::vec2(960.0f, 540.0f);
	mirror->GiveTexture(rm->GetTexture("laser"));
	AddChild(mirror);
	mirror2 = new Mirror(true, rm, camera, rm->GetShader("defaultShader"), world);
	mirror2->localPosition = glm::vec2(1440.0f, 700.0f);
	mirror2->SetRotation(-90.0f);
	mirror2->GiveTexture(rm->GetTexture("laser"));
	AddChild(mirror2);

	crystal = new Crystal(camera, rm->GetShader("crystal"), world);
	crystal->CreateBodyBox(1400, 540, 70, 70, glm::vec2(0, 0), false, false, true);
	crystal->GiveTexture(rm->GetTexture("crystal"));
	AddChild(crystal);
	crystal2 = new Crystal(camera, rm->GetShader("crystal"), world);
	crystal2->CreateBodyBox(1300, 640, 70, 70, glm::vec2(0, 0), false, false, true);
	crystal2->GiveTexture(rm->GetTexture("crystal"));
	AddChild(crystal2);

	door = new Door(Direction::west, camera, rm->GetShader("defaultShader"), world);
	door->CreateBodyBox(960, 900, 100, 50, glm::vec2(0, 0), false, false, true);
	door->GiveTexture(rm->GetTexture("player"));
	door->Link(crystal);
	door->Link(crystal2);
	AddChild(door);
	door2 = new Door(Direction::east, camera, rm->GetShader("defaultShader"), world);
	door2->CreateBodyBox(1060, 900, 100, 50, glm::vec2(0, 0), false, false, true);
	door2->GiveTexture(rm->GetTexture("player"));
	//door2->Link(door)
	door2->Link(crystal);
	door2->Link(crystal2);
	AddChild(door2);
}

Level1::~Level1()
{
	delete wall;
	delete wall2;
	delete wall3;
	delete door;
	delete door2;
	delete crystal;
	delete crystal2;
	delete mirror;
	delete mirror2;
}

void Level1::SetPlayer(Player * player)
{
	this->player = player;
	this->player->localPosition = glm::vec2(2000.0f, 0.0f);
	// We need to update the player otherwise the position will not be set because of the player using velocity and the velocity overrride it's position
	this->player->UpdateChilderen(this, 0.0f);
	this->player->SetCamera(camera);
}
