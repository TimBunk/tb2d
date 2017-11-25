#include "mirror.h"

Mirror::Mirror(Camera * camera, Shader * shader, b2World * world) : B2Entity::B2Entity(camera, shader, world)
{

}

Mirror::~Mirror()
{
}

void Mirror::Update(double deltaTime)
{
}
