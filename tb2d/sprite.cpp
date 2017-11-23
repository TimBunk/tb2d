#include "sprite.h"

Sprite::Sprite(int width, int height, Texture* texture, Shader* shader, Camera* camera, bool HUD) : Entity::Entity() {
	this->width = width;
	this->height = height;
	this->texture = texture;
	this->shader = shader;
	this->camera = camera;
	this->HUD = HUD;

	float vertices[] = {
		// position				// uv's
		-width / 2, height / 2, 0.0f, 0.0f,  // uper left corner
		-width / 2, -height / 2, 0.0f, 1.0f,  // lower-left corner
		width / 2, -height / 2, 1.0f, 1.0f,  // lower-right corner
		
		width / 2, -height / 2, 1.0f, 1.0f,  // lower-right corner
		width / 2, height / 2, 1.0f, 0.0f,  // upper-right corner
		-width / 2, height / 2, 0.0f, 0.0f,  // uper left corner
	};

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// set the vertices
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid*)(2 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	glBindVertexArray(0);
}

Sprite::~Sprite() {
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
}

void Sprite::Draw()
{
	shader->Use();
	shader->SetMatrix4("projection", camera->GetProjectionMatrix());
	if (!HUD) {
		shader->SetMatrix4("view", camera->GetViewMatrix());
	}
	glm::mat4 model;
	model = glm::translate(model, glm::vec3(this->GetGlobalPosition().x, this->GetGlobalPosition().y, 0.0f));
	model = glm::rotate(model, this->GetGlobalAngle(), glm::vec3(0.0f, 0.0f, 1.0f));
	model = glm::scale(model, glm::vec3(this->GetGlobalScale().x, this->GetGlobalScale().y, 1.0f));
	shader->SetMatrix4("model", model);
	glActiveTexture(GL_TEXTURE0 + texture->GetId());
	shader->SetInt("ourTexture", texture->GetId());
	glBindTexture(GL_TEXTURE_2D, texture->GetId());
	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glActiveTexture(GL_TEXTURE0);
	glBindVertexArray(0);
}

void Sprite::SetTexture(Texture * texture)
{
	this->texture = texture;
}

void Sprite::SetShader(Shader * shader)
{
	this->shader = shader;
}

int Sprite::GetWidth()
{
	return width;
}

int Sprite::GetHeight()
{
	return height;
}
