#ifndef SPRITE_H
#define SPRITE_H

#include "entity.h"
#include "camera.h"
#include "resourceManager.h"

class Sprite : public Entity {
public:
	Sprite(int width, int height, Texture* texture, Shader* shader, Camera* camera, bool HUD);
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
	bool HUD;
};

#endif // !SPRITE_H