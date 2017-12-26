#ifndef CRYSTAL_H
#define CRYSTAL_H

#include "linkable.h"

class Crystal : public Linkable
{
public:
	Crystal(int width, int height, unsigned int textureID, b2World* world);
	~Crystal();

	void Update(double deltaTime);

private:
	
};

#endif // !CRYSTAL_H
