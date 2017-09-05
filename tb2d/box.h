#ifndef BOX_H
#define BOX_H

#include <iostream>

#include "shader.h"

#include <gl\glew.h>
#include <glfw3.h>
#include <glm-0.9.8.4\glm\glm.hpp>
#include <glm-0.9.8.4\glm\gtc\matrix_transform.hpp>
#include <glm-0.9.8.4\glm\gtc\type_ptr.hpp>
#include <Box2D\Box2D.h>

class Box {
public:
	Box(int x, int y, int w, int h, bool dyn, float p2m, b2World* world);
	~Box();

	void Draw();
	glm::vec3 GetPositionInPixels(float m2p);
	// Note that the angle is in radians
	float GetAngle();

private:
	GLuint VBO, VAO, EBO;
	b2World* world;
	b2Body* body;
	b2Fixture* fixture;
};

#endif // !BOX_H
