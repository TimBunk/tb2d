#include "linkable.h"

Linkable::Linkable(Camera * camera, Shader * shader, b2World * world) : B2Entity::B2Entity(camera, shader, world)
{
	enabled = false;
}

Linkable::~Linkable()
{
}

void Linkable::Enable(bool state)
{
	enabled = state;
}

bool Linkable::IsEnabled()
{
	if (enabled) {
		enabled = false;
		return true;
	}
	return false;
}
