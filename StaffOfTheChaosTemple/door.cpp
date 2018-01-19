#include "door.h"

Door::Door(int width, int height, unsigned int textureID, b2World* world) : B2Entity::B2Entity(width, height, textureID, world)
{
	direction = glm::vec2(0.0f, 0.0f);
	xDirectionPositive = false;
	yDirectionPositive = false;
	enabled = false;
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
			direction.x = glm::cos(localAngle);
			direction.y = glm::sin(localAngle);
			direction = glm::normalize(direction);
			direction *= width;
			direction *= -1;
			if (direction.x > 0) {
				xDirectionPositive = true;
			}
			else {
				xDirectionPositive = false;
			}
			if (direction.y > 0) {
				yDirectionPositive = true;
			}
			else {
				yDirectionPositive = false;
			}
			openPosition = direction + localPosition;
		}
		// Open and enable the door so that everything that this door is linked with also know it is open
		enabled = true;
	}
	// Open the door by moving it its direction
	if (enabled) {
		if (localPosition != openPosition) {
			glm::vec2 tmpDirection = direction;
			tmpDirection = glm::normalize(tmpDirection);
			tmpDirection *= width/2 * deltaTime;
			this->localPosition += tmpDirection;
			if (xDirectionPositive == true && localPosition.x > openPosition.x) {
				localPosition.x = openPosition.x;
			}
			else if (xDirectionPositive == false && localPosition.x < openPosition.x) {
				localPosition.x = openPosition.x;
			}
			if (yDirectionPositive == true && localPosition.y > openPosition.y) {
				localPosition.y = openPosition.y;
			}
			else if (yDirectionPositive == false && localPosition.y < openPosition.y) {
				localPosition.y = openPosition.y;
			}
		}
	}
}

void Door::Link(Crystal* linkable)
{
	linkables.push_back(linkable);
}