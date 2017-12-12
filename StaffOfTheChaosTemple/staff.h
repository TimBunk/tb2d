#ifndef STAFF_H
#define STAFF_H

#include <gl\glew.h>
#include <glm-0.9.8.4\glm\glm.hpp>
#include <glm-0.9.8.4\glm\gtc\matrix_transform.hpp>
#include <glm-0.9.8.4\glm\gtc\type_ptr.hpp>
#include <Box2D/Box2D.h>

#include "sprite.h"
#include "laser.h"

class Staff : public Sprite
{
public:
	Staff(float laserRange, b2World* world, int width, int height, glm::vec2 pivot, Texture* texture, Camera* camera);
	~Staff();

	void Update(double deltaTime);
	void Shoot();

	void SetCamera(Camera* camera);

private:
	float laserRange;
	bool shooting;
	std::vector<Laser*> lasers;
	b2World* world;
};

#endif // !STAFF_H