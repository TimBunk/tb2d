#ifndef PLAYER_H
#define PLAYER_H

#include <cmath>

#include "b2entity.h"
#include "input.h"
#include "staff.h"

class Player : public B2Entity
{
public:
	Player(Input* input, ResourceManager* rm, Camera* camera, Shader* shader, b2World* world);
	~Player();

	void Update(double deltaTime);
	void SetCamera(Camera* camera);

private:
	Input* input;
	ResourceManager* rm;
	Staff* staff;
};

#endif // !PLAYER_H