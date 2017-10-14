#ifndef DESTRUCTABLE_H
#define DESTRUCTABLE_H

#include "b2entity.h"

class Destructable : public B2Entity {
public:
	Destructable(Camera* camera, Shader* shader);
	~Destructable();

	virtual void Update(float deltaTime);
	void Draw();

	virtual void Destroy();
	virtual void Reset();
	bool IsAlive();

	void SetActive(bool active);
protected:
	bool alive;
private:

};

#endif // !DESTRUCTABLE_H
