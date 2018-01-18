#include "sprite.h"

Sprite::Sprite(int width, int height, unsigned int textureID) : Entity::Entity()
{
	// Initialize the variables
	this->width = width;
	this->height = height;
	this->textureID = textureID;
	renderer = RenderManager::GetSimpleRenderer("default");
	color = glm::vec4(0, 0, 0, 0);
	repeatUV = glm::vec2(1, 1);
}

Sprite::Sprite(int width, int height, glm::vec4 color)
{
	// Initialize the variables
	this->width = width;
	this->height = height;
	this->color = color;
	textureID = 0;
	renderer = RenderManager::GetSimpleRenderer("default");
	repeatUV = glm::vec2(1, 1);
}

Sprite::~Sprite() {
	
}

void Sprite::Draw()
{
	// Submit this to the renderer
	if (renderer != nullptr) {
		renderer->Submit(this);
	}
}