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

void DebugRenderer::Submit(B2Entity * b2entity)
{
	switch (b2entity->GetShape())
	{
	case Shape::box:
		DebugRenderer::debugRenderer->AddBox(b2entity);
		break;
	case Shape::circle:
		DebugRenderer::debugRenderer->AddCircle(b2entity);
		break;
	}
}

void DebugRenderer::Render(Camera* camera)
{
	DebugRenderer::debugRenderer->shader->Use();
	DebugRenderer::debugRenderer->shader->SetMatrix4("projection", camera->GetProjectionMatrix());
	DebugRenderer::debugRenderer->shader->SetMatrix4("view", camera->GetViewMatrix());
	DebugRenderer::debugRenderer->DrawBoxes();
	DebugRenderer::debugRenderer->DrawCircles();
	DebugRenderer::debugRenderer->DrawLines(camera);
}

void DebugRenderer::Line(glm::vec2 point1, glm::vec2 point2, glm::vec3 color)
{
	DebugRenderer::debugRenderer->linesPosition.push_back(point1);
	DebugRenderer::debugRenderer->linesPosition.push_back(point2);
	DebugRenderer::debugRenderer->linesColor.push_back(color);
	DebugRenderer::debugRenderer->linesColor.push_back(color);
	DebugRenderer::debugRenderer->linesCount++;
}

DebugRenderer::DebugRenderer()
{
	shader = ResourceManager::GetShader("debugRenderer");
	shaderLine = ResourceManager::GetShader("debugLineRenderer");
	boxesCount = 0;
	circlesCount = 0;
	linesCount = 0;

	// VAO for the box and the line
	glGenVertexArrays(1, &VAO_box);
	glBindVertexArray(VAO_box);

	glGenBuffers(1, &VBO_position);
	glBindBuffer(GL_ARRAY_BUFFER, VBO_position);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(glm::vec2), (GLvoid*)0);

	// Generate the color buffer
	glGenBuffers(1, &VBO_color);
	glBindBuffer(GL_ARRAY_BUFFER, VBO_color);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (GLvoid*)0);

	// Gererate the model buffer
	glGenBuffers(1, &VBO_boxModel);
	glBindBuffer(GL_ARRAY_BUFFER, VBO_boxModel);
	// set attribute pointers for matrix (4 times vec4)
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (GLvoid*)0);
	glEnableVertexAttribArray(3);
	glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (GLvoid*)(sizeof(glm::vec4)));
	glEnableVertexAttribArray(4);
	glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (GLvoid*)(2 * sizeof(glm::vec4)));
	glEnableVertexAttribArray(5);
	glVertexAttribPointer(5, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (GLvoid*)(3 * sizeof(glm::vec4)));

	glBindVertexArray(0);

	// VAO for the the circle
	glGenVertexArrays(1, &VAO_circle);
	glBindVertexArray(VAO_circle);

	glGenBuffers(1, &VBO_circlePosition);
	glGenBuffers(1, &EBO_circlePosition);
	glBindBuffer(GL_ARRAY_BUFFER, VBO_circlePosition);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(glm::vec2), (GLvoid*)0);
	std::vector<glm::vec2> vertices;
	std::vector<GLuint> indices;
	for (int i = 0; i < 180; i++) {
		float angle = ((float(i)) / 180.0f) * M_PI * 2.0f;
		glm::vec2 vertex;
		vertex.x = cos(angle);
		vertex.y = sin(angle);
		vertices.push_back(vertex);
		indices.push_back(i);
		indices.push_back(i + 1);
	}
	// Set the last indice back to 0 otherwise you will have a ugly line in the middle of the circle
	indices.pop_back();
	indices.push_back(0);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec2), &vertices[0], GL_STREAM_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO_circlePosition);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * 360, &indices[0], GL_STREAM_DRAW);

	glGenBuffers(1, &VBO_circleColor);
	glBindBuffer(GL_ARRAY_BUFFER, VBO_circleColor);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (GLvoid*)0);
	glVertexAttribDivisor(1, 1);

	// Gererate the model buffer
	glGenBuffers(1, &VBO_circleModel);
	glBindBuffer(GL_ARRAY_BUFFER, VBO_circleModel);
	// set attribute pointers for matrix (4 times vec4)
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (GLvoid*)0);
	glEnableVertexAttribArray(3);
	glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (GLvoid*)(sizeof(glm::vec4)));
	glEnableVertexAttribArray(4);
	glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (GLvoid*)(2 * sizeof(glm::vec4)));
	glEnableVertexAttribArray(5);
	glVertexAttribPointer(5, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (GLvoid*)(3 * sizeof(glm::vec4)));
	glVertexAttribDivisor(2, 1);
	glVertexAttribDivisor(3, 1);
	glVertexAttribDivisor(4, 1);
	glVertexAttribDivisor(5, 1);

	glBindVertexArray(0);

	// VAO for the line
	glGenVertexArrays(1, &VAO_line);
	glBindVertexArray(VAO_line);

	glBindBuffer(GL_ARRAY_BUFFER, VBO_position);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(glm::vec2), (GLvoid*)0);

	glBindBuffer(GL_ARRAY_BUFFER, VBO_color);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (GLvoid*)0);

	glBindVertexArray(0);
}

DebugRenderer::~DebugRenderer()
{
	glDeleteBuffers(1, &VBO_position);
	glDeleteBuffers(1, &VBO_color);

	glDeleteVertexArrays(1, &VAO_box);
	glDeleteBuffers(1, &VBO_boxModel);

	glDeleteVertexArrays(1, &VAO_circle);
	glDeleteBuffers(1, &VBO_circlePosition);
	glDeleteBuffers(1, &EBO_circlePosition);
	glDeleteBuffers(1, &VBO_circleColor);
	glDeleteBuffers(1, &VBO_circleModel);

	glDeleteVertexArrays(1, &VAO_line);
}

