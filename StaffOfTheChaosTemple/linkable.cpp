#include "linkable.h"

Linkable::Linkable(int width, int height, unsigned int textureID, b2World* world) : B2Entity::B2Entity(width, height, textureID, world)
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
