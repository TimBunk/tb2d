#include "entity.h"

Entity::Entity()
{
	position = glm::vec2(0.0f, 0.0f);
	angle = 0.0f;
	scale = glm::vec2(1.0f, 1.0f);

	localPosition = glm::vec2(0.0f, 0.0f);
	localAngle = 0.0f;
	localScale = glm::vec2(1.0f, 1.0f);
}

Entity::~Entity()
{

}

void Entity::AddChild(Entity* child)
{
	childeren.push_back(child);
}

void Entity::RemoveChild(Entity* child) {
	std::vector<Entity*>::iterator it = childeren.begin();
	while (it != childeren.end()) {
		if ((*it) == child) {
			it = childeren.erase(it);
			return;
		}
		++it;
	}
	std::cout << "You tried to remove a child, but that child could not be found!" << std::endl;
}

void Entity::UpdateChilderen(Entity * parent, double deltaTime)
{
	if (parent != NULL) {
		model = parent->model;
		model = glm::translate(model, glm::vec3(localPosition.x, localPosition.y, 0.0f));
		model = glm::rotate(model, localAngle, glm::vec3(0.0f, 0.0f, 1.0f));
		this->position = model[3];
		this->angle = glm::atan(model[0][1], model[0][0]);
		this->scale = this->localScale * parent->scale;
	}
	else {
		this->position = this->localPosition;
		this->angle = this->localAngle;
		this->scale = this->localScale;
		model = glm::mat4();
		model = glm::translate(model, glm::vec3(position.x, position.y, 0.0f));
		model = glm::rotate(model, angle, glm::vec3(0.0f, 0.0f, 1.0f));
	}
	for (int i = 0; i < childeren.size(); i++) {
		childeren[i]->Draw();
		childeren[i]->Update(deltaTime);
		childeren[i]->UpdateChilderen(this, deltaTime);
	}
}

void Entity::DrawChilderen(Entity * parent)
{
	if (parent != NULL) {
		model = parent->model;
		model = glm::translate(model, glm::vec3(localPosition.x, localPosition.y, 0.0f));
		model = glm::rotate(model, localAngle, glm::vec3(0.0f, 0.0f, 1.0f));
		this->position = model[3];
		this->angle = glm::atan(model[0][1], model[0][0]);
		this->scale = this->localScale * parent->scale;
	}
	else {
		this->position = this->localPosition;
		this->angle = this->localAngle;
		this->scale = this->localScale;
		model = glm::mat4();
		model = glm::translate(model, glm::vec3(position.x, position.y, 0.0f));
		model = glm::rotate(model, angle, glm::vec3(0.0f, 0.0f, 1.0f));
	}
	for (int i = 0; i < childeren.size(); i++) {
		childeren[i]->Draw();
		childeren[i]->DrawChilderen(this);
	}
}
