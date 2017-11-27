#ifndef ROTATOR_H
#define ROTATOR_H

#include "b2entity.h"
class Rotator : public B2Entity
{
public:
	Rotator(Camera* camera, Shader* shader, b2World* world);
	~Rotator();

	void Update(double deltaTime);

private:

};

#endif // !ROTATOR_H
