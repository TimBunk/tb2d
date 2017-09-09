#include "debugRenderer.h"

DebugRenderer::DebugRenderer(glm::mat4 projection, glm::vec4 color)
{
	shader = new Shader("shaders//debugRenderer.vs", "shaders//debugRenderer.fs");
	shader->Use();
	shader->SetMatrix4("projection", projection);
	shader->SetVec4Float("color", color);
	
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

	// set the vertices
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	glBindVertexArray(0);
}

DebugRenderer::~DebugRenderer()
{
	delete shader;
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
}

void DebugRenderer::DrawBox(b2Vec2* points)
{
	verts.resize(verts.size() + 4);

	for (int i = 0; i < 4; i++) {
		verts[i] = glm::vec3(points[i].x, points[i].y, 1.0f);
	}
	indices.reserve(8);

	indices.push_back(0);
	indices.push_back(1);

	indices.push_back(1);
	indices.push_back(2);

	indices.push_back(2);
	indices.push_back(3);

	indices.push_back(3);
	indices.push_back(0);
}

void DebugRenderer::DrawCircle(const glm::vec3 & center, float radius)
{
	int numVerts = 100;
	verts.resize(numVerts);
	for (int i = 0; i < numVerts; i++) {
		float angle = ((float)i / numVerts) * M_PI * 2.0f;
		verts[i].x = cos(angle) * radius;
		verts[i].y = sin(angle) * radius;
	}
	indices.reserve(numVerts * 2.0f);
	for (int i = 0; i < numVerts - 1; i++) {
		indices.push_back(i);
		indices.push_back(i + 1);
	}
	indices.push_back(numVerts - 1);
	indices.push_back(0);
}

void DebugRenderer::Init()
{

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, verts.size() * sizeof(glm::vec3), nullptr, GL_DYNAMIC_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0, verts.size() * sizeof(glm::vec3), verts.data());
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), nullptr, GL_DYNAMIC_DRAW);
	glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, indices.size() * sizeof(GLuint), indices.data());
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);


	numElements = indices.size();
	indices.clear();
	verts.clear();
}

void DebugRenderer::Render(glm::mat4& view, glm::mat4& model, float lineWidth)
{
	shader->Use();
	shader->SetMatrix4("model", model);
	shader->SetMatrix4("view", view);
	glLineWidth(lineWidth);
	glBindVertexArray(VAO);
	glDrawElements(GL_LINES, numElements, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}
