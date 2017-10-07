#ifndef LEVEL1_H
#define LEVEL1_H

#include "scene.h"
#include "resourceManager.h"
#include "input.h"
#include "player.h"
#include "wall.h"
#include "floor.h"

#include <Box2D/Box2D.h>

class Level1 : public Scene {
public:
	Level1(b2World* world, ResourceManager* rm, Input* input, Camera* camera);
	~Level1();

	void Update();
private:
	ResourceManager* rm;
	Input* input;
	b2World* world;
	Player* player;
	Wall* wall;
	Wall* wall2;
	Floor* floor;
};

#endif // !LEVEL1_H
