#ifndef CRATE_H
#define CRATE_H

#include "destructable.h"
#include "weapon.h"
#include "player.h"

class Crate : public Destructable{
public:
	Crate(Camera* camera, Shader* shader);
	~Crate();

	void Update(float deltaTime);

	void Destroy();
	void Reset();

private:

};

#endif // !CRATE_H
