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
#include "text.h"

struct Link {
	Door* door = nullptr;
	std::vector<int> crystalIDs;
	std::vector<Crystal*> crystals;
};

class Level : public Scene
{
public:
	Level(int screenWidthCamera, int screenHeightCamera);
	virtual ~Level();

	virtual void Update(double deltaTime);
	bool IsFinished();
	bool IsPlayerAlive() { return player->IsAlive(); }
	std::string GetLoadingErrors() { return LoadingErrors; }

	void LoadFile(std::string filename);
	void LoadTutorial();

protected:

	Sprite* greenHealthbarPlayer;
	Sprite* redHealthbarPlayer;

	b2World* world;
	ContactListener* contactListener;
	Player* player;
	B2Entity* finish;
	bool finished;

private:
	void Init();
	void ReadLine(std::string line);

	Textfile* textfile;
	std::string LoadingErrors;
	std::vector<Entity*> levelObjects;
	std::vector<Enemy*> enemies;
	std::vector<Text*> textVector;

	std::vector<Link> tmpLinks;
	std::vector<Crystal*> tmpCrystals;
};

#endif // !LEVEL_H
