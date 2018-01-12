#ifndef LEVEL_H
#define LEVEL_H

#include "scene.h"
#include "mirror.h"
#include "crystal.h"
#include "door.h"
#include "player.h"
#include "box2Dclasses/contactListener.h"
#include "enemy.h"
#include "textfile.h"

class Level : public Scene
{
public:
	Level(int screenWidthCamera, int screenHeightCamera, std::string filename);
	virtual ~Level();

	virtual void Update(double deltaTime);
	bool IsFinished();
	bool IsPlayerAlive() { return player->IsAlive(); }
	std::string GetLoadingErrors() { return LoadingErrors; }

protected:

	Sprite* greenHealthbarPlayer;
	Sprite* redHealthbarPlayer;

	b2World* world;
	ContactListener* contactListener;
	Player* player;
	B2Entity* finish;
	bool finished;

private:
	void Load(std::string filename);
	Textfile* textfile;
	std::string LoadingErrors;
	std::vector<Entity*> levelObjects;
	std::vector<Enemy*> enemies;
};

#endif // !LEVEL_H
