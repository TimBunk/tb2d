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
	DebugRenderer(Camera* camera, Shader* debug, glm::vec4 color);
	~DebugRenderer();

	void DrawBox(b2Vec2* points);
	void DrawCircle(const glm::vec3& center, float radius);
	void Init();
	void Render(glm::mat4 model, float lineWidth);

private:
	Camera* camera;
	Shader* shader;
	glm::vec4 color;

	std::vector<glm::vec3> verts;
	std::vector<GLuint> indices;
	GLuint VBO, VAO, EBO;
	int numElements;
};

#endif // !DEBUGRENDERER_H
