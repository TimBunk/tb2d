#ifndef WALL_H
#define WALL_H

#include "b2entity.h"

class Wall : public B2Entity {
public:
	// Visible means if the wall should be rendered
	Wall(Camera* camera, Shader* shader, bool visible);
	~Wall();

	void Update(float deltaTime);

	bool visible;
private:

};

#endif // !WALL_H
