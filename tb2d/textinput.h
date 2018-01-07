#ifndef TEXTINPUT_H
#define TEXTINPUT_H

#include "sprite.h"
#include "text.h"
#include "input.h"

class Textinput : public Sprite
{
public:
	Textinput(std::string text, bool onlyNumbers, Font font, glm::vec3 textColor, bool hud, int width, int height, unsigned int textureID);
	Textinput(std::string text, bool onlyNumbers, Font font, glm::vec3 textColor, bool hud, int width, int height, glm::vec4 color);
	~Textinput();

	void Update(double deltaTime);
	bool IsActive() { return active; }

	void SetText(std::string text);
	void SetMaxLength(int maxLength) { this->maxLength = maxLength; }
	void SetMaxDecimals(int maxDecimals) { this->maxDecimals = maxDecimals; }
	float GetFloat() { return number; }
	std::string GetString() { return input; }

private:
	bool onlyNumbers;
	bool hud;
	bool active;

	int maxLength;
	int maxDecimals;
	int maxDecimalsAfterDot;

	Text* text;
	std::string input;
	float number;
};

#endif // !TEXTINPUT_H
