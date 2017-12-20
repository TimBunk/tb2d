#include "renderer.h"
#include "sprite.h"

Renderer::Renderer(Shader* shader, bool hud)
{
	this->shader = shader;
	this->hud = hud;
	drawCount = 0;
	texture = nullptr;
	VBO_uv = 0;
	EBO_uv = 0;
	VBO_color = 0;

	GLuint indices[] = {
		0, 1, 3,
		1, 2, 3,
	};
	
	// Generate and bind the VAO
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	
	// Generate and bind the positions
	glGenBuffers(1, &VBO_position);
	glBindBuffer(GL_ARRAY_BUFFER, VBO_position);
	// Generate the indices for the positions
	glGenBuffers(1, &EBO_position);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO_position);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STREAM_DRAW);
	// Set attribute pointer for the position
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), (GLvoid*)0);

	// Gererate the model buffer
	glGenBuffers(1, &VBO_model);
	glBindBuffer(GL_ARRAY_BUFFER, VBO_model);
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

	// Unbind the VAO and VBO
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

Renderer::~Renderer()
{
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO_position);
	glDeleteBuffers(1, &EBO_position);
	glDeleteBuffers(1, &VBO_model);
	if (VBO_uv != 0) {
		glDeleteBuffers(1, &VBO_uv);
		glDeleteBuffers(1, &EBO_uv);
	}
	if (VBO_color != 0) {
		glDeleteBuffers(1, &VBO_color);
	}
}

void Renderer::Clear()
{
	positions.clear();
	matrices.clear();
	if (VBO_uv != 0) {
		uvs.clear();
	}
	if (VBO_color != 0) {
		colors.clear();
	}
	drawCount = 0;
}

void Renderer::UpdateVBO(Entity * entity)
{
	if (dynamic_cast<Sprite*>(entity) != NULL) {
		Sprite* sprite = dynamic_cast<Sprite*>(entity);
		// Get the vertex positions from the sprite
		positions.insert(positions.end(), sprite->vertexPositions.begin(), sprite->vertexPositions.end());
		// Get the model matrix from the sprite
		sprite->model = glm::scale(sprite->model, glm::vec3(sprite->width * sprite->scale.x, sprite->height * sprite->scale.y, 0.0f));
		matrices.push_back(sprite->model);
		// Get the uv positions from the sprite
		if (VBO_uv != 0) {
			uvs.insert(uvs.end(), sprite->uvPositions.begin(), sprite->uvPositions.end());
		}
		if (VBO_color != 0) {
			colors.push_back(sprite->color);
		}
		// Increate the counter
		drawCount++;
	}
}

void Renderer::Render(Camera* camera)
{
	if (drawCount == 0) { return; };
	shader->Use();
	shader->SetMatrix4("projection", camera->GetProjectionMatrix());
	if (!hud) {
		shader->SetMatrix4("view", camera->GetViewMatrix());
	}

	// Bind the VAO
	//glActiveTexture(GL_TEXTURE0);
	glBindVertexArray(VAO);
	//glBindTexture(GL_TEXTURE_2D, texture->GetId());

	// Fill all of the buffers with their data
	glBindBuffer(GL_ARRAY_BUFFER, VBO_position);
	glBufferData(GL_ARRAY_BUFFER, positions.size() * sizeof(glm::vec2), &positions[0], GL_STREAM_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, VBO_model);
	glBufferData(GL_ARRAY_BUFFER, matrices.size() * sizeof(glm::mat4), &matrices[0], GL_STREAM_DRAW);
	if (VBO_uv != 0) {
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture->GetId());
		glBindBuffer(GL_ARRAY_BUFFER, VBO_uv);
		glBufferData(GL_ARRAY_BUFFER, uvs.size() * sizeof(glm::vec2), &uvs[0], GL_STREAM_DRAW);
	}
	if (VBO_color != 0) {
		glBindBuffer(GL_ARRAY_BUFFER, VBO_color);
		glBufferData(GL_ARRAY_BUFFER, colors.size() * sizeof(glm::vec4), &colors[0], GL_STREAM_DRAW);
	}
	// Unbind the buffer
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	//glDrawArraysInstanced(GL_TRIANGLES, 0, 6, count);
	glDrawElementsInstanced(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0, drawCount);

	// Unbind the VAO
	glBindVertexArray(0);
	if (VBO_uv != 0) {
		glBindTexture(GL_TEXTURE_2D, 0);
	}
}

void Renderer::AddAttributeUV(Texture* texture)
{
	this->texture = texture;
	GLuint indices[] = {
		0, 1, 3,
		1, 2, 3,
	};
	// Bind the VAO
	glBindVertexArray(VAO);

	// Generate and bind the uv
	glGenBuffers(1, &VBO_uv);
	glBindBuffer(GL_ARRAY_BUFFER, VBO_uv);
	// Generate the indices for the uv
	glGenBuffers(1, &EBO_uv);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO_uv);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STREAM_DRAW);
	// Set attribute pointer for the position
	glEnableVertexAttribArray(5);
	glVertexAttribPointer(5, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), (GLvoid*)0);

	// Unbind the VAO and VBO
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void Renderer::AddInstanceAttributeColor()
{
	// Bind the VAO
	glBindVertexArray(VAO);

	// Generate and bind the uv
	glGenBuffers(1, &VBO_color);
	glBindBuffer(GL_ARRAY_BUFFER, VBO_color);
	// Set attribute pointer for the position
	glEnableVertexAttribArray(6);
	glVertexAttribPointer(6, 4, GL_FLOAT, GL_FALSE, sizeof(glm::vec4), (GLvoid*)0);
	// Enable instancing for this vertextAttribPoitner
	glVertexAttribDivisor(6, 1);

	// Unbind the VAO and VBO
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}
