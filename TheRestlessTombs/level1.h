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
#include "contactListener.h"

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
	ContactListener* contactListener;

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
};

#endif // !LEVEL1_H
