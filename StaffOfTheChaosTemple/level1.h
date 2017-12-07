#ifndef LEVEL1_H
#define LEVEL1_H

#include "level.h"
#include "player.h"

class Level1 : public Level
{
public:
	Level1(b2World* world, int screenWidthCamera, int screenHeightCamera, ResourceManager* rm);
	~Level1();

	void SetPlayer(Player* player);

private:

};

#endif // !LEVEL1_H