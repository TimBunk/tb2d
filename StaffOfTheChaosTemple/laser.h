#ifndef LASER_H
#define LASER_H

#include "crystal.h"
#include "box2Dclasses/raycast.h"

class Laser : public Sprite
{
public:
	Laser(int width, int height, unsigned int texture, b2World* world);
	~Laser();

	void Update(double deltaTime);

	void SetDirection(glm::vec2 direction);
	bool Hit();
	glm::vec2 GetHitPosition();
	glm::vec2 GetReflection();

private:
	bool hit;
	Raycast* raycast;
	glm::vec2 direction;
	b2Vec2 hitPosition;
	b2Vec2 reflection;
};

#endif // !LASER_H