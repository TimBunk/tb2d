#ifndef HAND_H
#define HAND_H

#define _USE_MATH_DEFINES

#include "camera.h"
#include "shader.h"
#include "renderable.h"

#include <math.h>
#include <glm-0.9.8.4/glm/gtx/rotate_vector.hpp>

class Hand : public Renderable {
public:
	Hand(Camera* camera, Shader* shader, float radius);
	~Hand();

	void Update(float deltaTime);
	void Draw();

	void SetAngle(glm::vec2 angle);
	// returns angle in radians!
	float GetAngle();

private:
	float radius;
	glm::vec2 angle;
	float rotation;
};

#endif // !HAND_H
