#ifndef ENTITY_H
#define ENTITY_H

#include <iostream>
#include <string>
#include <math.h>
#include <vector>

#include "shader.h"
#include "texture.h"
#include "box.h"

#include <gl\glew.h>
#include <glfw3.h>
#include <glm-0.9.8.4\glm\glm.hpp>
#include <glm-0.9.8.4\glm\gtc\matrix_transform.hpp>
#include <glm-0.9.8.4\glm\gtc\type_ptr.hpp>
#include <Box2D\Box2D.h>

class Entity {
public:
	Entity();
	virtual ~Entity();

	// global values
	glm::vec3 position;
	float angle;
	glm::vec2 scale;
	// local values
	glm::vec3 localPosition;
	float localAngle;
	glm::vec2 localScale;

	virtual void Update(float deltaTime);
	virtual void Draw(glm::mat4 view, glm::mat4 projection);

	void AddTexture(Texture texture);

protected:
	std::vector<Entity*> entities;
	Shader* shader;
	Texture texture;

	void AddChild(Entity* child);
	void UpdateChilderen(Entity* parent);
private:
	glm::mat4 model;
};

#endif // !ENTITY_H