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
	void CreateBody(int x, int y, int w, int h, bool dynamic, bool sensor);

private:
	Input* input;
	ResourceManager* rm;
	Staff* staff;
};

#endif // !PLAYER_H