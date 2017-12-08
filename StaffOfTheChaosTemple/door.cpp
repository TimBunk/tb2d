#include "door.h"

Door::Door(Direction direction, Camera * camera, Shader * shader, b2World * world) : Linkable::Linkable(camera, shader, world)
{
	this->direction = direction;
	openPosition = glm::vec2(0.0f, 0.0f);
}

Door::~Door()
{
}

void Door::Update(double deltaTime)
{
	bool isOpen = true;
	int size = linkables.size();
	// Check if all of the linkables are enabled
	for (int i = 0; i < size; i++) {
		if (linkables[i]->IsEnabled() == false) {
			isOpen = false;
		}
	}
	// if all linkables are enabled start opening the door
	if (isOpen) {
		if (enabled == false) {
			switch (direction)
			{
			case north:
				openPosition.y = localPosition.y + this->height;
				break;
			case east:
				openPosition.x = localPosition.x + this->width;
				break;
			case south:
				openPosition.y = localPosition.y - this->height;
				break;
			case west:
				openPosition.x = localPosition.x - this->width;
				break;
			}
		}
		// Open and enable the door so that everything that this door is linked with also know it is open
		enabled = true;
	}
	// Open the door by moving it its direction
	if (enabled) {
		switch (direction)
		{
		case north:
			if (this->GetGlobalPosition().y != openPosition.y) {
				localPosition.y = localPosition.y + (height / 2 * deltaTime);
				if (localPosition.y > openPosition.y)
					localPosition.y = openPosition.y;
			}
			break;
		case east:
			if (this->GetGlobalPosition().x != openPosition.x) {
				localPosition.x = localPosition.x + (width / 2 * deltaTime);
				if (localPosition.x > openPosition.x)
					localPosition.x = openPosition.x;
			}
			break;
		case south:
			if (this->GetGlobalPosition().y != openPosition.y) {
				localPosition.y = localPosition.y - (height / 2 * deltaTime);
				if (localPosition.y < openPosition.y)
					localPosition.y = openPosition.y;
			}
			break;
		case west:
			if (this->GetGlobalPosition().x != openPosition.x) {
				localPosition.x = localPosition.x - (width / 2 * deltaTime);
				if (localPosition.x < openPosition.x)
					localPosition.x = openPosition.x;
			}
			break;
		}
	}
}

void Door::Link(Linkable* linkable)
{
	linkables.push_back(linkable);
}