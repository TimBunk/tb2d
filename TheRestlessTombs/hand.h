#ifndef HAND_H
#define HAND_H

#include "entity.h"
#include "camera.h"
#include "shader.h"

class Hand : public Entity {
public:
	Hand(Camera* camera, Shader* shader);
	~Hand();

	void Update(float deltaTime);

private:

};

#endif // !HAND_H
