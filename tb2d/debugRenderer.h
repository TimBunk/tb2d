#ifndef DEBUGRENDERER_H
#define DEBUGRENDERER_H
#define _USE_MATH_DEFINES

#include <iostream>
#include <vector>
#include <math.h>

#include "shader.h"
#include "camera.h"

#include <GL/glew.h>
#include <glm-0.9.8.4/glm/glm.hpp>
#include <glm-0.9.8.4/glm/gtc/matrix_transform.hpp>
#include <glm-0.9.8.4/glm/gtc/type_ptr.hpp>
#include <Box2D/Box2D.h>


class  DebugRenderer
{
public:
	DebugRenderer(Camera* camera, glm::vec3 color);
	virtual ~DebugRenderer();

	void DrawBox(GLfloat* vertices);
	void DrawCircle(glm::vec2 center, float radius);

	void Render(glm::mat4 model, float lineWidth);

private:

	Camera* camera;
	Shader* shader;
	glm::vec3 color;
	GLuint VBO, VAO, EBO;
	int numElements;
};

#endif // !DEBUGRENDERER_H
