#ifndef LEVEL_H
#define LEVEL_H

#include "scene.h"
#include "mirror.h"
#include "crystal.h"
#include "door.h"
#include "player.h"
#include "box2Dclasses/contactListener.h"
#include "enemy.h"

class Level : public Scene
{
public:
	Level(int screenWidthCamera, int screenHeightCamera);
	virtual ~Level();

	virtual void Update(double deltaTime);
	void CreateFinish(int x, int y, int width, int height);
	bool IsFinished();

	b2World* GetB2World();
	void AddEnemy(Enemy* enemy);

protected:

	Sprite* greenHealthbarPlayer;
	Sprite* redHealthbarPlayer;

	b2World* world;
	ContactListener* contactListener;
	Player* player;
	B2Entity* finish;
	bool finished;

private:
	std::vector<Enemy*> enemies;
};

#endif // !LEVEL_H
