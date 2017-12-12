#ifndef SPRITE_H
#define SPRITE_H

#include "entity.h"
#include "camera.h"
#include "resourceManager.h"

class Sprite : public Entity {
public:
	Sprite(int width, int height, glm::vec2 pivot, Texture* texture, Camera* camera, bool HUD);
	virtual ~Sprite();

	virtual void Draw();
	void SetTexture(Texture* texture);
	void SetShader(Shader* shader);
	virtual void SetCamera(Camera* camera);

	int GetWidth();
	int GetHeight();

protected:
	Shader* shader;
	Camera* camera;
	int width, height;
	QuadData quadData;
	Texture* texture;
	bool HUD;

private:

};

#endif // !SPRITE_H