#include "debugRenderer.h"

DebugRenderer::DebugRenderer(Camera* camera, glm::vec3 color)
{
	this->camera = camera;
	this->color = color;
	shader = new Shader("shaders\\debugRenderer.vs", "shaders\\debugRenderer.fs");
	VAO = 0;
	VBO = 0;
	EBO = 0;
}

DebugRenderer::~DebugRenderer()
{
	delete shader;
	if (VAO != 0) {
		glDeleteVertexArrays(1, &VAO);
		glDeleteBuffers(1, &VBO);
		glDeleteBuffers(1, &EBO);
	}
}

void DebugRenderer::DrawBox(GLfloat* vertices)
{
	GLuint * indices = new GLuint[8];
	indices[0] = 0; indices[1] = 1; 
	indices[2] = 1; indices[3] = 2;
	indices[4] = 2; indices[5] = 3;
	indices[6] = 3; indices[7] = 0;

	if (VAO != 0) {
		glDeleteVertexArrays(1, &VAO);
		glDeleteBuffers(1, &VBO);
		glDeleteBuffers(1, &EBO);
	}
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 8, &vertices[0], GL_STATIC_DRAW);
	
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * 8, &indices[0], GL_STATIC_DRAW);

	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	glBindVertexArray(0);

	numElements = 8;
	delete indices;
}

void DebugRenderer::DrawCircle(glm::vec2 center, float radius) 
{
	int verticesAmount = 180;
	GLfloat* vertices = new GLfloat[verticesAmount * 2];
	for (int i = 0; i < verticesAmount * 2; i++) {
		float angle = ((float)i / verticesAmount * 2) * M_PI * 2.0f;
		vertices[i] = glm::cos(angle) * radius;
		i += 1;
		vertices[i] = glm::sin(angle) * radius;
	}
	GLuint* indices = new GLuint[verticesAmount * 2];

	for (int i = 0; i < verticesAmount - 1; i++) {
		indices[i] = i;
		indices[i + 1] = i + 1;
	}

	if (VAO != 0) {
		glDeleteVertexArrays(1, &VAO);
		glDeleteBuffers(1, &VBO);
		glDeleteBuffers(1, &EBO);
	}
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * verticesAmount * 2, &vertices[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * verticesAmount * 2, &indices[0], GL_STATIC_DRAW);

	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	glBindVertexArray(0);

	numElements = verticesAmount * 2;
	delete vertices;
	delete indices;
}

void DebugRenderer::Render(glm::mat4 model, float lineWidth)
{
	shader->Use();
	shader->SetMatrix4("model", model);
	shader->SetMatrix4("projection", camera->GetProjectionMatrix());
	shader->SetMatrix4("view", camera->GetViewMatrix());
	shader->SetVec3Float("color", color);
	glLineWidth(lineWidth);
	glBindVertexArray(VAO);
	glDrawElements(GL_LINES, numElements, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}
