#ifndef PERSON_H
#define PERSON_H

#include "b2entity.h"
#include "camera.h"
#include "texture.h"
#include "shader.h"
#include <Box2D/Box2D.h>

class Person : public B2Entity {
public:
    Person(Camera* camera, Shader* shader);
    virtual ~Person();

    virtual void Update(float deltaTime);

    void TakeDamage(int damage);
    void ApplyHealing(int healing);

    virtual void FlipTextureAutomatic();
    // if it is already flipped set to true
    void FlipTexture();
    bool IsTextureFlipped();

protected:

	int health;
	int currentHealth;
	int damage;
	float attackSpeed;
	float speed;

	bool flippedTexture;
	float currentX;

private:

};

#endif // !PERSON_H
