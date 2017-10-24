#ifndef CRATE_H
#define CRATE_H

#include "destructable.h"
#include "healthPotion.h"

class Crate : public Destructable{
public:
	Crate(Camera* camera, Shader* shader);
	~Crate();

	void Update(float deltaTime);

	void Store(Potion* potion);
	void Destroy();
	void Reset();

private:
	Potion* potion;
};

#endif // !CRATE_H
