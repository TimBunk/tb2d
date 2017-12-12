#include "linkable.h"

Linkable::Linkable(int width, int height, Texture* texture, Camera * camera, b2World * world) : B2Entity::B2Entity(width, height, glm::vec2(0,0), texture, camera, world)
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
