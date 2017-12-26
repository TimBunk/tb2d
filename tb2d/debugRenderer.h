#ifndef DEBUGRENDERER_H
#define DEBUGRENDERER_H
#define _USE_MATH_DEFINES

#include <iostream>
#include <vector>
#include <math.h>

#include "shader.h"
#include "camera.h"
#include "resourceManager.h"

#include <GL/glew.h>
#include <glm-0.9.8.4/glm/glm.hpp>
#include <glm-0.9.8.4/glm/gtc/matrix_transform.hpp>
#include <glm-0.9.8.4/glm/gtc/type_ptr.hpp>
#include <Box2D/Box2D.h>

class B2Entity;

class  DebugRenderer
{
public:
	static void Initialize();
	static void Destroy();

	static void Clear();
	static void AddBox(int width, int height, glm::vec2 pivot, glm::mat4 model, glm::vec3 color);
	static void AddCircle(int radius, glm::mat4 model, glm::vec3 color);
	static void Render(Camera* camera);

private:

	static DebugRenderer* debugRenderer;
	DebugRenderer();
	virtual ~DebugRenderer();

	//void DrawBox(GLfloat* vertices);
	//void DrawCircle(glm::vec2 center, float radius);

	Shader* shader;
	GLuint VAO_box, VBO_box, EBO_box;
	GLuint VBO_boxModel;
	GLuint VBO_boxColor;
	std::vector<glm::vec2> boxesPosition;
	std::vector<glm::vec3> boxesColor;
	std::vector<glm::mat4> boxesModel;
	int boxesCount;
	GLuint VAO_circle, VBO_circle, EBO_circle;
	std::vector<glm::vec3> circlesColor;
	std::vector<glm::mat4> circlesModel;
	int circlesCount;
};

#endif // !DEBUGRENDERER_H
