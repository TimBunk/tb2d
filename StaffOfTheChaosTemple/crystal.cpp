#include "crystal.h"

Crystal::Crystal(int uniqueID, int width, int height, unsigned int textureID, b2World* world) : B2Entity::B2Entity(width, height, textureID, world)
{
	// Initialize the variables
	this->uniqueID = uniqueID;
	enabled = false;
	hit = false;
	activeColor = glm::vec4(0, 0, 0, 1);
}

Crystal::~Crystal()
{

}

void Crystal::Update(double deltaTime)
{
	// If the crystal is being hit enable it and set a bright color over it
	if (hit) {
		enabled = true;
		hit = false;
		color = glm::vec4(0.5f, 0.5f, 0.5f, 0.0f);
	}
	else {
		enabled = false;
		color = activeColor;
	}
}

void Crystal::SetColor(glm::vec4 color)
{
	this->color = color;
	activeColor = color;
}
