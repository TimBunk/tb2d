#include "rotator.h"

Rotator::Rotator(Camera * camera, Shader * shader, b2World * world) : B2Entity::B2Entity(camera, shader, world)
{
	rotation = 0.0f;
}

Rotator::~Rotator()
{

}

void Rotator::Update(double deltaTime)
{
	
}

void Rotator::Rotate(bool clockWise, float degrees)
{
	if (clockWise) {
		rotation += glm::radians(degrees);
	}
	else {
		rotation -= glm::radians(degrees);
	}
	if (rotation / M_PI >= 1) {
		rotation -= (M_PI*2);
	}
	else if (rotation < (M_PI * -1)) {
		rotation += (M_PI * 2);
	}
}

float Rotator::GetRotation()
{
	return rotation;
}

void Rotator::SetRotation(float degrees)
{
	rotation = glm::radians(degrees);
}
