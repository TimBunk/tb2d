#ifndef ENTITY_H
#define ENTITY_H

#include <iostream>
#include <string>
#include <math.h>
#include <vector>

#include "shader.h"
#include "texture.h"
#include "box.h"
#include "camera.h"

#include <GL/glew.h>
#include <glm-0.9.8.4/glm/glm.hpp>
#include <glm-0.9.8.4/glm/gtc/matrix_transform.hpp>
#include <glm-0.9.8.4/glm/gtc/type_ptr.hpp>
#include <Box2D/Box2D.h>

class Entity {
public:
	Entity(Camera* camera);
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
	virtual void Draw();

protected:
	std::vector<Entity*> entities;
	Shader* shader;
	Texture texture;

	// You only have to add a child one, otherwise it might cause unexpected behaviour
	void AddChild(Entity* child);
	void RemoveChild(Entity* child);
	void UpdateChilderen(Entity* parent, float deltaTime);
private:
	glm::mat4 model;
	Camera* camera;
};

#endif // !ENTITY_H
