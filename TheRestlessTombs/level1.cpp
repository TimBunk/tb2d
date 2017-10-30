#include "level1.h"

Level1::Level1(Player* player, b2World* world, ResourceManager* rm, Input* input, Camera* camera) : Scene::Scene(camera) {
	// Set all of the variables
	this->player = player;
	this->rm = rm;
	this->input = input;
	this->world = world;
	currentRoom = 0;

	// room1
	floor1_1 = new Renderable(this->rm->GetTexture("floorDetailed"), this->camera, this->rm->GetShader("shader"));
	floor1_1->CreateBody(0, 0, 800, 600, 800, 600);
	floor1_2 = new Renderable(this->rm->GetTexture("floor"), this->camera, this->rm->GetShader("shader"));
	floor1_2->CreateBody(0, -800, 948, 200, 948, 200);
	stair1_1 = new Renderable(this->rm->GetTexture("stairs"), this->camera, this->rm->GetShader("shader"));
	stair1_1->CreateBody(0, -500, 200, 400, 200, 400);
	door1_1 = new Door(5, Direction::west, camera, rm->GetShader("shader"), this->world);
	door1_1->CreateBody(-449, -800, 200);
	door1_1->GiveTexture(this->rm->GetTexture("doorWest"));
	door1_2 = new Door(1, Direction::east, camera, rm->GetShader("shader"), this->world);
	door1_2->CreateBody(449, -800, 200);
	door1_2->GiveTexture(this->rm->GetTexture("doorEast"));
	healthPotion1_1 = new HealthPotion(1, this->camera, this->rm->GetShader("shader"), this->world);
	healthPotion1_1->CreateBody(0, 0, 30, 36, false, true);
	healthPotion1_1->GiveTexture(this->rm->GetTexture("healthPotion"));
	crate1_1 = new Crate(this->camera, this->rm->GetShader("shader"), this->world);
	crate1_1->CreateBody(375, -250, 50, 100, false, false);
	crate1_1->GiveTexture(this->rm->GetTexture("doubleCrate"));
	crate1_2 = new Crate(this->camera, this->rm->GetShader("shader"), this->world);
	crate1_2->CreateBody(325, -231, 50, 62, false, false);
	crate1_2->GiveTexture(this->rm->GetTexture("crate"));
	crate1_2->Store(healthPotion1_1);
	wall1_1 = new Wall(true, this->camera, this->rm->GetShader("shader"), this->world);
	wall1_1->GiveTexture(this->rm->GetTexture("wall"));
	wall1_1->CreateBody(-250, -337, 300, 74);
	wall1_2 = new Wall(true, this->camera, this->rm->GetShader("shader"), this->world);
	wall1_2->GiveTexture(this->rm->GetTexture("wall"));
	wall1_2->CreateBody(250, -337, 300, 74);
	wall1_3 = new Wall(false, this->camera, this->rm->GetShader("shader"), this->world);
	wall1_3->CreateBody(-437, 0, 74, 748);
	wall1_4 = new Wall(false, this->camera, this->rm->GetShader("shader"), this->world);
	wall1_4->CreateBody(437, 0, 74, 748);
	wall1_5 = new Wall(false, this->camera, this->rm->GetShader("shader"), this->world);
	wall1_5->CreateBody(0, 337, 800, 74);
	wall1_6 = new Wall(false, this->camera, this->rm->GetShader("shader"), this->world);
	wall1_6->CreateBody(-287, -537, 374, 326);
	wall1_7 = new Wall(false, this->camera, this->rm->GetShader("shader"), this->world);
	wall1_7->CreateBody(287, -537, 374, 326);
	wall1_8 = new Wall(true, this->camera, this->rm->GetShader("shader"), this->world);
	wall1_8->GiveTexture(this->rm->GetTexture("wall"));
	wall1_8->CreateBody(0, -937, 948, 74);

	// room2
	floor2_1 = new Renderable(this->rm->GetTexture("floor"), this->camera, this->rm->GetShader("shader"));
	floor2_1->CreateBody(449, -800, 50, 200, 50, 200);
	floor2_2 = new Renderable(this->rm->GetTexture("floor"), this->camera, this->rm->GetShader("shader"));
	floor2_2->CreateBody(774, -525, 200, 50, 200, 50);
	floor2_3 = new Renderable(this->rm->GetTexture("floor"), this->camera, this->rm->GetShader("shader"));
	floor2_3->CreateBody(1299, -800, 50, 200, 50, 200);
	floor2_4 = new Renderable(this->rm->GetTexture("floor"), this->camera, this->rm->GetShader("shader"));
	floor2_4->CreateBody(449, -1400, 50, 200, 50, 200);
	floor2_5 = new Renderable(this->rm->GetTexture("floor"), this->camera, this->rm->GetShader("shader"));
	floor2_5->CreateBody(874, -1025, 800, 950, 800, 950);
	door2_1 = new Door(0, Direction::west, camera, rm->GetShader("shader"), this->world);
	door2_1->CreateBody(449, -800, 200);
	door2_1->GiveTexture(this->rm->GetTexture("doorWest"));
	door2_2 = new Door(3, Direction::east, camera, rm->GetShader("shader"), this->world);
	door2_2->CreateBody(1299, -800, 200);
	door2_2->GiveTexture(this->rm->GetTexture("doorEast"));
	door2_3 = new Door(2, Direction::south, camera, rm->GetShader("shader"), this->world);
	door2_3->CreateBody(774, -525, 200);
	door2_3->GiveTexture(this->rm->GetTexture("doorSouth"));
	door2_4 = new Door(4, Direction::west, camera, rm->GetShader("shader"), this->world);
	door2_4->CreateBody(449, -1400, 200);
	door2_4->GiveTexture(this->rm->GetTexture("doorWest"));
	gold2_1 = new Gold(32, this->camera, this->rm->GetShader("shader"), this->world);
	gold2_1->CreateBody(0, 0, 15, 15, true, true);
	gold2_1->GiveTexture(this->rm->GetTexture("gold"));
	healthPotion2_1 = new HealthPotion(1, this->camera, this->rm->GetShader("shader"), this->world);
	healthPotion2_1->CreateBody(1249, -1425, 30, 36, false, true);
	healthPotion2_1->GiveTexture(this->rm->GetTexture("healthPotion"));
	necromancerOrc2_1 = new NecromancerOrc(1.5f, this->player, 900.0f, this->rm, this->camera, rm->GetShader("shader"), this->world);
	necromancerOrc2_1->CreateBody(1174, -1350, 50, 75);
	necromancerOrc2_1->GiveTexture(this->rm->GetTexture("necromancerOrc"));
	necromancerOrc2_1->GiveItem(gold2_1);
	wall2_1 = new Wall(false, this->camera, this->rm->GetShader("shader"), this->world);
	wall2_1->CreateBody(449, -1100, 50, 400);
	wall2_2 = new Wall(false, this->camera, this->rm->GetShader("shader"), this->world);
	wall2_2->CreateBody(449, -600, 50, 200);
	wall2_3 = new Wall(false, this->camera, this->rm->GetShader("shader"), this->world);
	wall2_3->CreateBody(574, -525, 200, 50);
	wall2_4 = new Wall(false, this->camera, this->rm->GetShader("shader"), this->world);
	wall2_4->CreateBody(1074, -525, 400, 50);
	wall2_5 = new Wall(false, this->camera, this->rm->GetShader("shader"), this->world);
	wall2_5->CreateBody(1299, -600, 50, 200);
	wall2_6 = new Wall(false, this->camera, this->rm->GetShader("shader"), this->world);
	wall2_6->CreateBody(1299, -1200, 50, 600);
	wall2_7 = new Wall(true, this->camera, this->rm->GetShader("shader"), this->world);
	wall2_7->GiveTexture(this->rm->GetTexture("wall"));
	wall2_7->CreateBody(850, -1537, 850, 74);

	// room3
	floor3_1 = new Renderable(this->rm->GetTexture("floor"), this->camera, this->rm->GetShader("shader"));
	floor3_1->CreateBody(774, -525, 200, 50, 200, 50);
	floor3_2 = new Renderable(this->rm->GetTexture("floorDetailed"), this->camera, this->rm->GetShader("shader"));
	floor3_2->CreateBody(874, -200, 800, 600, 800, 600);
	door3_1 = new Door(1, Direction::north, camera, rm->GetShader("shader"), this->world);
	door3_1->CreateBody(774, -525, 200);
	door3_1->GiveTexture(this->rm->GetTexture("doorNorth"));
	gold3_1 = new Gold(21, this->camera, this->rm->GetShader("shader"), this->world);
	gold3_1->CreateBody(0, 0, 15, 15, true, true);
	gold3_1->GiveTexture(this->rm->GetTexture("gold"));
	gold3_2 = new Gold(19, this->camera, this->rm->GetShader("shader"), this->world);
	gold3_2->CreateBody(0, 0, 15, 15, true, true);
	gold3_2->GiveTexture(this->rm->GetTexture("gold"));
	gold3_3 = new Gold(11, this->camera, this->rm->GetShader("shader"), this->world);
	gold3_3->CreateBody(0, 0, 15, 15, true, true);
	gold3_3->GiveTexture(this->rm->GetTexture("gold"));
	crate3_1 = new Crate(this->camera, this->rm->GetShader("shader"), this->world);
	crate3_1->CreateBody(499, -450, 50, 100, false, false);
	crate3_1->GiveTexture(this->rm->GetTexture("doubleCrate"));
	crate3_1->Store(gold3_3);
	crate3_2 = new Crate(this->camera, this->rm->GetShader("shader"), this->world);
	crate3_2->CreateBody(549, -469, 50, 62, false, false);
	crate3_2->GiveTexture(this->rm->GetTexture("crate"));
	lootChest3_1 = new LootChest(104, this->player, this->rm->GetShader("text"), camera, this->rm->GetShader("shader"), this->world);
	lootChest3_1->CreateBody(824, 62, 75, 75, false, false);
	lootChest3_1->GiveTexture(this->rm->GetTexture("silverLootChestClosed"), this->rm->GetTexture("silverLootChestOpened"));
	orc3_1 = new Orc(this->player, 600.0f, this->rm, this->camera, this->rm->GetShader("shader"), this->world);
	orc3_1->CreateBody(692, -50, 50, 75);
	orc3_1->GiveTexture(this->rm->GetTexture("orc"));
	orc3_1->GiveItem(gold3_1);
	orc3_2 = new Orc(this->player, 600.0f, this->rm, this->camera, this->rm->GetShader("shader"), this->world);
	orc3_2->CreateBody(992, -50, 50, 75);
	orc3_2->GiveTexture(this->rm->GetTexture("orc"));
	orc3_2->GiveItem(gold3_2);
	wall3_1 = new Wall(true, this->camera, this->rm->GetShader("shader"), this->world);
	wall3_1->GiveTexture(this->rm->GetTexture("wall"));
	wall3_1->CreateBody(574, -537, 200, 74);
	wall3_2 = new Wall(true, this->camera, this->rm->GetShader("shader"), this->world);
	wall3_2->GiveTexture(this->rm->GetTexture("wall"));
	wall3_2->CreateBody(1074, -537, 400, 74);
	wall3_3 = new Wall(false, this->camera, this->rm->GetShader("shader"), this->world);
	wall3_3->CreateBody(1299, -200, 50, 774);
	wall3_4 = new Wall(false, this->camera, this->rm->GetShader("shader"), this->world);
	wall3_4->CreateBody(449, -200, 50, 774);
	wall3_5 = new Wall(false, this->camera, this->rm->GetShader("shader"), this->world);
	wall3_5->CreateBody(874, 125, 800, 50);

	// room4
	floor4_1 = new Renderable(this->rm->GetTexture("floor"), this->camera, this->rm->GetShader("shader"));
	floor4_1->CreateBody(1299, -800, 50, 200, 50, 200);
	floor4_2 = new Renderable(this->rm->GetTexture("floor"), this->camera, this->rm->GetShader("shader"));
	floor4_2->CreateBody(1674, -1025, 700, 950, 700, 950);
	floor4_3 = new Renderable(this->rm->GetTexture("floor"), this->camera, this->rm->GetShader("shader"));
	floor4_3->CreateBody(2774, -1025, 700, 950, 700, 950);
	floor4_4 = new Renderable(this->rm->GetTexture("floor"), this->camera, this->rm->GetShader("shader"));
	floor4_4->CreateBody(1674, -2350, 500, 500, 500, 500);
	stair4_1 = new Renderable(this->rm->GetTexture("stairs"), this->camera, this->rm->GetShader("shader"));
	stair4_1->CreateBody(2224, -1000, 200, 400, 200, 400);
	stair4_1->localAngle = glm::radians(270.0f);
	door4_1 = new Door(1, Direction::west, camera, rm->GetShader("shader"), this->world);
	door4_1->CreateBody(1299, -800, 200);
	door4_1->GiveTexture(this->rm->GetTexture("doorWest"));
	bomb4_1 = new Bomb(30.0f, 3.0f, 150.0f, 0.2f, this->rm->GetTexture("bomb"), this->rm->GetTexture("explosion"), this->camera, this->rm->GetShader("bomb"), this->world);
	bomb4_1->CreateBody(0, 0, 30);
	bomb4_2 = new Bomb(30.0f, 3.0f, 150.0f, 0.2f, this->rm->GetTexture("bomb"), this->rm->GetTexture("explosion"), this->camera, this->rm->GetShader("bomb"), this->world);
	bomb4_2->CreateBody(0, 0, 30);
	speedPotion4_1 = new SpeedPotion(2.0f, -0.15f, 4.0f, this->camera, this->rm->GetShader("shader"), this->world);
	speedPotion4_1->CreateBody(1847, -1200, 30, 36, false, true);
	speedPotion4_1->GiveTexture(this->rm->GetTexture("speedPotion"));
	lootChest4_1 = new LootChest(250, this->player, this->rm->GetShader("text"), camera, this->rm->GetShader("shader"), this->world);
	lootChest4_1->CreateBody(2974, -1025, 75, 75, false, false);
	lootChest4_1->GiveTexture(this->rm->GetTexture("goldLootChestClosed"), this->rm->GetTexture("goldLootChestOpened"));
	lootChest4_2 = new LootChest(211, this->player, this->rm->GetShader("text"), camera, this->rm->GetShader("shader"), this->world);
	lootChest4_2->CreateBody(1524, -2500, 75, 75, false, false);
	lootChest4_2->GiveTexture(this->rm->GetTexture("goldLootChestClosed"), this->rm->GetTexture("goldLootChestOpened"));
	lootChest4_3 = new LootChest(212, this->player, this->rm->GetShader("text"), camera, this->rm->GetShader("shader"), this->world);
	lootChest4_3->CreateBody(1824, -2500, 75, 75, false, false);
	lootChest4_3->GiveTexture(this->rm->GetTexture("goldLootChestClosed"), this->rm->GetTexture("goldLootChestOpened"));
	bomberOrc4_1 = new BomberOrc(this->player, 450.0f, this->rm, this->camera, this->rm->GetShader("shader"), this->world);
	bomberOrc4_1->CreateBody(2774, -825, 50, 57);
	bomberOrc4_1->GiveTexture(this->rm->GetTexture("bomberOrc"));
	bomberOrc4_1->GiveItem(bomb4_1);
	bomberOrc4_2 = new BomberOrc(this->player, 450.0f, this->rm, this->camera, this->rm->GetShader("shader"), this->world);
	bomberOrc4_2->CreateBody(2774, -1225, 50, 57);
	bomberOrc4_2->GiveTexture(this->rm->GetTexture("bomberOrc"));
	bomberOrc4_2->GiveItem(bomb4_2);
	psychoOrc4_1 = new PsychoOrc(this->player, 550.0f, this->rm, this->camera, this->rm->GetShader("shader"), this->world);
	psychoOrc4_1->CreateBody(1674, -2350, 50, 62);
	psychoOrc4_1->GiveTexture(this->rm->GetTexture("psychoOrc"));
	secretWall4_1 = new Renderable(this->rm->GetTexture("secretWall"), this->camera, this->rm->GetShader("shader"));
	secretWall4_1->CreateBody(1674, -1537, 300, 74, 300, 74);
	wall4_1 = new Wall(false, this->camera, this->rm->GetShader("shader"), this->world);
	wall4_1->CreateBody(1299, -600, 50, 200);
	wall4_2 = new Wall(false, this->camera, this->rm->GetShader("shader"), this->world);
	wall4_2->CreateBody(1299, -1200, 50, 600);
	wall4_3 = new Wall(false, this->camera, this->rm->GetShader("shader"), this->world);
	wall4_3->CreateBody(1674, -525, 800, 50);
	wall4_4 = new Wall(true, this->camera, this->rm->GetShader("shader"), this->world);
	wall4_4->GiveTexture(this->rm->GetTexture("wall"));
	wall4_4->CreateBody(1424, -1537, 200, 74);
	wall4_5 = new Wall(true, this->camera, this->rm->GetShader("shader"), this->world);
	wall4_5->GiveTexture(this->rm->GetTexture("wall"));
	wall4_5->CreateBody(1924, -1537, 200, 74);
	wall4_6 = new Wall(false, this->camera, this->rm->GetShader("shader"), this->world);
	wall4_6->CreateBody(2224, -1300, 400, 400);
	wall4_7 = new Wall(false, this->camera, this->rm->GetShader("shader"), this->world);
	wall4_7->CreateBody(2224, -700, 400,400);
	wall4_8 = new Wall(true, this->camera, this->rm->GetShader("shader"), this->world);
	wall4_8->GiveTexture(this->rm->GetTexture("wall"));
	wall4_8->CreateBody(2774, -1537, 700, 74);
	wall4_9 = new Wall(false, this->camera, this->rm->GetShader("shader"), this->world);
	wall4_9->CreateBody(2774, -525, 700, 50);
	wall4_10 = new Wall(false, this->camera, this->rm->GetShader("shader"), this->world);
	wall4_10->CreateBody(3149, -1025, 50, 1074);
	wall4_11 = new Wall(false, this->camera, this->rm->GetShader("shader"), this->world);
	wall4_11->CreateBody(1424, -1837, 200, 526);
	wall4_12 = new Wall(false, this->camera, this->rm->GetShader("shader"), this->world);
	wall4_12->CreateBody(1924, -1837, 200, 526);
	wall4_13 = new Wall(false, this->camera, this->rm->GetShader("shader"), this->world);
	wall4_13->CreateBody(1949, -2350, 50, 600);
	wall4_14 = new Wall(false, this->camera, this->rm->GetShader("shader"), this->world);
	wall4_14->CreateBody(1399, -2350, 50, 600);
	wall4_15 = new Wall(false, this->camera, this->rm->GetShader("shader"), this->world);
	wall4_15->CreateBody(1674, -2637, 700, 74);

	// room5
	floor5_1 = new Renderable(this->rm->GetTexture("floor"), this->camera, this->rm->GetShader("shader"));
	floor5_1->CreateBody(449, -1400, 50, 200, 50, 200);
	floor5_2 = new Renderable(this->rm->GetTexture("floor"), this->camera, this->rm->GetShader("shader"));
	floor5_2->CreateBody(-201, -1400, 50, 200, 50, 200);
	floor5_3 = new Renderable(this->rm->GetTexture("floor"), this->camera, this->rm->GetShader("shader"));
	floor5_3->CreateBody(449, -1900, 50, 200, 50, 200);
	floor5_4 = new Renderable(this->rm->GetTexture("floorDetailed"), this->camera, this->rm->GetShader("shader"));
	floor5_4->CreateBody(124, -1700, 600, 800, 600, 800);
	door5_1 = new Door(1, Direction::east, camera, rm->GetShader("shader"), this->world);
	door5_1->CreateBody(449, -1400, 200);
	door5_1->GiveTexture(this->rm->GetTexture("doorEast"));
	door5_2 = new Door(5, Direction::west, camera, rm->GetShader("shader"), this->world);
	door5_2->CreateBody(-201, -1400, 200);
	door5_2->GiveTexture(this->rm->GetTexture("doorWest"));
	door5_3 = new Door(6, Direction::east, camera, rm->GetShader("shader"), this->world);
	door5_3->CreateBody(449, -1900, 200);
	door5_3->GiveTexture(this->rm->GetTexture("doorEast"));
	gold5_1 = new Gold(39, this->camera, this->rm->GetShader("shader"), this->world);
	gold5_1->CreateBody(0, 0, 15, 15, true, true);
	gold5_1->GiveTexture(this->rm->GetTexture("gold"));
	gold5_2 = new Gold(42, this->camera, this->rm->GetShader("shader"), this->world);
	gold5_2->CreateBody(0, 0, 15, 15, true, true);
	gold5_2->GiveTexture(this->rm->GetTexture("gold"));
	damagePotion5_1 = new DamagePotion(1.0f, 5.0f, this->camera, this->rm->GetShader("shader"), this->world);
	damagePotion5_1->CreateBody(-126, -2000, 30, 36, false, true);
	damagePotion5_1->GiveTexture(this->rm->GetTexture("damagePotion"));
	armoredOrc5_1 = new ArmoredOrc(this->player, 500.0f, this->rm, this->camera, this->rm->GetShader("shader"), this->world);
	armoredOrc5_1->CreateBody(-26, -1700, 50, 75);
	armoredOrc5_1->GiveTexture(this->rm->GetTexture("armoredOrc"));
	armoredOrc5_1->GiveItem(gold5_1);
	armoredOrc5_2 = new ArmoredOrc(this->player, 500.0f, this->rm, this->camera, this->rm->GetShader("shader"), this->world);
	armoredOrc5_2->CreateBody(274, -1700, 50, 75);
	armoredOrc5_2->GiveTexture(this->rm->GetTexture("armoredOrc"));
	armoredOrc5_2->GiveItem(gold5_2);
	wall5_1 = new Wall(false, this->camera, this->rm->GetShader("shader"), this->world);
	wall5_1->CreateBody(124, -1275, 700, 50);
	wall5_2 = new Wall(false, this->camera, this->rm->GetShader("shader"), this->world);
	wall5_2->CreateBody(-201, -1800, 50, 600);
	wall5_3 = new Wall(true, this->camera, this->rm->GetShader("shader"), this->world);
	wall5_3->GiveTexture(this->rm->GetTexture("wall"));
	wall5_3->CreateBody(124, -2137, 600, 74);
	wall5_4 = new Wall(false, this->camera, this->rm->GetShader("shader"), this->world);
	wall5_4->CreateBody(449, -2050, 50, 100);
	wall5_5 = new Wall(false, this->camera, this->rm->GetShader("shader"), this->world);
	wall5_5->CreateBody(449, -1650, 50, 300);
	bossRoomWarning = new Text("fonts/OpenSans-Regular.ttf", "Boss ahead->", 60, glm::vec4(0.0f, 0.5f, 0.0f, 1.0f), false, camera, rm->GetShader("text"));
	bossRoomWarning->localPosition = glm::vec3(220, -1900, 1.0f);

	// room6
	floor6_1 = new Renderable(this->rm->GetTexture("floor"), this->camera, this->rm->GetShader("shader"));
	floor6_1->CreateBody(-449, -800, 50, 200, 50, 200);
	floor6_2 = new Renderable(this->rm->GetTexture("floor"), this->camera, this->rm->GetShader("shader"));
	floor6_2->CreateBody(-325, -1400, 298, 200, 298, 200);
	floor6_3 = new Renderable(this->rm->GetTexture("floorDetailed"), this->camera, this->rm->GetShader("shader"));
	floor6_3->CreateBody(-774, -1300, 600, 1200, 600, 1200);
	door6_1 = new Door(0, Direction::east, camera, rm->GetShader("shader"), this->world);
	door6_1->CreateBody(-449, -800, 200);
	door6_1->GiveTexture(this->rm->GetTexture("doorEast"));
	door6_2 = new Door(4, Direction::east, camera, rm->GetShader("shader"), this->world);
	door6_2->CreateBody(-201, -1400, 200);
	door6_2->GiveTexture(this->rm->GetTexture("doorEast"));
	gold6_1 = new Gold(61, this->camera, this->rm->GetShader("shader"), this->world);
	gold6_1->CreateBody(0, 0, 15, 15, true, true);
	gold6_1->GiveTexture(this->rm->GetTexture("gold"));
	bomb6_1 = new Bomb(30.0f, 3.0f, 150.0f, 0.2f, this->rm->GetTexture("bomb"), this->rm->GetTexture("explosion"), this->camera, this->rm->GetShader("bomb"), this->world);
	bomb6_1->CreateBody(0, 0, 30);
	healthPotion6_1 = new HealthPotion(1, this->camera, this->rm->GetShader("shader"), this->world);
	healthPotion6_1->CreateBody(0, 0, 30, 36, false, true);
	healthPotion6_1->GiveTexture(this->rm->GetTexture("healthPotion"));
	lootChest6_1 = new LootChest(198, this->player, this->rm->GetShader("text"), camera, this->rm->GetShader("shader"), this->world);
	lootChest6_1->CreateBody(-624, -1850, 75, 75, false, false);
	lootChest6_1->GiveTexture(this->rm->GetTexture("goldLootChestClosed"), this->rm->GetTexture("goldLootChestOpened"));
	crate6_1 = new Crate(this->camera, this->rm->GetShader("shader"), this->world);
	crate6_1->CreateBody(-1049, -750, 50, 100, false, false);
	crate6_1->GiveTexture(this->rm->GetTexture("doubleCrate"));
	crate6_2 = new Crate(this->camera, this->rm->GetShader("shader"), this->world);
	crate6_2->CreateBody(-999, -731, 50, 62, false, false);
	crate6_2->GiveTexture(this->rm->GetTexture("crate"));
	crate6_2->Store(bomb6_1);
	crate6_3 = new Crate(this->camera, this->rm->GetShader("shader"), this->world);
	crate6_3->CreateBody(-1049, -1850, 50, 100, false, false);
	crate6_3->GiveTexture(this->rm->GetTexture("doubleCrate"));
	crate6_3->Store(healthPotion6_1);
	crate6_4 = new Crate(this->camera, this->rm->GetShader("shader"), this->world);
	crate6_4->CreateBody(-999, -1869, 50, 62, false, false);
	crate6_4->GiveTexture(this->rm->GetTexture("crate"));
	necromancerOrc6_1 = new NecromancerOrc(1.5f, this->player, 1200.0f, this->rm, this->camera, rm->GetShader("shader"), this->world);
	necromancerOrc6_1->CreateBody(-878, -1680, 50, 75);
	necromancerOrc6_1->GiveTexture(this->rm->GetTexture("necromancerOrc"));
	necromancerOrc6_1->GiveItem(gold6_1);
	babyOrc6_1 = new BabyOrc(this->player, 1200.0f, this->rm, this->camera, this->rm->GetShader("shader"), this->world);
	babyOrc6_1->CreateBody(-998, -1700, 50, 50);
	babyOrc6_1->GiveTexture(this->rm->GetTexture("babyOrc"));
	babyOrc6_2 = new BabyOrc(this->player, 1200.0f, this->rm, this->camera, this->rm->GetShader("shader"), this->world);
	babyOrc6_2->CreateBody(-938, -1700, 50, 50);
	babyOrc6_2->GiveTexture(this->rm->GetTexture("babyOrc"));
	babyOrc6_3 = new BabyOrc(this->player, 1200.0f, this->rm, this->camera, this->rm->GetShader("shader"), this->world);
	babyOrc6_3->CreateBody(-818, -1700, 50, 50);
	babyOrc6_3->GiveTexture(this->rm->GetTexture("babyOrc"));
	babyOrc6_4 = new BabyOrc(this->player, 1200.0f, this->rm, this->camera, this->rm->GetShader("shader"), this->world);
	babyOrc6_4->CreateBody(-758, -1700, 50, 50);
	babyOrc6_4->GiveTexture(this->rm->GetTexture("babyOrc"));
	wall6_1 = new Wall(false, this->camera, this->rm->GetShader("shader"), this->world);
	wall6_1->CreateBody(-325, -1100, 298, 400);
	wall6_2 = new Wall(false, this->camera, this->rm->GetShader("shader"), this->world);
	wall6_2->CreateBody(-325, -1700, 298, 400);
	wall6_3 = new Wall(false, this->camera, this->rm->GetShader("shader"), this->world);
	wall6_3->CreateBody(-774, -675, 700, 50);
	wall6_4 = new Wall(false, this->camera, this->rm->GetShader("shader"), this->world);
	wall6_4->CreateBody(-1099, -1300, 50, 1200);
	wall6_5 = new Wall(true, this->camera, this->rm->GetShader("shader"), this->world);
	wall6_5->GiveTexture(this->rm->GetTexture("wall"));
	wall6_5->CreateBody(-774, -1937, 600, 74);

	// room7
	floor7_1 = new Renderable(this->rm->GetTexture("floor"), this->camera, this->rm->GetShader("shader"));
	floor7_1->CreateBody(449, -1900, 50, 200, 50, 200);
	floor7_2 = new Renderable(this->rm->GetTexture("floor"), this->camera, this->rm->GetShader("shader"));
	floor7_2->CreateBody(849, -2162, 750, 725, 750, 725);
	door7_1 = new Door(4, Direction::west, camera, rm->GetShader("shader"), this->world);
	door7_1->CreateBody(449, -1900, 200);
	door7_1->GiveTexture(this->rm->GetTexture("doorWest"));
	bossOrc7_1 = new BossOrc("BossOrc", this->player, 1000.0f, this->rm, this->camera, this->rm->GetShader("shader"), this->world);
	bossOrc7_1->CreateBody(849, -2343, 75, 100);
	bossOrc7_1->GiveTexture(this->rm->GetTexture("bossOrc"));
	wall7_1 = new Wall(false, this->camera, this->rm->GetShader("shader"), this->world);
	wall7_1->CreateBody(824, -1775, 800, 50);
	wall7_2 = new Wall(false, this->camera, this->rm->GetShader("shader"), this->world);
	wall7_2->CreateBody(1249, -2150, 50, 800);
	wall7_3 = new Wall(false, this->camera, this->rm->GetShader("shader"), this->world);
	wall7_3->CreateBody(449, -2300, 50, 600);
	wall7_4 = new Wall(true, this->camera, this->rm->GetShader("shader"), this->world);
	wall7_4->GiveTexture(this->rm->GetTexture("wall"));
	wall7_4->CreateBody(849, -2561, 750, 74);


	currentRoom = 0;
	room1 = new Room(camera);
	this->AddChild(room1);
	room1->AddChild(floor1_1);
	room1->AddChild(floor1_2);
	room1->AddChild(stair1_1);
	room1->AddChild(door1_1);
	room1->AddChild(door1_2);
	//room1->AddChild(healthPotion1_1);
	room1->AddChild(crate1_1);
	room1->AddChild(crate1_2);
	room1->AddChild(wall1_1);
	room1->AddChild(wall1_2);
	room1->AddChild(wall1_3);
	room1->AddChild(wall1_4);
	room1->AddChild(wall1_5);
	room1->AddChild(wall1_6);
	room1->AddChild(wall1_7);
	room1->AddChild(wall1_8);
	room1->SetActive(true);
	rooms.push_back(room1);

	room2 = new Room(camera);
	room2->AddChild(floor2_1);
	room2->AddChild(floor2_2);
	room2->AddChild(floor2_3);
	room2->AddChild(floor2_4);
	room2->AddChild(floor2_5);
	room2->AddChild(door2_1);
	room2->AddChild(door2_2);
	room2->AddChild(door2_3);
	room2->AddChild(door2_4);
	room2->AddChild(healthPotion2_1);
	room2->AddChild(wall2_1);
	room2->AddChild(wall2_2);
	room2->AddChild(wall2_3);
	room2->AddChild(wall2_4);
	room2->AddChild(wall2_5);
	room2->AddChild(wall2_6);
	room2->AddChild(wall2_7);
	room2->AddChild(necromancerOrc2_1);
	room2->SetActive(false);
	rooms.push_back(room2);

	room3 = new Room(camera);
	room3->AddChild(floor3_1);
	room3->AddChild(floor3_2);
	room3->AddChild(door3_1);
	room3->AddChild(crate3_1);
	room3->AddChild(crate3_2);
	room3->AddChild(lootChest3_1);
	room3->AddChild(wall3_1);
	room3->AddChild(wall3_2);
	room3->AddChild(wall3_3);
	room3->AddChild(wall3_4);
	room3->AddChild(wall3_5);
	room3->AddChild(orc3_1);
	room3->AddChild(orc3_2);
	room3->SetActive(false);
	rooms.push_back(room3);

	room4 = new Room(camera);
	room4->AddChild(floor4_1);
	room4->AddChild(floor4_2);
	room4->AddChild(floor4_3);
	room4->AddChild(floor4_4);
	room4->AddChild(stair4_1);
	room4->AddChild(door4_1);
	room4->AddChild(speedPotion4_1);
	room4->AddChild(lootChest4_1);
	room4->AddChild(lootChest4_2);
	room4->AddChild(lootChest4_3);
	room4->AddChild(secretWall4_1);
	room4->AddChild(wall4_1);
	room4->AddChild(wall4_2);
	room4->AddChild(wall4_3);
	room4->AddChild(wall4_4);
	room4->AddChild(wall4_5);
	room4->AddChild(wall4_6);
	room4->AddChild(wall4_7);
	room4->AddChild(wall4_8);
	room4->AddChild(wall4_9);
	room4->AddChild(wall4_10);
	room4->AddChild(wall4_11);
	room4->AddChild(wall4_12);
	room4->AddChild(wall4_13);
	room4->AddChild(wall4_14);
	room4->AddChild(wall4_15);
	room4->AddChild(bomberOrc4_1);
	room4->AddChild(bomberOrc4_2);
	room4->AddChild(psychoOrc4_1);
	room4->SetActive(false);
	rooms.push_back(room4);

	room5 = new Room(camera);
	room5->AddChild(floor5_1);
	room5->AddChild(floor5_2);
	room5->AddChild(floor5_3);
	room5->AddChild(floor5_4);
	room5->AddChild(door5_1);
	room5->AddChild(door5_2);
	room5->AddChild(door5_3);
	room5->AddChild(damagePotion5_1);
	room5->AddChild(wall5_1);
	room5->AddChild(wall5_2);
	room5->AddChild(wall5_3);
	room5->AddChild(wall5_4);
	room5->AddChild(wall5_5);
	room5->AddChild(armoredOrc5_1);
	room5->AddChild(armoredOrc5_2);
	room5->AddChild(bossRoomWarning);
	room5->SetActive(false);
	rooms.push_back(room5);

	room6 = new Room(camera);
	room6->AddChild(floor6_1);
	room6->AddChild(floor6_2);
	room6->AddChild(floor6_3);
	room6->AddChild(door6_1);
	room6->AddChild(door6_2);
	room6->AddChild(lootChest6_1);
	room6->AddChild(crate6_1);
	room6->AddChild(crate6_2);
	room6->AddChild(crate6_3);
	room6->AddChild(crate6_4);
	room6->AddChild(wall6_1);
	room6->AddChild(wall6_2);
	room6->AddChild(wall6_3);
	room6->AddChild(wall6_4);
	room6->AddChild(wall6_5);
	room6->AddChild(necromancerOrc6_1);
	room6->AddChild(babyOrc6_1);
	room6->AddChild(babyOrc6_2);
	room6->AddChild(babyOrc6_3);
	room6->AddChild(babyOrc6_4);
	room6->SetActive(false);
	rooms.push_back(room6);

	room7 = new Room(camera);
	room7->AddChild(floor7_1);
	room7->AddChild(floor7_2);
	room7->AddChild(door7_1);
	room7->AddChild(wall7_1);
	room7->AddChild(wall7_2);
	room7->AddChild(wall7_3);
	room7->AddChild(wall7_4);
	room7->AddChild(bossOrc7_1);
	room7->SetActive(false);
	rooms.push_back(room7);



	this->AddChild(player);
}

