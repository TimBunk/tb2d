#ifndef LASER_H
#define LASER_H

#include "crystal.h"
#include "raycast.h"

class Laser : public Sprite
{
public:
	Laser(float damage, int width, int height, unsigned int texture, b2World* world);
	~Laser();

	void Update(double deltaTime);
	void DrawParticles(double deltaTime);

	void SpawnParticles();

	void SetDirection(glm::vec2 direction) { this->direction = direction; };
	bool Hit() { return hit; };
	glm::vec2 GetHitPosition() { return hitPosition; };
	glm::vec2 GetReflection() { return reflection; };

private:
	float damage;
	ParticleRenderer* pr;

	bool hit;
	Raycast* raycast;
	glm::vec2 direction;
	glm::vec2 hitPosition;
	glm::vec2 reflection;

	unsigned int particleTextureID;
	std::vector<Particle> particles;
};

#endif // !LASER_H