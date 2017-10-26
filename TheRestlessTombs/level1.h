#ifndef LEVEL1_H
#define LEVEL1_H

#include "scene.h"
#include "resourceManager.h"
#include "input.h"
#include "player.h"
#include "wall.h"
#include "renderable.h"
#include "room.h"
#include "door.h"
#include "crate.h"
#include "healthPotion.h"
#include "damagePotion.h"
#include "speedPotion.h"
#include "lootChest.h"
#include "bomb.h"
#include "babyOrc.h"
#include "psychoOrc.h"
#include "orc.h"
#include "armoredOrc.h"
#include "necromancerOrc.h"
#include "bomberOrc.h"
#include "bossOrc.h"
#include "gold.h"

#include <Box2D/Box2D.h>

class Level1 : public Scene {
public:
	Level1(b2World* world, ResourceManager* rm, Input* input, Camera* camera);
	~Level1();

	void Update(float deltaTime);
private:
	ResourceManager* rm;
	Input* input;
	b2World* world;

	std::vector<Room*> rooms;
	int currentRoom;

	Player* player;
	Wall* wall;
	Wall* wall2;
	Wall* wall3;
	Wall* wall4;
	Wall* wall5;
	Wall* wall6;
	Wall* wall7;
	Wall* wall8;
	Renderable* floor;
	Renderable* floor2;
	Renderable* stair1;
	Room* room1;
	Room* room2;
	Door* door;
	Door* door2;
	Crate* crate1;
	HealthPotion* healthPotion1;
	DamagePotion* damagePotion1;
	SpeedPotion* speedPotion1;
	LootChest* lootChest1;
	BabyOrc* babyOrc1;
	PsychoOrc* psychoOrc1;
	Orc* orc1;
	ArmoredOrc* armoredOrc1;
	NecromancerOrc* necromancerOrc1;
	Bomb* bomb1;
	BomberOrc* bomberOrc1;
	BossOrc* bossOrc;
	Gold* gold1;

};

#endif // !LEVEL1_H
