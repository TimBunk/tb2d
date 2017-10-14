#ifndef GROUND_H
#define GROUND_H

#include "shader.h"
#include "window.h"
#include "texture.h"
#include "camera.h"

#include <GL/glew.h>
#include <glm-0.9.8.4/glm/glm.hpp>
#include <glm-0.9.8.4/glm/gtc/matrix_transform.hpp>
#include <glm-0.9.8.4/glm/gtc/type_ptr.hpp>
#include <Box2D/Box2D.h>

class Ground {
public:
	Ground(int x, int y, int w, int h, bool dyn, b2World* world, Camera* camera, Shader* shader);
	~Ground();

	void Draw();

	void SetTexture(Texture texture);

	glm::vec3 GetPositionInPixels();
	float GetAngle();
private:
	b2Vec2 point[4];
	Texture tex;
	Camera* camera;
	Shader* shader;

	GLuint VBO, VAO, EBO;
	b2World* world;
	b2Body* body;
	b2Fixture* fixture;
};

#endif
