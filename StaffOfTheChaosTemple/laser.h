#ifndef LASER_H
#define LASER_H

#include "sprite.h"
#include "raycastCallBack.h"

class Laser : public Sprite
{
public:
	Laser(b2World* world, Shader* debug, float radius, Texture* texture, Camera* camera, bool HUD);
	~Laser();

	void Update(double deltaTime);
	void Draw();

	void SetDirection(glm::vec2 direction);
	bool Hit();
	glm::vec2 GetHitPosition();
	glm::vec2 GetReflection();

private:
	bool hit;
	RaycastCallBack* raycast;
	glm::vec2 direction;
	b2Vec2 hitPosition;
	b2Vec2 reflection;
	GLuint VAO, VBO;
	b2World* world;
};

#endif // !LASER_H