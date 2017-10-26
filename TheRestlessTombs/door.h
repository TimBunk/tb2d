#ifndef DOOR_H
#define DOOR_H

#include "b2entity.h"
#include "player.h"

enum Direction {
	north,
	east,
	south,
	west
};

class Door : public B2Entity {
public:
	Door(int roomNumber, Direction direction, Camera* camera, Shader* shader, b2World* world);
	~Door();

	void Update(float deltaTime);

	void CreateBody(int x, int y, float width);
private:
	Direction direction;
	int roomNumber;
};

#endif // !DOOR_H
