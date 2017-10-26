#ifndef WALL_H
#define WALL_H

#include "b2entity.h"
#include "debugRenderer.h"

class Wall : public B2Entity {
public:
	// Visible means if the wall should be rendered
	Wall(bool visible, Camera* camera, Shader* shader, b2World* world);
	~Wall();

	void Update(float deltaTime);
	void Draw();
	void CreateBody(int x, int y, int w, int h);

	bool visible;
private:
	DebugRenderer* dr;
};

#endif // !WALL_H
