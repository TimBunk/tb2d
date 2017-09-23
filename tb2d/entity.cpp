#include "entity.h"

Entity::Entity()
{
	position = glm::vec3(0.0f);
	angle = 0.0f;
	scale = glm::vec2(1.0f);

	localPosition = glm::vec3(0.0f);
	localAngle = 0.0f;
	localScale = glm::vec2(1.0f);
}

Entity::~Entity()
{

}

void Entity::Update(float deltaTime)
{

}

void Entity::Draw(glm::mat4 view, glm::mat4 projection)
{
	shader->SetMatrix4("model", model);
	shader->SetMatrix4("view", view);
	shader->SetMatrix4("projection", projection);
	shader->Use();
}

void Entity::AddTexture(Texture texture)
{
	this->texture = texture;
}

void Entity::AddChild(Entity* child)
{
	entities.push_back(child);
}

void Entity::UpdateChilderen(Entity * parent)
{
	for (int i = 0; i < entities.size(); i++) {
		entities[i]->UpdateChilderen(this);
	}
}
