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
#include "shop.h"

#include <Box2D/Box2D.h>

enum GameState {
	_game,
	_menu,
	_shop
};

class Level1 : public Scene {
public:
	Level1(Player* player, Shop* shop, b2World* world, ResourceManager* rm, Input* input, Camera* camera);
	~Level1();

	void Update(float deltaTime);
	void Reset();
private:
	ResourceManager* rm;
	Input* input;
	b2World* world;

	std::vector<Room*> rooms;
	int currentRoom;

	Player* player;
	Shop* shop;

	// room1
	Room* room1;
	Renderable* floor1_1;
	Renderable* floor1_2;
	Renderable* stair1_1;
	Door* door1_1;
	Door* door1_2;
	HealthPotion* healthPotion1_1;
	Crate* crate1_1;
	Crate* crate1_2;
	Wall* wall1_1;
	Wall* wall1_2;
	Wall* wall1_3;
	Wall* wall1_4;
	Wall* wall1_5;
	Wall* wall1_6;
	Wall* wall1_7;
	Wall* wall1_8;

	// room2
	Room* room2;
	Renderable* floor2_1;
	Renderable* floor2_2;
	Renderable* floor2_3;
	Renderable* floor2_4;
	Renderable* floor2_5;
	Door* door2_1;
	Door* door2_2;
	Door* door2_3;
	Door* door2_4;
	Gold* gold2_1;
	HealthPotion* healthPotion2_1;
	NecromancerOrc* necromancerOrc2_1;
	Wall* wall2_1;
	Wall* wall2_2;
	Wall* wall2_3;
	Wall* wall2_4;
	Wall* wall2_5;
	Wall* wall2_6;
	Wall* wall2_7;

	// room3
	Room* room3;
	Renderable* floor3_1;
	Renderable* floor3_2;
	Door* door3_1;
	Gold* gold3_1;
	Gold* gold3_2;
	Gold* gold3_3;
	Crate* crate3_1;
	Crate* crate3_2;
	LootChest* lootChest3_1;
	Orc* orc3_1;
	Orc* orc3_2;
	Wall* wall3_1;
	Wall* wall3_2;
	Wall* wall3_3;
	Wall* wall3_4;
	Wall* wall3_5;

	// room4
	Room* room4;
	Renderable* floor4_1;
	Renderable* floor4_2;
	Renderable* floor4_3;
	Renderable* floor4_4;
	Renderable* stair4_1;
	Door* door4_1;
	Bomb* bomb4_1;
	Bomb* bomb4_2;
	SpeedPotion* speedPotion4_1;
	LootChest* lootChest4_1;
	LootChest* lootChest4_2;
	LootChest* lootChest4_3;
	BomberOrc* bomberOrc4_1;
	BomberOrc* bomberOrc4_2;
	PsychoOrc* psychoOrc4_1;
	Renderable* secretWall4_1;
	Wall* wall4_1;
	Wall* wall4_2;
	Wall* wall4_3;
	Wall* wall4_4;
	Wall* wall4_5;
	Wall* wall4_6;
	Wall* wall4_7;
	Wall* wall4_8;
	Wall* wall4_9;
	Wall* wall4_10;
	Wall* wall4_11;
	Wall* wall4_12;
	Wall* wall4_13;
	Wall* wall4_14;
	Wall* wall4_15;

	// room5
	Room* room5;
	Renderable* floor5_1;
	Renderable* floor5_2;
	Renderable* floor5_3;
	Renderable* floor5_4;
	Door* door5_1;
	Door* door5_2;
	Door* door5_3;
	Gold* gold5_1;
	Gold* gold5_2;
	DamagePotion* damagePotion5_1;
	ArmoredOrc* armoredOrc5_1;
	ArmoredOrc* armoredOrc5_2;
	Wall* wall5_1;
	Wall* wall5_2;
	Wall* wall5_3;
	Wall* wall5_4;
	Wall* wall5_5;
	Text* bossRoomWarning;

	// room6
	Room* room6;
	Renderable* floor6_1;
	Renderable* floor6_2;
	Renderable* floor6_3;
	Door* door6_1;
	Door* door6_2;
	Gold* gold6_1;
	Bomb* bomb6_1;
	HealthPotion* healthPotion6_1;
	LootChest* lootChest6_1;
	Crate* crate6_1;
	Crate* crate6_2;
	Crate* crate6_3;
	Crate* crate6_4;
	NecromancerOrc* necromancerOrc6_1;
	BabyOrc* babyOrc6_1;
	BabyOrc* babyOrc6_2;
	BabyOrc* babyOrc6_3;
	BabyOrc* babyOrc6_4;
	Wall* wall6_1;
	Wall* wall6_2;
	Wall* wall6_3;
	Wall* wall6_4;
	Wall* wall6_5;

	// room7
	Room* room7;
	Renderable* floor7_1;
	Renderable* floor7_2;
	Door* door7_1;
	BossOrc* bossOrc7_1;
	Wall* wall7_1;
	Wall* wall7_2;
	Wall* wall7_3;
	Wall* wall7_4;

};

#endif // !LEVEL1_H
