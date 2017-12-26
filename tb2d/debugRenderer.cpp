#include "debugRenderer.h"
#include "box2Dclasses/b2entity.h"

DebugRenderer* DebugRenderer::debugRenderer = nullptr;

void DebugRenderer::Initialize()
{
	if (DebugRenderer::debugRenderer == nullptr) {
		DebugRenderer::debugRenderer = new DebugRenderer();
	}
}

void DebugRenderer::Destroy()
{
	if (DebugRenderer::debugRenderer != nullptr) {
		delete DebugRenderer::debugRenderer;
		DebugRenderer::debugRenderer = nullptr;
	}
}

void DebugRenderer::Clear()
{
	DebugRenderer::debugRenderer->boxesPosition.clear();
	DebugRenderer::debugRenderer->boxesModel.clear();
	DebugRenderer::debugRenderer->boxesColor.clear();
	DebugRenderer::debugRenderer->boxesCount = 0;
	DebugRenderer::debugRenderer->circlesModel.clear();
	DebugRenderer::debugRenderer->circlesColor.clear();
	DebugRenderer::debugRenderer->circlesCount = 0;
}

void DebugRenderer::AddBox(int width, int height, glm::vec2 pivot, glm::mat4 model, glm::vec3 color)
{
	/*GLfloat vertices[]{
		-0.5f, -0.5f, // lower left
		0.5f, -0.5f, // lower right
		0.5f, 0.5f, // upper right
		-0.5f, 0.5f // upper left
	};*/
	DebugRenderer::debugRenderer->boxesPosition.push_back(glm::vec2(-0.5f + pivot.x, -0.5f + pivot.y)); // lower left
	DebugRenderer::debugRenderer->boxesPosition.push_back(glm::vec2(0.5f + pivot.x, -0.5f + pivot.y)); // lower right
	DebugRenderer::debugRenderer->boxesPosition.push_back(glm::vec2(0.5f + pivot.x, 0.5f + pivot.y)); // upper right
	DebugRenderer::debugRenderer->boxesPosition.push_back(glm::vec2(-0.5f + pivot.x, 0.5f + pivot.y)); // upper left

	model = glm::scale(model, glm::vec3(width, height, 0.0f));
	DebugRenderer::debugRenderer->boxesModel.push_back(model);
	DebugRenderer::debugRenderer->boxesColor.push_back(color);
	DebugRenderer::debugRenderer->boxesCount++;
}

void DebugRenderer::AddCircle(int radius, glm::mat4 model, glm::vec3 color)
{
	model = glm::scale(model, glm::vec3(radius, radius, 0.0f));
	DebugRenderer::debugRenderer->circlesModel.push_back(model);
	DebugRenderer::debugRenderer->circlesColor.push_back(color);
	DebugRenderer::debugRenderer->circlesCount++;
}

void DebugRenderer::Render(Camera * camera)
{
	if (DebugRenderer::debugRenderer->boxesPosition.size() == 0) { return; }
	DebugRenderer::debugRenderer->shader->Use();
	DebugRenderer::debugRenderer->shader->SetMatrix4("projection", camera->GetProjectionMatrix());
	DebugRenderer::debugRenderer->shader->SetMatrix4("view", camera->GetViewMatrix());

	// Bind the VAO
	glBindVertexArray(DebugRenderer::debugRenderer->VAO_box);
	//glBindTexture(GL_TEXTURE_2D, texture->GetId());

	// Fill all of the buffers with their data
	glBindBuffer(GL_ARRAY_BUFFER, DebugRenderer::debugRenderer->VBO_box);
	glBufferData(GL_ARRAY_BUFFER, DebugRenderer::debugRenderer->boxesPosition.size() * sizeof(glm::vec2), &DebugRenderer::debugRenderer->boxesPosition[0], GL_STREAM_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, DebugRenderer::debugRenderer->VBO_boxModel);
	glBufferData(GL_ARRAY_BUFFER, DebugRenderer::debugRenderer->boxesModel.size() * sizeof(glm::mat4), &DebugRenderer::debugRenderer->boxesModel[0], GL_STREAM_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, DebugRenderer::debugRenderer->VBO_boxColor);
	glBufferData(GL_ARRAY_BUFFER, DebugRenderer::debugRenderer->boxesColor.size() * sizeof(glm::vec3), &DebugRenderer::debugRenderer->boxesColor[0], GL_STREAM_DRAW);

	// Unbind the buffer
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glDrawElementsInstanced(GL_LINES, 8, GL_UNSIGNED_INT, 0, DebugRenderer::debugRenderer->boxesCount);

	// Unbind the VAO
	glBindVertexArray(0);
}

DebugRenderer::DebugRenderer()
{
	boxesCount = 0;
	circlesCount = 0;
	VAO_circle = 0;
	VBO_circle = 0;
	EBO_circle = 0;
	/*GLfloat vertices[]{
		-0.5f, -0.5f, // lower left
		0.5f, -0.5f, // lower right
		0.5f, 0.5f, // upper right
		-0.5f, 0.5f // upper left
	};*/

	GLuint indices[] = {
		0, 1, 1, 2,
		2, 3, 3, 0
	};

	glGenVertexArrays(1, &VAO_box);
	glGenBuffers(1, &VBO_box);
	glGenBuffers(1, &EBO_box);

	glBindVertexArray(VAO_box);

	glBindBuffer(GL_ARRAY_BUFFER, VBO_box);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO_box);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * 8, &indices[0], GL_STREAM_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(glm::vec2), (GLvoid*)0);

	// Gererate the model buffer
	glGenBuffers(1, &VBO_boxModel);
	glBindBuffer(GL_ARRAY_BUFFER, VBO_boxModel);
	// set attribute pointers for matrix (4 times vec4)
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (GLvoid*)0);
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (GLvoid*)(sizeof(glm::vec4)));
	glEnableVertexAttribArray(3);
	glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (GLvoid*)(2 * sizeof(glm::vec4)));
	glEnableVertexAttribArray(4);
	glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (GLvoid*)(3 * sizeof(glm::vec4)));

	glVertexAttribDivisor(1, 1);
	glVertexAttribDivisor(2, 1);
	glVertexAttribDivisor(3, 1);
	glVertexAttribDivisor(4, 1);

	glGenBuffers(1, &VBO_boxColor);
	glBindBuffer(GL_ARRAY_BUFFER, VBO_boxColor);

	glEnableVertexAttribArray(5);
	glVertexAttribPointer(5, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (GLvoid*)0);

	glVertexAttribDivisor(5, 1);

	glBindVertexArray(0);

	shader = ResourceManager::GetShader("debugRenderer");
}

DebugRenderer::~DebugRenderer()
{
	glDeleteVertexArrays(1, &VAO_box);
	glDeleteBuffers(1, &VBO_box);
	glDeleteBuffers(1, &EBO_box);
	glDeleteBuffers(1, &VBO_boxModel);
	glDeleteBuffers(1, &VBO_boxColor);
}

/*void DebugRenderer::DrawBox(GLfloat* vertices)
{
	
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
*/