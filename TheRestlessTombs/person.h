#ifndef PERSON_H
#define PERSON_H

#include "destructable.h"
#include "camera.h"
#include "texture.h"
#include "shader.h"
#include <Box2D/Box2D.h>

class Person : public Destructable {
public:
    Person(Camera* camera, Shader* shader);
    virtual ~Person();

    virtual void Update(float deltaTime);
    virtual void Draw();

    bool IsAlive();

    virtual void TakeDamage(int damage);
    void ApplyHealing(int healing);

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
