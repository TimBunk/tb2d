#include "level1.h"

Level1::Level1(b2World* world, ResourceManager* rm, Input* input, Camera* camera) : Scene::Scene(camera){
	this->rm = rm;
	this->input = input;
	this->world = world;
	currentRoom = 0;
	player = new Player(input, camera, rm, rm->GetShader("shader"), world);
	player->GiveTexture(rm->GetTexture("player"));
	player->CreateBody(camera->screenWidth/2, camera->screenHeight/2, 50, 75, true, false, world);
	wall = new Wall(camera, rm->GetShader("shader"), true);
	wall->GiveTexture(rm->GetTexture("wall"));
	wall->CreateBody(150, 0, 300, 74, false, world);
	wall2 = new Wall(camera, rm->GetShader("shader"), true);
	wall2->GiveTexture(rm->GetTexture("wall"));
	wall2->CreateBody(650, 0, 300, 74, false, world);
	wall3 = new Wall(camera, rm->GetShader("shader"), false);
	wall3->CreateBody(-37, camera->screenHeight/2, 74, 74 + camera->screenHeight, false, world);
	wall4 = new Wall(camera, rm->GetShader("shader"), false);
	wall4->CreateBody(camera->screenWidth/2, camera->screenHeight + 74, camera->screenWidth + 148, 74, false, world);
	wall5 = new Wall(camera, rm->GetShader("shader"), false);
	wall5->CreateBody(camera->screenWidth + 37, camera->screenHeight/2, 74, 74 + camera->screenHeight, false, world);
	wall6 = new Wall(camera, rm->GetShader("shader"), false);
	wall6->CreateBody(150, -170, 300, 260, false, world);
	wall7 = new Wall(camera, rm->GetShader("shader"), false);
	wall7->CreateBody(650, -170, 300, 260, false, world);
	wall8 = new Wall(camera, rm->GetShader("shader"), true);
	wall8->GiveTexture(rm->GetTexture("wall"));
	wall8->CreateBody(camera->screenWidth/2, -537, camera->screenWidth, 74, false, world);
	floor = new Renderable(camera, rm->GetShader("shader"));
	floor->GiveTexture(rm->GetTexture("floorDetailed"));
	floor->CreateBody(camera->screenWidth/2, camera->screenHeight/2 + 37, camera->screenWidth, camera->screenHeight, camera->screenWidth, camera->screenHeight);
	floor2 = new Renderable(camera, rm->GetShader("shader"));
	floor2->GiveTexture(rm->GetTexture("floorStandard"));
	floor2->CreateBody(camera->screenWidth/2, -400, camera->screenWidth, 200, camera->screenWidth, 200);
	stair1 = new Renderable(camera, rm->GetShader("shader"));
	stair1->GiveTexture(rm->GetTexture("stairs"));
	stair1->CreateBody(camera->screenWidth/2, -200 + 37, 200, 400, 200, 400);
	door = new Door(camera, rm->GetShader("shader"), 1);
	door->CreateBody(camera->screenWidth - 25, -400, Direction::east, 200.0f, world);
	door->GiveTexture(rm->GetTexture("doorEast"));
	door2 = new Door(camera, rm->GetShader("shader"), 1);
	door2->CreateBody(0 + 25, -400, Direction::west, 200.0f, world);
	door2->GiveTexture(rm->GetTexture("doorWest"));
	healthPotion1 = new HealthPotion(1, camera, rm->GetShader("shader"));
	healthPotion1->CreateBody(450, 150, 30, 36, false, true, world);
	healthPotion1->GiveTexture(rm->GetTexture("healthPotion"));
	crate1 = new Crate(camera, rm->GetShader("shader"));
	crate1->CreateBody(450, 150, 50, 60, false, false, world);
	crate1->GiveTexture(rm->GetTexture("crate"));
	crate1->Store(healthPotion1);
	lootChest1 = new LootChest(100, player, camera, rm->GetShader("shader"), rm->GetShader("text"));
	lootChest1->CreateBody(400, 500, 75, 75, false, false, world);
	lootChest1->GiveTexture(rm->GetTexture("goldLootChestClosed"), rm->GetTexture("goldLootChestOpened"));

	currentRoom = 0;
	room1 = new Room(camera);
	this->AddChild(room1);
	room1->AddChild(floor);
	room1->AddChild(floor2);
	room1->AddChild(stair1);
	room1->AddChild(wall);
	room1->AddChild(wall2);
	room1->AddChild(wall3);
	room1->AddChild(wall4);
	room1->AddChild(wall5);
	room1->AddChild(wall6);
	room1->AddChild(wall7);
	room1->AddChild(wall8);
	room1->AddChild(door);
	room1->AddChild(door2);
	room1->AddChild(crate1);
	room1->AddChild(healthPotion1);
	room1->AddChild(lootChest1);
	room1->SetActive(true);
	rooms.push_back(room1);

	room2 = new Room(camera);
	this->AddChild(room2);
	room2->SetActive(false);
	rooms.push_back(room2);

	this->AddChild(player);
}

Level1::~Level1() {
	delete player;
	delete wall;
	delete wall2;
	delete room1;
	delete floor;
	delete floor2;
	delete door;
	delete door2;
	delete room2;
	delete wall3;
	delete wall4;
	delete wall5;
	delete wall6;
	delete wall7;
	delete wall8;
	delete stair1;
	delete crate1;
	delete healthPotion1;
	delete lootChest1;
}

void Level1::Update(float deltaTime) {
	// Check in which room the player is located, if the player is in a new room then load the new room
	int playerRoom = player->GetRoom();
	if (playerRoom != currentRoom) {
		rooms[currentRoom]->SetActive(false);
		this->RemoveChild(rooms[currentRoom]);
		currentRoom = playerRoom;
		rooms[currentRoom]->SetActive(true);
		this->AddChild(rooms[currentRoom]);
	}
	// RESET
	if (input->KeyPress(SDL_SCANCODE_R)) {
		crate1->Reset();
	}
	this->UpdateChilderen(this, deltaTime);
}
