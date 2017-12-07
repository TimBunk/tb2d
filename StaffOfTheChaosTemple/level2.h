#ifndef LEVEL2_H
#define LEVEL2_H

#include "level.h"

class Level2 : public Level
{
public:
	Level2(b2World* world, int screenWidthCamera, int screenHeightCamera, ResourceManager* rm);
	~Level2();

	void SetPlayer(Player* player);

private:

};

#endif // !LEVEL2_H