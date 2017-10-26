#ifndef DESTRUCTABLE_H
#define DESTRUCTABLE_H

#include "b2entity.h"

class Destructable : public B2Entity {
public:
	Destructable(Camera* camera, Shader* shader, b2World* world);
	~Destructable();

	virtual void Update(float deltaTime);
	virtual void Draw();

	virtual void Destroy();
	virtual void Reset();
	virtual bool IsAlive();

	virtual void SetActive(bool active);
protected:
	bool alive;
private:

};

#endif // !DESTRUCTABLE_H
