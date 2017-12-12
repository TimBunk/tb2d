#ifndef ROTATOR_H
#define ROTATOR_H

#include "b2entity.h"
class Rotator : public B2Entity
{
public:
	Rotator(int width, int height, glm::vec2 pivot, Texture* texture, Camera* camera, b2World* world);
	~Rotator();

	void Update(double deltaTime);
	
	void Rotate(bool clockWise, float degrees);
	float GetRotation();
	void SetRotation(float degrees);

private:
	float rotation;
};

#endif // !ROTATOR_H
