#ifndef CRYSTAL_H
#define CRYSTAL_H

#include "linkable.h"

class Crystal : public Linkable
{
public:
	Crystal(int uniqueID, int width, int height, unsigned int textureID, b2World* world);
	~Crystal();

	void Update(double deltaTime);
	int GetUniqueID() { return uniqueID; }

private:
	int uniqueID;
};

#endif // !CRYSTAL_H
