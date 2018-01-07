#ifndef MIRROR_H
#define MIRROR_H

#include "laser.h"
#include "rotator.h"

class Mirror : public B2Entity
{
public:
	Mirror(bool rotatable, int width, int height, unsigned int textureID, b2World* world);
	~Mirror();

	void Update(double deltaTime);
	void SetRotation(float degrees);

	void Rotatable(bool boolean);
	bool IsRotatable();
	virtual void SetFilter(unsigned int filter);

private:
	Rotator* rotator;
	B2Entity* notHitableArea;
};

#endif // !MIRROR_H