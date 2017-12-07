#ifndef LEVEL_H
#define LEVEL_H

#include "scene.h"
#include "player.h"

class Level : public Scene
{
public:
	Level(b2World* world, int screenWidthCamera, int screenHeightCamera, ResourceManager* rm);
	virtual ~Level();

	virtual void Update(double deltaTime);

	virtual void SetPlayer(Player* player);
	bool IsFinished();

protected:
	void CreateFinish(int x, int y, int width, int height);

	b2World* world;
	Player* player;
	B2Entity* finish;
	bool finished;
private:
	
};

#endif // !LEVEL_H
