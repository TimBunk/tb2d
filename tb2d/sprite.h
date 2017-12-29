#ifndef SPRITE_H
#define SPRITE_H

#include "entity.h"
#include "camera.h"
#include "resourceManager.h"
#include "renderManager.h"

class Sprite : public Entity {
public:
	Sprite(int width, int height, unsigned int textureID);
	virtual ~Sprite();

	virtual void Draw();

	// SETTERS
	void SetRenderer(SimpleRenderer* renderer)		{ this->renderer = renderer; };
	void SetTextureID(unsigned int textureID)		{ this->textureID = textureID; };
	void SetRepeatableUV(glm::vec2 repeat)			{ this->repeatUV = repeat; };
	void SetPivot(glm::vec2 pivot)					{ this->pivot = pivot; };
	void SetColor(glm::vec4 color)					{ this->color = color; };
	void SetWidth(int width)						{ this->width = width; };
	void SetHeight(int height)						{ this->height = height; };
	// GETTERS
	unsigned int	GetTextureID()		{ return textureID; };
	glm::vec2		GetRepeatableUV()	{ return repeatUV; };
	glm::vec2		GetPivot()			{ return pivot; };
	glm::vec4		GetColor()			{ return color; };
	int				GetWidth()			{ return width; };
	int				GetHeight()			{ return height; };

protected:
	unsigned int textureID;
	glm::vec2 repeatUV;
	glm::vec2 pivot;
	glm::vec4 color;
	int width, height;
	SimpleRenderer* renderer;

private:
	
};

#endif // !SPRITE_H