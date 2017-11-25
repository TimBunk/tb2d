#ifndef MIRROR_H
#define MIRROR_H

#include "laser.h"

class Mirror : public B2Entity
{
public:
	Mirror(Camera* camera, Shader* shader, b2World* world);
	~Mirror();

	void Update(double deltaTime);

private:
	Laser* laser;
};

#endif // !MIRROR_H