#ifndef CRYSTAL_H
#define CRYSTAL_H

#include "linkable.h"

class Crystal : public Linkable
{
public:
	Crystal(Camera* camera, Shader* shader, b2World* world);
	~Crystal();

	void Update(double deltaTime);
	void Draw();

private:
	
};

#endif // !CRYSTAL_H
