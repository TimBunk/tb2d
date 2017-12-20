#include "crystal.h"

Crystal::Crystal(int width, int height, Texture* texture, Camera * camera, b2World * world) : Linkable::Linkable(width, height, texture, camera, world)
{
	color = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
}

Crystal::~Crystal()
{

}

void Crystal::Update(double deltaTime)
{
	if (hit) {
		enabled = true;
		hit = false;
		color = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
	}
	else {
		enabled = false;
		color = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
	}
}