#ifndef RENDERABLE_H
#define RENDERABLE_H

#include "entity.h"
#include "texture.h"
#include "camera.h"
#include "shader.h"

class Renderable : public Entity {
public:
	Renderable(Texture texture, Camera* camera, Shader* shader);
	~Renderable();

	virtual void Draw();
	// Example textureWidth: Lets say your w = 50 but your textureWidth is 25 that means your texture will fit in 2 times
	virtual void CreateBody(int x, int y, int w, int h, float textureWidth, float textureHeight);

protected:
	GLuint VBO, VAO, EBO;
	Camera* camera;
	Shader* shader;
	Texture texture;

};

#endif // !RENDERABLE_H
