#ifndef LASER_H
#define LASER_H

#include "crystal.h"
#include "box2Dclasses/raycast.h"

class Laser : public Sprite
{
public:
	Laser(float damage, float laserRange, int width, int height, unsigned int texture, b2World* world);
	~Laser();

	void Update(double deltaTime);
	void Draw();

	void UpdateParticles(double deltaTime);

	void SetDirection(glm::vec2 direction) { this->direction = direction; };
	bool Hit() { return hit; };
	glm::vec2 GetHitPosition() { return hitPosition; };
	glm::vec2 GetReflection() { return reflection; };

private:
	float damage;
	float laserRange;
	ParticleRenderer* pr;

	bool hit;
	Raycast* raycast;
	glm::vec2 direction;
	glm::vec2 hitPosition;
	glm::vec2 reflection;

	std::vector<Particle> particles;
	std::vector<float> randomLengths;
	std::vector<glm::vec2> randomOffsets;
};

#endif // !LASER_H