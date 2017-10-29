#ifndef CRATE_H
#define CRATE_H

#include "item.h"

class Crate : public Destructable {
public:
	Crate(Camera* camera, Shader* shader, b2World* world);
	~Crate();

	void Store(Item* item);
	void Destroy();
	void Reset();

private:
	Item* item;
};

#endif // !CRATE_H
