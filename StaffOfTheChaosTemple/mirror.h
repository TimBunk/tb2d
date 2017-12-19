#ifndef MIRROR_H
#define MIRROR_H

#include "laser.h"
#include "rotator.h"

class Mirror : public B2Entity
{
public:
	Mirror(bool rotatable, int width, int height, Texture* texture, Camera* camera, b2World* world);
	~Mirror();

	void Update(double deltaTime);
	void SetRotation(float degrees);

private:
	Rotator* rotator;
	B2Entity* notHitableArea;
};

#endif // !MIRROR_H