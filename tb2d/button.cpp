#include "button.h"

Button::Button(int width, int height, unsigned int textureID, bool hud) : Sprite::Sprite(width, height, textureID) {
	// Initialize the variables
	this->hud = hud;
	this->text = nullptr;
	hover = false;
	down = false;
	heldDown = false;
}
Button::~Button() {
	// Check if text has been created and if so delete it
	if (text != nullptr) {
		delete text;
	}
}

void Button::Update(double deltaTime) {
	// Get mouse position from input
	glm::vec2 mousePos;
	if (hud) {
		mousePos = Input::GetMousePositionScreenSpace();
	}
	else {
		mousePos = Input::GetMousePositionWorldSpace();
	}
	// Checks if mousePosition is inside the Buttons space
	if (mousePos.x >= (this->position.x - (this->width/2 * scale.x)) && mousePos.x <= (this->position.x + (this->width/2 * scale.x)) && mousePos.y >= (this->position.y - (this->height/2 * scale.y)) && mousePos.y <= (this->position.y + (this->height/2 * scale.y))) {
		hover = true;
		// If left mouse button has been pressed set down to true otherwise set it to false
		if (Input::MousePress(0)) {
			down = true;
		}
		else {
			down = false;
		}
		if (Input::MouseDown(0)) {
			heldDown = true;
		}
		else {
			heldDown = false;
		}
	}
	else {
		hover = false;
		down = false;
	}
}

void Button::CreateText(std::string text, Font font, glm::vec3 color)
{
	// If a text has already been created remove the previous one
	if (this->text != nullptr) {
		RemoveChild(this->text);
		delete this->text;
	}
	// Create text with the information that we received
	this->text = new Text(text, font, color, Text::AlignmentX::centerX, Text::AlignmentY::centerY);
	AddChild(this->text);

}

void Button::SetText(std::string text) {
	// Set the text string if the text has been created
	if (this->text != nullptr) {
		this->text->SetText(text);
	}
}

void Button::SetTextColor(glm::vec4 color)
{
	// Set the text color if the text has been created
	if (text != nullptr) {
		text->SetColor(color);
	}
}

bool Button::HeldDown()
{
	if (heldDown && Input::MouseDown(0)) {
		return true;
	}
	else if (heldDown) {
		heldDown = false;
	}
	return false;
}
