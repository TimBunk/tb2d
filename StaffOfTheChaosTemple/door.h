#ifndef DOOR_H
#define DOOR_H

#include "linkable.h"

enum Direction {
	north,
	east,
	south,
	west
};

class Door : public Linkable
{
public:
	Door(Direction direction, Camera* camera, b2World* world);
	~Door();

	void Update(double deltaTime);

	void Link(Linkable* linkable);

private:
	std::vector<Linkable*> linkables;
	glm::vec2 openPosition;
	Direction direction;
};

#endif // !DOOR_H
