#ifndef ENTITY_H
#define ENTITY_H

#include <iostream>
#include <vector>

#include <glm-0.9.8.4/glm/glm.hpp>
#include <glm-0.9.8.4/glm/gtc/matrix_transform.hpp>
#include <glm-0.9.8.4/glm/gtc/type_ptr.hpp>

class Entity {
public:
	Entity();
	virtual ~Entity();

	// local values
	glm::vec2 localPosition;
	float localAngle;
	glm::vec2 localScale;

	virtual void Update(double deltaTime);
	virtual void UpdateChilderen(Entity* parent, double deltaTime);
	virtual void Draw();

	// You only have to add a child one, otherwise it might cause unexpected behaviour
	void AddChild(Entity* child);
	void RemoveChild(Entity* child);

	glm::vec2 GetGlobalPosition();
	float GetGlobalAngle();
	glm::vec2 GetGlobalScale();

protected:
	std::vector<Entity*> entities;
	// global values
	glm::vec2 position;
	float angle;
	glm::vec2 scale;
private:

};

#endif // !ENTITY_H
