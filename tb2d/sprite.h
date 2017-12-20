#ifndef SPRITE_H
#define SPRITE_H

#include "entity.h"
#include "camera.h"
#include "resourceManager.h"
#include "renderManager.h"

class Sprite : public Entity {
// Give the Renderer class acces to everything from the renderer
friend class Renderer;

public:
	Sprite(int width, int height, glm::vec2 pivot, Texture* texture, Camera* camera, bool HUD);
	virtual ~Sprite();

	virtual void Draw();
	void SetTexture(Texture* texture);
	void SetShader(Shader* shader);
	virtual void SetCamera(Camera* camera);
	void SetInstancedRenderer(std::string name);
	void SetPivot(glm::vec2 pivot);
	void SetUvCoordinates(float x, float y);
	void SetColor(glm::vec4 color);

	int GetWidth();
	int GetHeight();

protected:
	Shader* shader;
	Camera* camera;
	int width, height;
	glm::vec2 pivot;
	QuadData quadData;
	Renderer* renderer;
	Texture* texture;
	glm::vec4 color;
	bool HUD;

private:
	std::vector<glm::vec2> vertexPositions;
	std::vector<glm::vec2> uvPositions;
};

#endif // !SPRITE_H