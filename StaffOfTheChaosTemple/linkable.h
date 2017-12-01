#ifndef LINKABLE_H
#define LINKABLE_H

#include "b2entity.h"

class Linkable : public B2Entity
{
public:
	Linkable(Camera* camera, Shader* shader, b2World* world);
	~Linkable();

	virtual void Enable(bool state);
	virtual bool IsEnabled();

protected:
	bool enabled;

private:
	
};

#endif // !LINKABLE_H
