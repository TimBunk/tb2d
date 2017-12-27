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
	
	static void Submit(B2Entity* b2entity);
	static void Render(Camera* camera);
	static void Line(glm::vec2 point1, glm::vec2 point2, glm::vec3 color);

private:
	DebugRenderer();
	virtual ~DebugRenderer();

	void AddBox(B2Entity* b2entity);
	void AddCircle(B2Entity* b2entity);

	void DrawBoxes();
	void DrawCircles();
	void DrawLines(Camera* camera);

	static DebugRenderer* debugRenderer;
	Shader* shader;
	Shader* shaderLine;

	// The VBO_position and the VBO_color are buffers that are both being shared by the box and the line
	GLuint VBO_position;
	GLuint VBO_color;
	// box
	GLuint VAO_box;
	GLuint VBO_boxModel;
	std::vector<glm::vec2> boxesPosition;
	std::vector<glm::vec3> boxesColor;
	std::vector<glm::mat4> boxesModel;
	int boxesCount;
	// circle
	GLuint VAO_circle;
	GLuint VBO_circlePosition;
	GLuint EBO_circlePosition;
	GLuint VBO_circleColor;
	GLuint VBO_circleModel;
	std::vector<glm::vec3> circlesColor;
	std::vector<glm::mat4> circlesModel;
	int circlesCount;
	// line
	GLuint VAO_line;
	std::vector<glm::vec2> linesPosition;
	std::vector<glm::vec3> linesColor;
	int linesCount;
};

#endif // !DEBUGRENDERER_H
