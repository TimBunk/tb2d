#ifndef DOOR_H
#define DOOR_H

#include "crystal.h"

class Door : public B2Entity
{
public:
	Door(int width, int height, unsigned int textureID, b2World* world);
	~Door();

	void Update(double deltaTime);
	void Link(Crystal* linkable);

private:
	bool enabled;
	std::vector<Crystal*> linkables;
	glm::vec2 direction;
	glm::vec2 openPosition;
	bool xDirectionPositive;
	bool yDirectionPositive;
};

#endif // !DOOR_H
