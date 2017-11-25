#ifndef LEVEL1_H
#define LEVEL1_H

#include "scene.h"
#include "player.h"

class Level1 : public Scene
{
public:
	Level1(int screenWidthCamera, int screenHeightCamera);
	~Level1();

	void Update(double deltaTime);

private:
	Player* player;
};

#endif // !LEVEL1_H