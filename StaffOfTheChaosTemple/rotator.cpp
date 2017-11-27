#include "rotator.h"

Rotator::Rotator(Camera * camera, Shader * shader, b2World * world) : B2Entity::B2Entity(camera, shader, world)
{

}

Rotator::~Rotator()
{

}

void Rotator::Update(double deltaTime)
{
	//localAngle = GetAngleB2body();
}
