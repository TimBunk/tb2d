#ifndef PERSON_H
#define PERSON_H

#include "entity.h"
#include "camera.h"
#include "texture.h"
#include "configure.h"
#include "shader.h"
#include <Box2D/Box2D.h>

class Person : public Entity {
public:
    Person(Camera* camera, Shader* shader);
    virtual ~Person();

    virtual void Update(float deltaTime);
    virtual void Draw();

    void CreateBody(int x, int y, int w, int h, b2World* world);
    void GiveTexture(Texture texture);
protected:

    glm::vec3 GetPositionInPixels();
	// Note that the angle is in radians
	float GetAngle();

	Camera* camera;
	Shader* shader;
	Texture texture;

	float health;
	float damage;
	float attackSpeed;
	float speed;

	GLuint VBO, VAO, EBO;
    b2World* world;
	b2Body* body;
	b2Fixture* fixture;
	b2Vec2 point[4];
private:

};

#endif // !PERSON_H