void DebugRenderer::AddBox(B2Entity* b2entity)
{
	glm::vec2 pivot = b2entity->GetColliderPivot();
	boxesPosition.push_back(glm::vec2(-0.5f + pivot.x, -0.5f + pivot.y));	//	lower left	1
	boxesPosition.push_back(glm::vec2(0.5f + pivot.x, -0.5f + pivot.y));	//	lower right	1
	boxesPosition.push_back(glm::vec2(0.5f + pivot.x, -0.5f + pivot.y));	//	lower right	2
	boxesPosition.push_back(glm::vec2(0.5f + pivot.x, 0.5f + pivot.y));		//	upper right	2
	boxesPosition.push_back(glm::vec2(0.5f + pivot.x, 0.5f + pivot.y));		//	upper right	3
	boxesPosition.push_back(glm::vec2(-0.5f + pivot.x, 0.5f + pivot.y));	//	upper left	3
	boxesPosition.push_back(glm::vec2(-0.5f + pivot.x, 0.5f + pivot.y));	//	upper left	4
	boxesPosition.push_back(glm::vec2(-0.5f + pivot.x, -0.5f + pivot.y));	//	lower left	4

	glm::mat4 model = b2entity->GetModelMatrix();
	model = glm::scale(model, glm::vec3(b2entity->GetColliderWidth(), b2entity->GetColliderHeight(), 0.0f));
	for (int i = 0; i < 8; i++) {
		boxesModel.push_back(model);
		boxesColor.push_back(b2entity->GetDebugColor());
	}
	boxesCount++;
}

void DebugRenderer::AddCircle(B2Entity* b2entity)
{
	glm::mat4 model = b2entity->GetModelMatrix();
	model = glm::scale(model, glm::vec3(b2entity->GetColliderWidth(), b2entity->GetColliderHeight(), 0.0f));
	circlesModel.push_back(model);
	circlesColor.push_back(b2entity->GetDebugColor());
	circlesCount++;
}

void DebugRenderer::DrawBoxes()
{
	if (boxesCount == 0) { return; }

	// Bind the VAO
	glBindVertexArray(VAO_box);

	// Fill all of the buffers with their data
	glBindBuffer(GL_ARRAY_BUFFER, VBO_position);
	glBufferData(GL_ARRAY_BUFFER, boxesPosition.size() * sizeof(glm::vec2), &boxesPosition[0], GL_STREAM_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, VBO_color);
	glBufferData(GL_ARRAY_BUFFER, boxesColor.size() * sizeof(glm::vec3), &boxesColor[0], GL_STREAM_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, VBO_boxModel);
	glBufferData(GL_ARRAY_BUFFER, boxesModel.size() * sizeof(glm::mat4), &boxesModel[0], GL_STREAM_DRAW);

	// Unbind the buffer
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glDrawArrays(GL_LINES, 0, 8 * boxesCount);
	//glDrawElementsInstanced(GL_LINES, 8, GL_UNSIGNED_INT, 0, DebugRenderer::debugRenderer->boxesCount);

	// Unbind the VAO
	glBindVertexArray(0);

	// Clear all the data that was passed in
	boxesPosition.clear();
	boxesColor.clear();
	boxesModel.clear();
	boxesCount = 0;
}

void DebugRenderer::DrawCircles()
{
	if (circlesCount == 0) { return; }
	
	// Bind the VAO
	glBindVertexArray(VAO_circle);

	// Fill all of the buffers with their data
	glBindBuffer(GL_ARRAY_BUFFER, VBO_circleColor);
	glBufferData(GL_ARRAY_BUFFER, circlesColor.size() * sizeof(glm::vec3), &circlesColor[0], GL_STREAM_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, VBO_circleModel);
	glBufferData(GL_ARRAY_BUFFER, circlesModel.size() * sizeof(glm::mat4), &circlesModel[0], GL_STREAM_DRAW);

	// Unbind the buffer
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	//glDrawArrays(GL_LINES, 0, 8 * boxesCount);
	glDrawElementsInstanced(GL_LINES, 360, GL_UNSIGNED_INT, 0, circlesCount);

	// Unbind the VAO
	glBindVertexArray(0);

	// Clear all the data that was passed in
	circlesColor.clear();
	circlesModel.clear();
	circlesCount = 0;
}

void DebugRenderer::DrawLines(Camera* camera)
{
	if (linesCount == 0) { return; }
	shaderLine->Use();
	shaderLine->SetMatrix4("projection", camera->GetProjectionMatrix());
	shaderLine->SetMatrix4("view", camera->GetViewMatrix());
	// Bind the VAO
	glBindVertexArray(VAO_line);

	// Fill all of the buffers with their data
	glBindBuffer(GL_ARRAY_BUFFER, VBO_position);
	glBufferData(GL_ARRAY_BUFFER, linesPosition.size() * sizeof(glm::vec2), &linesPosition[0], GL_STREAM_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, VBO_color);
	glBufferData(GL_ARRAY_BUFFER, linesColor.size() * sizeof(glm::vec3), &linesColor[0], GL_STREAM_DRAW);

	// Unbind the buffer
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glDrawArrays(GL_LINES, 0, 2 * linesCount);

	// Unbind the VAO
	glBindVertexArray(0);

	// Clear all the data that was passed in
	linesPosition.clear();
	linesColor.clear();
	linesCount = 0;
}
