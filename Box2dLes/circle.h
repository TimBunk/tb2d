#ifndef CIRCLE_H
#define CIRCLE_H

#include <iostream>

#include "debugRenderer.h"
#include "b2entity.h"
#include "window.h"


#include <GL/glew.h>
#include <glm-0.9.8.4/glm/glm.hpp>
#include <glm-0.9.8.4/glm/gtc/matrix_transform.hpp>
#include <glm-0.9.8.4/glm/gtc/type_ptr.hpp>
#include <Box2D/Box2D.h>


class Circle : public B2Entity {
public:
	Circle(Camera* camera, Shader* shader, Shader* debug);
    ~Circle();
	
	void Update(float deltaTime);
	void Draw();

    void CreateBody(int x, int y, int radius, b2World* world);

private:
	DebugRenderer* dr;

	GLuint VBO, VAO, EBO;
	b2World* world;
	b2Body* body;
	b2Fixture* fixture;
};

#endif // !CIRCLE_H
