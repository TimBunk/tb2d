#include "crystal.h"

Crystal::Crystal(int uniqueID, int width, int height, unsigned int textureID, b2World* world) : B2Entity::B2Entity(width, height, textureID, world)
{
	this->uniqueID = uniqueID;
	enabled = false;
	hit = false;
}

Crystal::~Crystal()
{

}

void Crystal::Update(double deltaTime)
{
	if (hit) {
		enabled = true;
		hit = false;
		color = glm::vec4(0.5f, 0.5f, 0.5f, 0.0f);
	}
	else {
		enabled = false;
		color = glm::vec4(0.0f, 0.0f, 0.0f, 0.0f);
	}
}