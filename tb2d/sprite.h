#ifndef SPRITE_H
#define SPRITE_H

#include "entity.h"
#include "shader.h"
#include "texture.h"
#include "camera.h"

class Sprite : public Entity {
public:
	Sprite(int width, int height, Texture* texture, Shader* shader, Camera* camera);
	virtual ~Sprite();

	void Draw();
	void SetTexture(Texture* texture);
	void SetShader(Shader* shader);

private:
	GLuint VAO;
	GLuint VBO;
	Texture* texture;
	Shader* shader;
	Camera* camera;
};

#endif // !SPRITE_H