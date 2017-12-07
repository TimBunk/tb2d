#include "sprite.h"

Sprite::Sprite(Texture* texture, Shader* shader, Camera* camera, bool HUD) : Entity::Entity() {
	this->texture = texture;
	this->shader = shader;
	this->camera = camera;
	this->HUD = HUD;
	VAO = 0;
	VBO = 0;
	width = 0;
	height = 0;
}

Sprite::~Sprite() {
	if (VAO != 0) {
		glDeleteVertexArrays(1, &VAO);
		glDeleteBuffers(1, &VBO);
	}
}

void Sprite::Draw()
{
	shader->Use();
	shader->SetMatrix4("projection", camera->GetProjectionMatrix());
	if (!HUD) {
		shader->SetMatrix4("view", camera->GetViewMatrix());
	}
	shader->SetMatrix4("model", model);

	glActiveTexture(GL_TEXTURE0);
	glBindVertexArray(VAO);
	glBindTexture(GL_TEXTURE_2D, texture->GetId());

	glDrawArrays(GL_TRIANGLES, 0, 6);
	// Set the currently binded VAO and texture to 0
	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Sprite::SetTexture(Texture * texture)
{
	this->texture = texture;
}

void Sprite::SetShader(Shader * shader)
{
	this->shader = shader;
}

void Sprite::SetCamera(Camera * camera)
{
	this->camera = camera;
}

int Sprite::GetWidth()
{
	int w = width * this->GetGlobalScale().x;
	return w;
}

int Sprite::GetHeight()
{
	int h = height * this->GetGlobalScale().y;
	return h;
}

void Sprite::CreateBody(int height, int width, glm::vec2 pivot)
{
	float vertices[] = {
		// position										// uv's
		-width / 2 + pivot.x, height / 2 + pivot.y,		0.0f, 1.0f,  // uper left corner
		-width / 2 + pivot.x, -height / 2 + pivot.y,	0.0f, 0.0f,  // lower-left corner
		width / 2 + pivot.x, -height / 2 + pivot.y,		1.0f, 0.0f,  // lower-right corner

		width / 2 + pivot.x, -height / 2 + pivot.y,		1.0f, 0.0f,  // lower-right corner
		width / 2 + pivot.x, height / 2 + pivot.y,		1.0f, 1.0f,  // upper-right corner
		-width / 2 + pivot.x, height / 2 + pivot.y,		0.0f, 1.0f,  // uper left corner
	};

	if (VAO != 0) {
		glDeleteVertexArrays(1, &VAO);
		glDeleteBuffers(1, &VBO);
	}

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// set the vertices
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	glBindVertexArray(0);
}
