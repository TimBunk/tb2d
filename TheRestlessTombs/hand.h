#ifndef HAND_H
#define HAND_H

#include "b2entity.h"

class Hand : public B2Entity {
public:
	Hand(Camera* camera, Shader* shader);
	~Hand();

	void Update(float deltaTime);
private:

};

#endif // !HAND_H
