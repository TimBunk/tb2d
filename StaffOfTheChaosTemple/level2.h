#ifndef LEVEL2_H
#define LEVEL2_H

#include "level.h"

class Level2 : public Level
{
public:
	Level2(int screenWidthCamera, int screenHeightCamera);
	~Level2();

private:
	Enemy* enemy;
	B2Entity* wall;
	B2Entity* wall2;
	B2Entity* wall3;
	B2Entity* wall4;
	Mirror* mirror;
	Mirror* mirror2;
	Mirror* mirror3;
	Door* door1;
	Door* door2;
};

#endif // !LEVEL2_H