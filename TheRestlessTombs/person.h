#ifndef PERSON_H
#define PERSON_H

#include "b2entity.h"
#include "camera.h"
#include "texture.h"
#include "configure.h"
#include "shader.h"
#include <Box2D/Box2D.h>

class Person : public B2Entity {
public:
    Person(Camera* camera, Shader* shader);
    virtual ~Person();

    virtual void Update(float deltaTime);

protected:

	float health;
	float damage;
	float attackSpeed;
	float speed;

private:

};

#endif // !PERSON_H
