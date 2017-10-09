#ifndef DOOR_H
#define DOOR_H

#include "b2entity.h";
#include "player.h"

enum Direction {
	north,
	east,
	south,
	west
};

class Door : public B2Entity {
public:
	Door(Camera* camera, Shader* shader, int roomNumber);
	~Door();

	void Update(float deltaTime);

	void CreateBody(int x, int y, Direction direction, float width, b2World* world);
private:
	Direction direction;
	int roomNumber;
};

#endif // !DOOR_H
