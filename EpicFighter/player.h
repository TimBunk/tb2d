#ifndef PLAYER_H
#define PLAYER_H

#include "shader.h"
#include "window.h"
#include "texture.h"
#include "camera.h"
#include "input.h"

#include <GL/glew.h>
#include <glm-0.9.8.4/glm/glm.hpp>
#include <glm-0.9.8.4/glm/gtc/matrix_transform.hpp>
#include <glm-0.9.8.4/glm/gtc/type_ptr.hpp>
#include <Box2D/Box2D.h>

class Player {
public:
	Player(int x, int y, int w, int h, bool dyn, b2World* world, Camera* camera, Shader* shader);
	~Player();

	void Update(float deltaTime);
	void Draw();

	void SetMovement(SDL_Scancode left, SDL_Scancode right, Input* input);

	void SetTexture(Texture texture);

	glm::vec3 GetPositionInPixels();
	float GetAngle();

private:
	b2Vec2 point[4];
	Texture tex;
	Camera* camera;
	Shader* shader;
	Input* input;
	SDL_Scancode left;
	SDL_Scancode right;

	GLuint VBO, VAO, EBO;
	b2World* world;
	b2Body* body;
	b2Fixture* fixture;
};

#endif
