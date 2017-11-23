#ifndef LASER_H
#define LASER_H

#include "b2entity.h"
#include "raycastCallBack.h"

class Laser : public B2Entity
{
public:
	Laser(Shader* debug, Camera* camera, Shader* shader, b2World* world);
	~Laser();

	void Update(glm::vec2 direction);

private:
	RaycastCallBack* raycast;
};

#endif // !LASER_H