Level1::~Level1() {
	// room1
	delete room1;
	delete floor1_1;
	delete floor1_2;
	delete stair1_1;
	delete door1_1;
	delete door1_2;
	delete healthPotion1_1;
	delete crate1_1;
	delete crate1_2;
	delete wall1_1;
	delete wall1_2;
	delete wall1_3;
	delete wall1_4;
	delete wall1_5;
	delete wall1_6;
	delete wall1_7;
	delete wall1_8;
	// room2
	delete room2;
	delete floor2_1;
	delete floor2_2;
	delete floor2_3;
	delete floor2_4;
	delete floor2_5;
	delete door2_1;
	delete door2_2;
	delete door2_3;
	delete door2_4;
	delete gold2_1;
	delete healthPotion2_1;
	delete necromancerOrc2_1;
	delete wall2_1;
	delete wall2_2;
	delete wall2_3;
	delete wall2_4;
	delete wall2_5;
	delete wall2_6;
	delete wall2_7;
	// room3
	delete room3;
	delete floor3_1;
	delete floor3_2;
	delete door3_1;
	delete gold3_1;
	delete gold3_2;
	delete gold3_3;
	delete crate3_1;
	delete crate3_2;
	delete lootChest3_1;
	delete orc3_1;
	delete orc3_2;
	delete wall3_1;
	delete wall3_2;
	delete wall3_3;
	delete wall3_4;
	delete wall3_5;
	// room4
	delete room4;
	delete floor4_1;
	delete floor4_2;
	delete floor4_3;
	delete stair4_1;
	delete door4_1;
	delete bomb4_1;
	delete bomb4_2;
	delete speedPotion4_1;
	delete lootChest4_1;
	delete lootChest4_2;
	delete lootChest4_3;
	delete bomberOrc4_1;
	delete bomberOrc4_2;
	delete psychoOrc4_1;
	delete secretWall4_1;
	delete wall4_1;
	delete wall4_2;
	delete wall4_3;
	delete wall4_4;
	delete wall4_5;
	delete wall4_6;
	delete wall4_7;
	delete wall4_8;
	delete wall4_9;
	delete wall4_10;
	delete wall4_11;
	delete wall4_12;
	// room5
	delete room5;
	delete floor5_1;
	delete floor5_2;
	delete floor5_3;
	delete floor5_4;
	delete door5_1;
	delete door5_2;
	delete door5_3;
	delete gold5_1;
	delete gold5_2;
	delete damagePotion5_1;
	delete armoredOrc5_1;
	delete armoredOrc5_2;
	delete wall5_1;
	delete wall5_2;
	delete wall5_3;
	delete wall5_4;
	delete wall5_5;
	delete bossRoomWarning;
	// room6
	delete room6;
	delete floor6_1;
	delete floor6_2;
	delete floor6_3;
	delete door6_1;
	delete door6_2;
	delete gold6_1;
	delete bomb6_1;
	delete healthPotion6_1;
	delete lootChest6_1;
	delete crate6_1;
	delete crate6_2;
	delete crate6_3;
	delete crate6_4;
	delete necromancerOrc6_1;
	delete babyOrc6_1;
	delete babyOrc6_2;
	delete babyOrc6_3;
	delete babyOrc6_4;
	delete wall6_1;
	delete wall6_2;
	delete wall6_3;
	delete wall6_4;
	delete wall6_5;
	// room7
	delete room7;
	delete floor7_1;
	delete floor7_2;
	delete door7_1;
	delete bossOrc7_1;
	delete wall7_1;
	delete wall7_2;
	delete wall7_3;
	delete wall7_4;
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
		// remove and add the player so that the player will be drawn on top of everything else
		this->RemoveChild(player);
		this->AddChild(player);
	}
	// RESET
	if (input->KeyPress(SDL_SCANCODE_R)) {
		Reset();
	}
	this->UpdateChilderen(this, deltaTime);
}

void Level1::Reset() {
	for (int i=0;i<rooms.size();i++) {
		rooms[i]->Reset();
	}
}
