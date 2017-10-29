#ifndef B2ENTITY_H
#define B2ENTITY_H

#include "entity.h"
#include "texture.h"
#include "camera.h"
#include "shader.h"
#include "window.h"

#include <Box2D/Box2D.h>

class B2Entity : public Entity {
public:
	B2Entity(Camera* camera, Shader* shader, b2World* world);
	virtual ~B2Entity();

	virtual void Update(float deltaTime);
	virtual void UpdateChilderen(Entity* parent, float deltaTime);
	virtual void Draw();

	virtual void CreateBody(int x, int y, int w, int h, bool dynamic, bool sensor);
	virtual void GiveTexture(Texture texture);

	glm::vec2 GetPositionInPixels();
	// Note that the angle is in radians
	float GetAngle();

	void AddContact(B2Entity* contact);
	void RemoveContact(B2Entity* contact);

	virtual void SetActive(bool active);

protected:
	Camera* camera;
	Shader* shader;
	b2Body* body;
	b2World* world;
	Texture texture;

	GLuint VBO, VAO, EBO;
	b2Fixture* fixture;
	b2Vec2 point[4];

	std::vector<B2Entity*> contacts;
	int width, height;
private:

};
#endif // !B2ENTITY_H
