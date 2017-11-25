#ifndef LASER_H
#define LASER_H

#include "sprite.h"
#include "raycastCallBack.h"

class Laser : public Sprite
{
public:
	Laser(b2World* world, Shader* debug, float radius, Texture* texture, Shader* shader, Camera* camera, bool HUD);
	~Laser();

	void Update(double deltaTime);
	void Draw();

	void SetDirection(glm::vec2 direction);

private:
	RaycastCallBack* raycast;
	glm::vec2 direction;
	b2World* world;
};

#endif // !LASER_H