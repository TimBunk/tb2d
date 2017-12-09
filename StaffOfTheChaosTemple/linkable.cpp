#include "linkable.h"

Linkable::Linkable(Camera * camera, b2World * world) : B2Entity::B2Entity(camera, world)
{
	enabled = false;
	hit = false;
}

Linkable::~Linkable()
{
}

void Linkable::Hit()
{
	hit = true;
}

bool Linkable::IsEnabled()
{
	return enabled;
}
