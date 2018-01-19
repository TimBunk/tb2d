#include "textinput.h"

Textinput::Textinput(std::string text, bool onlyNumbers, Font font, glm::vec3 textColor, bool hud, int width, int height, unsigned int textureID) : Sprite(width, height, textureID)
{
	// Initialize the variables
	this->onlyNumbers = onlyNumbers;
	this->hud = hud;
	this->text = new Text(text, font, textColor, Text::AlignmentX::leftX, Text::AlignmentY::centerY);
	this->text->localPosition.x = -width / 2;
	AddChild(this->text);
	active = false;
	input = text;
	number = 0;
	std::stringstream myStream(input);
	myStream >> number;
	maxLength = 9000;
	maxDecimals = 9000;
	maxDecimalsAfterDot = 9000;
	timer = 0.0f;
}

Textinput::Textinput(std::string text, bool onlyNumbers, Font font, glm::vec3 textColor, bool hud, int width, int height, glm::vec4 color) : Sprite(width, height, 0)
{
	// Intialize the variables
	this->onlyNumbers = onlyNumbers;
	this->hud = hud;
	this->text = new Text(text, font, textColor, Text::AlignmentX::leftX, Text::AlignmentY::centerY);
	this->text->localPosition.x = -width / 2;
	AddChild(this->text);
	this->SetColor(color);
	active = false;
	input = text;
	number = 0;
	std::stringstream myStream(input);
	myStream >> number;
	maxLength = 9000;
	maxDecimals = 9000;
	maxDecimalsAfterDot = 9000;
	timer = 0.0f;
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
	// Check if the mouse is hovering over the textinput
	if (mousePos.x >= (this->position.x - (this->width / 2 * scale.x)) && mousePos.x <= (this->position.x + (this->width / 2 * scale.x)) && mousePos.y >= (this->position.y - (this->height / 2 * scale.y)) && mousePos.y <= (this->position.y + (this->height / 2 * scale.y))) {
		if (Input::MousePress(0)) {
			active = true;
		}
	}
	timer += deltaTime;
	if (active) {
		// If the user pressed backspace and the lenght of the input is longer then 0 pop_back the last character
		if (Input::KeyDown(GLFW_KEY_BACKSPACE) && timer > 0.1f) {
			timer = 0.0f;
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
		// If a new char got entered by the user type it into the textinput if maxlength has not yet been reached
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

void Textinput::SetText(std::string text)
{
	// Set the text
	input = text;
	number = 0;
	std::stringstream myStream(input);
	myStream >> number;
	this->text->SetText(input);
}
