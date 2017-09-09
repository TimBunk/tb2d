#ifndef BOX_H
#define BOX_H

#include <iostream>

#include "shader.h"
#include "debugRenderer.h"

#include <gl\glew.h>
#include <glfw3.h>
#include <glm-0.9.8.4\glm\glm.hpp>
#include <glm-0.9.8.4\glm\gtc\matrix_transform.hpp>
#include <glm-0.9.8.4\glm\gtc\type_ptr.hpp>
#include <Box2D\Box2D.h>

class Box {
public:
	Box(int x, int y, int w, int h, bool dyn, float p2m, b2World* world, glm::mat4 projection);
	~Box();

	void Draw(glm::mat4 view, Shader* shader, float m2p);
	glm::vec3 GetPositionInPixels(float m2p);
	// Note that the angle is in radians
	float GetAngle();

private:
	b2Vec2 point[4];
	glm::mat4 projection;
	DebugRenderer* dr;

	GLuint VBO, VAO, EBO;
	b2World* world;
	b2Body* body;
	b2Fixture* fixture;
};

#endif // !BOX_H
