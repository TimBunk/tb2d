#include "level1.h"

Level1::Level1(b2World* world, ResourceManager* rm, Input* input, Camera* camera) : Scene::Scene(camera){
	this->rm = rm;
	this->input = input;
	this->world = world;
	player = new Player(input, camera, rm->GetShader("shader"));
	player->GiveTexture(rm->GetTexture("player"));
	player->CreateBody(Configure::screenWidth/2, Configure::screenHeight/2, 100, 100, true, world);
	this->AddChild(player);
	wall = new Wall(camera, rm->GetShader("shader"), true);
	wall->GiveTexture(rm->GetTexture("wall"));
	wall->CreateBody(Configure::screenWidth/2, 25, Configure::screenWidth, 50, false, world);
	this->AddChild(wall);
	wall2 = new Wall(camera, rm->GetShader("shader"), false);
	wall2->CreateBody(0, 25, 50, Configure::screenHeight, false, world);
	this->AddChild(wall2);
}

Level1::~Level1() {
	this->RemoveChild(player);
	delete player;
	this->RemoveChild(wall);
	delete wall;
	this->RemoveChild(wall2);
	delete wall2;
}

void Level1::Update() {
	CalculateDeltaTime();
	this->UpdateChilderen(this, deltaTime);
	player->Draw();
	wall->Draw();
}
