#ifndef WALL_H
#define WALL_H

#include "b2entity.h"
#include "debugRenderer.h"

class Wall : public B2Entity {
public:
	// Visible means if the wall should be rendered
	Wall(Camera* camera, Shader* shader, bool visible);
	~Wall();

	void Update(float deltaTime);
	void CreateBody(int x, int y, int w, int h, bool dynamic, b2World* world);

	bool visible;
private:
	DebugRenderer* dr;
};

#endif // !WALL_H
