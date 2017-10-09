#ifndef FLOOR_H
#define FLOOR_H

#include "entity.h"
#include "texture.h"
#include "camera.h"
#include "shader.h"

class Floor : public Entity {
public:
	Floor(Camera* camera, Shader* shader);
	~Floor();

	void Update(float deltaTime);
	void Draw();

	void GiveTexture(Texture texture);
	// repeat means how many times the texture should repeat this goes by the amount of pixels
	void CreateBody(int x, int y, int w, int h, float textureWidth, float textureHeight);

private:
	GLuint VBO, VAO, EBO;
	Camera* camera;
	Shader* shader;
	Texture texture;
};

#endif // !FLOOR_H
