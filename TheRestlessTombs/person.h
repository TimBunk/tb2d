#ifndef PERSON_H
#define PERSON_H

#include "destructable.h"
#include "camera.h"
#include "texture.h"
#include "shader.h"
#include <Box2D/Box2D.h>

class Person : public Destructable {
public:
    Person(ResourceManager* rm, Camera* camera, Shader* shader, b2World* world);
    virtual ~Person();

    virtual void Draw();

    bool IsAlive();

    virtual void TakeDamage(int damage);
    void ApplyHealing(int healing);

    // if it is already flipped set to true
    void FlipTexture();
    bool IsTextureFlipped();

protected:
    ResourceManager* rm;

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
