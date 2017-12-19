#include "sprite.h"

Sprite::Sprite(int width, int height, glm::vec2 pivot, Texture* texture, Camera* camera, bool HUD) : Entity::Entity()
{
	this->width = width;
	this->height = height;
	this->pivot = pivot;
	this->quadData = ResourceManager::GetQuad(pivot);
	this->texture = texture;
	this->shader = ResourceManager::GetShader("defaultShader");
	this->camera = camera;
	this->HUD = HUD;

	renderer = nullptr;
}

Sprite::~Sprite() {
	
}

void Sprite::Draw()
{
	if (renderer != nullptr) {
		// If a renderer was found just update VBO of the renderer by the data of this sprite
		renderer->UpdateVBO(this);
		//std::cout << "instanced drawing" << std::endl;
		return;
	}
	// Manually draw the sprite
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

void Sprite::SetInstancedRenderer(std::string name)
{
	renderer = RenderManager::GetRenderer(name);
	if (renderer == nullptr) {
		RenderManager::CreateRenderer(name, shader, HUD);
		renderer = RenderManager::GetRenderer(name);
		// If the sprite contains a texture pass that texture to the renderer
		if (texture != nullptr) {
			renderer->AddAttributeUV(texture);
		}
	}
	vertexPositions.push_back(glm::vec2(-0.5f, -0.5f)); // lower left
	vertexPositions.push_back(glm::vec2(0.5f, -0.5f)); // lower right
	vertexPositions.push_back(glm::vec2(0.5f, 0.5f)); // upper right
	vertexPositions.push_back(glm::vec2(-0.5f, 0.5f)); // upper left

	uvPositions.push_back(glm::vec2(0.0f, 0.0f)); // lower left
	uvPositions.push_back(glm::vec2(1.0f, 0.0f)); // lower right
	uvPositions.push_back(glm::vec2(1.0f, 1.0f)); // upper right
	uvPositions.push_back(glm::vec2(0.0f, 1.0f)); // upper left
}

int Sprite::GetWidth()
{
	return width;
}

int Sprite::GetHeight()
{
	return height;
}