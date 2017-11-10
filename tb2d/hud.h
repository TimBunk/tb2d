#ifndef HUD_H
#define HUD_H

#include "entity.h"
#include "camera.h"
#include "texture.h"
#include "shader.h"

class Hud : public Entity {
public:
	Hud(int x, int y, int w, int h, Camera* camera, Shader* shader, Texture texture);
	virtual ~Hud();

	virtual void Update(double deltaTime);
	virtual void Draw();

	void SetTexture(Texture texture);
	int w, h;
protected:
	//int w, h;

	Camera* camera;
	Shader* shader;
	Texture texture;

	GLuint VBO, VAO, EBO;
private:
};

#endif // !HUD_H
