#ifndef LEVEL_H
#define LEVEL_H

#include "scene.h"
#include "mirror.h"
#include "crystal.h"
#include "door.h"
#include "player.h"
#include "contactListener.h"
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
	~Level();

	virtual void Update(double deltaTime);
	bool IsFinished();
	bool IsPlayerAlive() { return player->IsAlive(); }
	std::string GetLoadingErrors() { return LoadingErrors; }

	void LoadFile(std::string filename);
	void LoadTutorial();

private:
	void Init();
	void ReadLine(std::string line);
	// Healthbar player
	Sprite* greenHealthbarPlayer;
	Sprite* redHealthbarPlayer;
	// World
	b2World* world;
	ContactListener* contactListener;
	// Player and finish
	Player* player;
	B2Entity* finish;
	bool finished;
	// Variables for loading the level
	Textfile* textfile;
	std::string LoadingErrors;
	std::vector<Entity*> levelObjects;
	std::vector<Enemy*> enemies;
	std::vector<Text*> textVector;
	// Tmp vectors for creating the links between a door and a crystal
	std::vector<Link> tmpLinks;
	std::vector<Crystal*> tmpCrystals;
};

#endif // !LEVEL_H
