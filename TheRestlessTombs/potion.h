#ifndef POTION_H
#define POTION_H

#include "item.h"

class Potion : public Item {
public:
	Potion(Camera* camera, Shader* shader, b2World* world);
	~Potion();

protected:
	bool alive;
private:

};

#endif // !POTION_H
