#ifndef LINKABLE_H
#define LINKABLE_H

#include "box2Dclasses/b2entity.h"

class Linkable : public B2Entity
{
public:
	Linkable(int width, int height, unsigned int textureID, b2World* world);
	~Linkable();

	void Hit();
	virtual bool IsEnabled();

protected:
	bool hit;
	bool enabled;

private:
	
};

#endif // !LINKABLE_H
