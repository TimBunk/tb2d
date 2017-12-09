#ifndef PLAYER_H
#define PLAYER_H

#include <cmath>

#include "b2entity.h"
#include "input.h"
#include "staff.h"
#include "rotator.h"
#include "person.h"

class Player : public Person
{
public:
	Player(Input* input, int health, float speed, int damage, Camera* camera, b2World* world);
	~Player();

	void Update(double deltaTime);
	void SetCamera(Camera* camera);

private:
	Input* input;
	Staff* staff;
};

#endif // !PLAYER_H