#include "sprite.h"

Sprite::Sprite(int width, int height, glm::vec2 pivot, Texture* texture, Camera* camera, bool HUD) : Entity::Entity()
{
	this->width = width;
	this->height = height;
	this->quadData = ResourceManager::GetQuad(pivot);
	this->texture = texture;
	this->shader = ResourceManager::GetShader("defaultShader");
	this->camera = camera;
	this->HUD = HUD;
}

Sprite::~Sprite() {
	
}

void Sprite::Draw()
{
	shader->Use();
	shader->SetMatrix4("projection", camera->GetProjectionMatrix());
	if (!HUD) {
		shader->SetMatrix4("view", camera->GetViewMatrix());
	}
	// Create a local model for the scaling otherwise all of the childeren will get the wrong scaling
	glm::mat4 _model = glm::scale(model, glm::vec3(width * GetGlobalScale().x, height * GetGlobalScale().y, 0.0f));
	shader->SetMatrix4("model", _model);

	glActiveTexture(GL_TEXTURE0);
	glBindVertexArray(quadData.VAO);
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