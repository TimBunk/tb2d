#ifndef TICKBOX_H
#define TICKBOX_H

#include "sprite.h"
#include "input.h"

class Tickbox : public Sprite
{
public:
	Tickbox(bool hud, unsigned int notActiveTextureID, int width, int height, unsigned int activeTextureID);
	Tickbox(bool hud, glm::vec4 notActiveColor, int width, int height, glm::vec4 activeColor);
	~Tickbox();

	void Update(double deltaTime);
	void SetActive(bool active);

	bool IsActive() { return active; }

private:
	bool hud;
	bool active;
	glm::vec4 activeColor;
	glm::vec4 notActiveColor;
	unsigned int activeTextureID;
	unsigned int notActiveTextureID;
};

#endif // !TICKBOX_H
