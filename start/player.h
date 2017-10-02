#ifndef PLAYER_H
#define PLAYER_H

#include "entity.h"
#include "configure.h"

class Player : public Entity {
public:

	Player(b2World* world, Camera* camera);
	~Player();

	void Update(float deltaTime);

private:

};

#endif // !PLAYER_H
