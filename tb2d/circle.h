#ifndef CIRCLE_H
#define CIRCLE_H

#include <iostream>

#include "shader.h"
#include "OBJloader.h"
#include "debugRenderer.h"

#include <GL/glew.h>
#include <glm-0.9.8.4/glm/glm.hpp>
#include <glm-0.9.8.4/glm/gtc/matrix_transform.hpp>
#include <glm-0.9.8.4/glm/gtc/type_ptr.hpp>
#include <Box2D/Box2D.h>


class Circle {
public:
	Circle(int x, int y, int radius, bool dynamic, float p2m, b2World* world, glm::mat4 projection);
	~Circle();

	void Draw(glm::mat4 view, Shader* shader, float m2p);
	glm::vec3 GetPositionInPixels(float m2p);
	// Note that the angle is in radians
	float GetAngle();

private:
	glm::mat4 projection;
	DebugRenderer* dr;

	GLuint VBO, VAO, EBO;
	b2World* world;
	b2Body* body;
	b2Fixture* fixture;
};

#endif // !CIRCLE_H
