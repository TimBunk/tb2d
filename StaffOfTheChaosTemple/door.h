#ifndef DOOR_H
#define DOOR_H

#include "linkable.h"

class Door : public Linkable
{
public:
	Door(int width, int height, unsigned int textureID, b2World* world);
	~Door();

	void Update(double deltaTime);
	void Link(Linkable* linkable);

private:
	std::vector<Linkable*> linkables;
	glm::vec2 direction;
	glm::vec2 openPosition;
	bool xDirectionPositive;
	bool yDirectionPositive;
};

#endif // !DOOR_H
