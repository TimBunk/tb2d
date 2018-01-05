#include "textinput.h"

Textinput::Textinput(bool onlyNumbers, Font font, glm::vec3 textColor, bool hud, int width, int height, unsigned int textureID) : Sprite(width, height, textureID)
{
	this->onlyNumbers = onlyNumbers;
	this->hud = hud;
	text = new Text("", font, textColor, Text::AlignmentX::leftX, Text::AlignmentY::centerY);
	text->localPosition.x = -width / 2;
	AddChild(text);
	active = false;
	input = "";
	number = 0;
	maxLength = 9000;
	maxDecimals = 9000;
	maxDecimalsAfterDot = 9000;
}

Textinput::Textinput(bool onlyNumbers, Font font, glm::vec3 textColor, bool hud, int width, int height, glm::vec4 color) : Sprite(width, height, 0)
{
	this->onlyNumbers = onlyNumbers;
	this->hud = hud;
	text = new Text("", font, textColor, Text::AlignmentX::leftX, Text::AlignmentY::centerY);
	text->localPosition.x = -width / 2;
	AddChild(text);
	this->SetColor(color);
	active = false;
	input = "";
	number = 0;
	maxLength = 9000;
	maxDecimals = 9000;
	maxDecimalsAfterDot = 9000;
}

Textinput::~Textinput()
{
	delete text;
}

void Textinput::Update(double deltaTime)
{
	// Check if the textinput has been clicked or not and set active or not according to that feedback
	glm::vec2 mousePos;
	if (hud) {
		mousePos = Input::GetMousePositionScreenSpace();
	}
	else {
		mousePos = Input::GetMousePositionWorldSpace();
	}
	if (Input::MousePress(0) || Input::KeyPress(GLFW_KEY_ENTER)) {
		active = false;
	}
	if (mousePos.x >= (this->position.x - (this->width / 2 * scale.x)) && mousePos.x <= (this->position.x + (this->width / 2 * scale.x)) && mousePos.y >= (this->position.y - (this->height / 2 * scale.y)) && mousePos.y <= (this->position.y + (this->height / 2 * scale.y))) {
		if (Input::MousePress(0)) {
			active = true;
		}
	}

	if (active) {
		if (Input::KeyPress(GLFW_KEY_BACKSPACE)) {
			if (input.length() > 0) {
				input.pop_back();
				if (onlyNumbers) {
					while (input.length() > 0) {
						std::stringstream myStream(input);
						if (myStream >> number) {
							break;
						}
						else {
							input.pop_back();
						}
					}
				}
				text->SetText(input);
			}
		}
		if (Input::NewChar()) {
			if (input.length() >= maxLength) {
				return;
			}

			char c = Input::GetKeyPressChar();
			if (onlyNumbers == false) {
				input += c;
				text->SetText(input);
			}
			else {
				// USE ONLY NUMBERS
				if (c == '.') {
					for (int i = 0; i < input.length(); i++) {
						if (input[i] == '.') {
							return;
						}
					}
					maxDecimalsAfterDot = input.length();
				}
				if (c == '0' || c == '1' || c == '2' || c == '3' || c == '4' || c == '5' || c == '6' || c == '7' || c == '8' || c == '9' || c == '.') {
					if (input.length() > maxDecimalsAfterDot + maxDecimals) {
						return;
					}
					else if (input.length() == maxDecimalsAfterDot && c != '.') {
						maxDecimalsAfterDot = 9000;
					}
					input += c;
					while (input.length() > 0) {
						std::stringstream myStream(input);
						if (myStream >> number) {
							text->SetText(input);
							return;
						}
						else {
							input.pop_back();
						}
					}
					text->SetText(input);
				}
			}
		}
	}
}
