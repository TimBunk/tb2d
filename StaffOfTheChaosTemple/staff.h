#ifndef STAFF_H
#define STAFF_H

#include <Box2D/Box2D.h>

#include "laser.h"

class Staff : public Sprite
{
public:
	Staff(float damage, float laserRange, int width, int height, unsigned int textureID, b2World* world);
	~Staff();

	void Update(double deltaTime);
	void Shoot() { shooting = true; }

private:
	float damage;
	float laserRange;
	bool shooting;
	std::vector<Laser*> lasers;
	b2World* world;
};

#endif // !STAFF_H