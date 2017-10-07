#include "level1.h"

Level1::Level1(b2World* world, ResourceManager* rm, Input* input, Camera* camera) : Scene::Scene(camera){
	this->rm = rm;
	this->input = input;
	this->world = world;
	player = new Player(input, camera, rm->GetShader("shader"), rm->GetTexture("playerHand"), world);
	player->GiveTexture(rm->GetTexture("player"));
	player->CreateBody(camera->screenWidth/2, camera->screenHeight/2, 50, 75, true, world);
	this->AddChild(player);
	wall = new Wall(camera, rm->GetShader("shader"), true);
	wall->GiveTexture(rm->GetTexture("wall"));
	wall->CreateBody(camera->screenWidth/2, 37, camera->screenWidth, 75, false, world);
	this->AddChild(wall);
	wall2 = new Wall(camera, rm->GetShader("shader"), false);
	wall2->CreateBody(-25, camera->screenHeight/2 + 38, 50, camera->screenHeight, false, world);
	this->AddChild(wall2);
	floor = new Floor(camera, rm->GetShader("shader"));
	floor->GiveTexture(rm->GetTexture("floor"));
	floor->CreateBody(camera->screenWidth/2, camera->screenHeight/2 + 38, camera->screenWidth, camera->screenHeight, camera->screenWidth, camera->screenHeight);
	this->AddChild(floor);
}

Level1::~Level1() {
	this->RemoveChild(player);
	delete player;
	this->RemoveChild(wall);
	delete wall;
	this->RemoveChild(wall2);
	delete wall2;
	this->RemoveChild(floor);
	delete floor;
}

void Level1::Update() {
	CalculateDeltaTime();
	floor->Draw();
	player->Draw();
	wall->Draw();
	this->UpdateChilderen(this, deltaTime);
}
