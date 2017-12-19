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
	Player(int health, float speed, int damage, int width, int height, Texture* texture, Camera* camera, b2World* world);
	~Player();

	void Update(double deltaTime);
	void SetCamera(Camera* camera);

private:
	Staff* staff;
};

#endif // !PLAYER_H