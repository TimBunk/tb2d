#include "level1.h"

Level1::Level1(b2World* world, ResourceManager* rm, Input* input, Camera* camera) : Scene::Scene(camera){
	this->rm = rm;
	this->input = input;
	this->world = world;
	currentRoom = 0;
	player = new Player(input, camera, rm, rm->GetShader("shader"), this->world);
	player->GiveTexture(rm->GetTexture("player"));
	player->CreateBody(this->camera->screenWidth/2, this->camera->screenHeight/2, 50, 75, true, false, this->world);
	wall = new Wall(this->camera, this->rm->GetShader("shader"), true);
	wall->GiveTexture(this->rm->GetTexture("wall"));
	wall->CreateBody(150, 0, 300, 74, false, this->world);
	wall2 = new Wall(this->camera, this->rm->GetShader("shader"), true);
	wall2->GiveTexture(this->rm->GetTexture("wall"));
	wall2->CreateBody(650, 0, 300, 74, false, this->world);
	wall3 = new Wall(this->camera, this->rm->GetShader("shader"), false);
	wall3->CreateBody(-37, this->camera->screenHeight/2, 74, 74 + this->camera->screenHeight, false, this->world);
	wall4 = new Wall(this->camera, this->rm->GetShader("shader"), false);
	wall4->CreateBody(this->camera->screenWidth/2, this->camera->screenHeight + 74, this->camera->screenWidth + 148, 74, false, this->world);
	wall5 = new Wall(this->camera, this->rm->GetShader("shader"), false);
	wall5->CreateBody(this->camera->screenWidth + 37, this->camera->screenHeight/2, 74, 74 + this->camera->screenHeight, false, this->world);
	wall6 = new Wall(this->camera, this->rm->GetShader("shader"), false);
	wall6->CreateBody(150, -170, 300, 260, false, this->world);
	wall7 = new Wall(this->camera, this->rm->GetShader("shader"), false);
	wall7->CreateBody(650, -170, 300, 260, false, this->world);
	wall8 = new Wall(this->camera, this->rm->GetShader("shader"), true);
	wall8->GiveTexture(this->rm->GetTexture("wall"));
	wall8->CreateBody(this->camera->screenWidth/2, -537, this->camera->screenWidth, 74, false, this->world);
	floor = new Renderable(this->camera, this->rm->GetShader("shader"));
	floor->GiveTexture(this->rm->GetTexture("floorDetailed"));
	floor->CreateBody(this->camera->screenWidth/2, this->camera->screenHeight/2 + 37, this->camera->screenWidth, this->camera->screenHeight, this->camera->screenWidth, this->camera->screenHeight);
	floor2 = new Renderable(this->camera, this->rm->GetShader("shader"));
	floor2->GiveTexture(this->rm->GetTexture("floorStandard"));
	floor2->CreateBody(this->camera->screenWidth/2, -400, this->camera->screenWidth, 200, this->camera->screenWidth, 200);
	stair1 = new Renderable(this->camera, this->rm->GetShader("shader"));
	stair1->GiveTexture(this->rm->GetTexture("stairs"));
	stair1->CreateBody(this->camera->screenWidth/2, -200 + 37, 200, 400, 200, 400);
	door = new Door(this->camera, this->rm->GetShader("shader"), 1);
	door->CreateBody(this->camera->screenWidth - 25, -400, Direction::east, 200.0f, this->world);
	door->GiveTexture(this->rm->GetTexture("doorEast"));
	door2 = new Door(this->camera, this->rm->GetShader("shader"), 1);
	door2->CreateBody(0 + 25, -400, Direction::west, 200.0f, this->world);
	door2->GiveTexture(this->rm->GetTexture("doorWest"));
	healthPotion1 = new HealthPotion(1, this->camera, this->rm->GetShader("shader"));
	healthPotion1->CreateBody(450, 150, 30, 36, false, true, this->world);
	healthPotion1->GiveTexture(this->rm->GetTexture("healthPotion"));
	damagePotion1 = new DamagePotion(1.0f, 5.0f, this->camera, this->rm->GetShader("shader"));
	damagePotion1->CreateBody(100, 300, 30, 36, false, true, this->world);
	damagePotion1->GiveTexture(this->rm->GetTexture("damagePotion"));
	speedPotion1 = new SpeedPotion(2.0f, -0.15f, 4.0f, this->camera, this->rm->GetShader("shader"));
	speedPotion1->CreateBody(150, 300, 30, 36, false, true, this->world);
	speedPotion1->GiveTexture(this->rm->GetTexture("speedPotion"));
	crate1 = new Crate(this->camera, this->rm->GetShader("shader"));
	crate1->CreateBody(450, 150, 50, 60, false, false, this->world);
	crate1->GiveTexture(this->rm->GetTexture("crate"));
	crate1->Store(healthPotion1);
	lootChest1 = new LootChest(100, this->player, camera, this->rm->GetShader("shader"), this->rm->GetShader("text"));
	lootChest1->CreateBody(400, 500, 75, 75, false, false, this->world);
	lootChest1->GiveTexture(this->rm->GetTexture("goldLootChestClosed"), this->rm->GetTexture("goldLootChestOpened"));
	babyOrc1 = new BabyOrc(this->player, 350.0f, this->rm->GetTexture("orcWeapon"), this->camera, this->rm->GetShader("shader"), this->rm->GetShader("debugRenderer"), this->world);
	babyOrc1->CreateBody(400, -300, 50, 50);
	babyOrc1->GiveTexture(this->rm->GetTexture("babyOrc"));
	/*psychoOrc1 = new PsychoOrc(this->player, 350.0f, this->rm->GetTexture("psychoOrcWeapon"), this->camera, this->rm->GetShader("shader"), this->rm->GetShader("debugRenderer"), this->world);
	psychoOrc1->CreateBody(500, 500, 50, 62);
	psychoOrc1->GiveTexture(this->rm->GetTexture("psychoOrc"));
	orc1 = new Orc(this->player, 350.0f, this->rm->GetTexture("orcWeapon"), this->camera, this->rm->GetShader("shader"), this->rm->GetShader("debugRenderer"), this->world);
	orc1->CreateBody(500, 500, 50, 75);
	orc1->GiveTexture(this->rm->GetTexture("orc"));
	armoredOrc1 = new ArmoredOrc(this->player, 350.0f, this->rm->GetTexture("orcWeapon"), this->camera, this->rm->GetShader("shader"), this->rm->GetShader("debugRenderer"), this->world);
	armoredOrc1->CreateBody(500, 500, 50, 75);
	armoredOrc1->GiveTexture(this->rm->GetTexture("armoredOrc"));*/
	necromancerOrc1 = new NecromancerOrc(1.5f, this->rm, this->player, 250.0f, this->camera, rm->GetShader("shader"), this->rm->GetShader("debugRenderer"), this->world);
	necromancerOrc1->CreateBody(555, 500, 50, 75);
	necromancerOrc1->GiveTexture(this->rm->GetTexture("necromancerOrc"));

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
	room1->AddChild(damagePotion1);
	room1->AddChild(speedPotion1);
	room1->AddChild(lootChest1);
	room1->AddChild(babyOrc1);
	//room1->AddChild(psychoOrc1);
	//room1->AddChild(orc1);
	//room1->AddChild(armoredOrc1);
	room1->AddChild(necromancerOrc1);
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
	delete damagePotion1;
	delete speedPotion1;
	delete lootChest1;
	delete babyOrc1;
	/*delete psychoOrc1;
	delete orc1;
	delete armoredOrc1;*/
	delete necromancerOrc1;
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
		damagePotion1->Reset();
		speedPotion1->Reset();
		babyOrc1->Reset();
		//psychoOrc1->Reset();
		//orc1->Reset();
		//armoredOrc1->Reset();
		necromancerOrc1->Reset();
	}
	this->UpdateChilderen(this, deltaTime);
}
