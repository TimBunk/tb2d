#ifndef RENDERABLE_H
#define RENDERABLE_H

#include "entity.h"
#include "texture.h"
#include "camera.h"
#include "shader.h"

class Renderable : public Entity {
public:
	Renderable(Camera* camera, Shader* shader);
	~Renderable();

	void Update(float deltaTime);
	virtual void Draw();

	void GiveTexture(Texture texture);
	// repeat means how many times the texture should repeat this goes by the amount of pixels
	virtual void CreateBody(int x, int y, int w, int h, float textureWidth, float textureHeight);
protected:
	GLuint VBO, VAO, EBO;
	Camera* camera;
	Shader* shader;
	Texture texture;
private:

};

#endif // !RENDERABLE_H
