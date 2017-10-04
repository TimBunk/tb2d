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

void Entity::Draw()
{

}

glm::vec3 Entity::GetGlobalPosition() {
	return position;
}

float Entity::GetGlobalAngle() {
	return angle;
}

glm::vec2 Entity::GetGlobalScale() {
	return scale;
}

void Entity::AddChild(Entity* child)
{
	entities.push_back(child);
}

void Entity::RemoveChild(Entity* child) {
	std::vector<Entity*>::iterator it = entities.begin();
	while (it != entities.end()) {
		if ((*it) == child) {
			it = entities.erase(it);
			return;
		}
		++it;
	}
	std::cout << "You tried to remove a child, but that child could not be found!" << std::endl;
}

void Entity::UpdateChilderen(Entity * parent, float deltaTime)
{
	if (parent != NULL) {
		this->position = this->localPosition + parent->position;
		this->angle = this->localAngle + parent->angle;
		this->scale = this->localScale * parent->scale;
		/*model = glm::translate(model, this->position);
		model = glm::rotate(model, glm::radians(this->angle), glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::scale(model, glm::vec3(this->scale, 0.0f));*/
	}
	for (int i = 0; i < entities.size(); i++) {
		entities[i]->Update(deltaTime);
		entities[i]->UpdateChilderen(this, deltaTime);
	}
}
