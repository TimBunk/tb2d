#ifndef LEVEL1_H
#define LEVEL1_H

#include "level.h"
#include "player.h"

class Level1 : public Level
{
public:
	Level1(b2World* world, int screenWidthCamera, int screenHeightCamera);
	~Level1();

	void SetPlayer(Player* player);

private:
	B2Entity* wall;
	B2Entity* wall2;
	B2Entity* wall3;
	B2Entity* wall4;
	B2Entity* wall5;
	B2Entity* wall6;
	Mirror* mirror;
	Crystal* crystal;
	Crystal* crystal2;
	Door* door;
	Door* door2;
};

#endif // !LEVEL1_H