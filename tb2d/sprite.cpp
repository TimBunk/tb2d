#include "sprite.h"

Sprite::Sprite(int width, int height, unsigned int textureID) : Entity::Entity()
{
	this->width = width;
	this->height = height;
	this->textureID = textureID;
	renderer = RenderManager::GetRenderer("default");
	color = glm::vec4(0, 0, 0, 0);
	repeatUV = glm::vec2(1, 1);
}

Sprite::~Sprite() {
	
}

void Sprite::Draw()
{
	if (renderer != nullptr) {
		renderer->Submit(this);
	}
}