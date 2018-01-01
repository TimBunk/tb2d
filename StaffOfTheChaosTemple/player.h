#ifndef PLAYER_H
#define PLAYER_H

#include <cmath>

#include "input.h"
#include "staff.h"
#include "rotator.h"
#include "person.h"

class Player : public Person
{
public:
	Player(Camera* camera, float health, float speed, float damage, int width, int height, unsigned int textureID, b2World* world);
	~Player();

	void Update(double deltaTime);

private:
	Staff* staff;
	Camera* camera;
};

#endif // !PLAYER_H