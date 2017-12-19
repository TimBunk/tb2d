#ifndef LEVEL_H
#define LEVEL_H

#include "scene.h"
#include "mirror.h"
#include "crystal.h"
#include "door.h"
#include "player.h"
#include "box2Dclasses/contactListener.h"

class Level : public Scene
{
public:
	Level(int screenWidthCamera, int screenHeightCamera);
	virtual ~Level();

	virtual void Update(double deltaTime);
	bool IsFinished();

	b2World* GetB2World();

protected:
	void CreateFinish(int x, int y, int width, int height);

	b2World* world;
	ContactListener* contactListener;
	Player* player;
	B2Entity* finish;
	bool finished;
private:
	
};

#endif // !LEVEL_H
