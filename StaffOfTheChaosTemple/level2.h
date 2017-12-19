#ifndef LEVEL2_H
#define LEVEL2_H

#include "level.h"
#include "enemy.h"

class Level2 : public Level
{
public:
	Level2(int screenWidthCamera, int screenHeightCamera);
	~Level2();

private:
	Enemy* enemy;
	Enemy* enemy1;
	Enemy* enemy2;
	B2Entity* wall;
	Mirror* mirror;
};

#endif // !LEVEL2_H