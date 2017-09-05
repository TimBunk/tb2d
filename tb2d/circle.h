#ifndef CIRCLE_H
#define CIRCLE_H

#include <iostream>

#include "shader.h"
#include "OBJloader.h"

#include <gl\glew.h>
#include <glfw3.h>
#include <glm-0.9.8.4\glm\glm.hpp>
#include <glm-0.9.8.4\glm\gtc\matrix_transform.hpp>
#include <glm-0.9.8.4\glm\gtc\type_ptr.hpp>
#include <Box2D\Box2D.h>


class Circle {
public:
	Circle(int x, int y, int radius, bool dynamic, float p2m, b2World* world);
	~Circle();

	void Draw();
	glm::vec3 GetPositionInPixels(float m2p);
	// Note that the angle is in radians
	float GetAngle();

private:
	GLuint VBO, VAO, EBO;
	b2Body* body;
	Mesh* mesh;
};

#endif // !CIRCLE_H