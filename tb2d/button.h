#ifndef BUTTON_H
#define BUTTON_H

#include "input.h"
#include "text.h"
#include "sprite.h"

class Button : public Sprite {
public:
	Button(int width, int height, unsigned int textureID, bool hud, Camera* camera);
	virtual ~Button();

	void Update(double deltaTime);

	void CreateText(std::string text, Font font, glm::vec3 color);
	void SetText(std::string text);
	void SetTextColor(glm::vec4 color);

	bool Hover();
	bool Down();

private:
	Text* text;
	Camera* camera;

	bool hud;
	bool hover;
	bool down;
};

#endif //!BUTTON_H