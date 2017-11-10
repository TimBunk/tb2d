/*#ifndef SHAPE_H
#define SHAPE_H

#include <iostream>

#include "shader.h"
#include "debugRenderer.h"

#include <GL/glew.h>
#include <glm-0.9.8.4/glm/glm.hpp>
#include <glm-0.9.8.4/glm/gtc/matrix_transform.hpp>
#include <glm-0.9.8.4/glm/gtc/type_ptr.hpp>
#include <Box2D/Box2D.h>

class Shape {
public:
	Shape();
	virtual ~Shape();

	void Draw();
	void CreateBox(int w, int h, bool dyn, b2World* world);
private:
	b2Vec2 point[4];
	DebugRenderer* dr;

	GLuint VBO, VAO, EBO;
	b2World* world;
	b2Body* body;
	b2Fixture* fixture;

};

#endif // !SHAPE_H
*/
