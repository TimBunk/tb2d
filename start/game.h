#ifndef GAME_H
#define GAME_H

#include "scene.h"
#include "text.h"
#include "player.h"

class Game : public Scene{
public:
	Game(Camera* camera);
	void Update();
};

#endif // !GAME_H
