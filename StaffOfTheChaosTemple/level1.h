#ifndef LEVEL1_H
#define LEVEL1_H

#include "scene.h"
#include "player.h"

class Level1 : public Scene
{
public:
	Level1(b2World* world, int screenWidthCamera, int screenHeightCamera, ResourceManager* rm);
	~Level1();

	void Update(double deltaTime);

	void SetFinish(Player* player, int x, int y, int width, int height);

private:
	Player* player;
	B2Entity* finish;
};

#endif // !LEVEL1_H