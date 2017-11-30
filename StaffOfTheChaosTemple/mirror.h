#ifndef MIRROR_H
#define MIRROR_H

#include "laser.h"
#include "rotator.h"

class Mirror : public B2Entity
{
public:
	Mirror(bool rotatable, ResourceManager* rm, Camera* camera, Shader* shader, b2World* world);
	~Mirror();

	void Update(double deltaTime);
	void SetRotation(float degrees);

private:
	Rotator* rotator;
};

#endif // !MIRROR_H