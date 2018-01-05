#include "button.h"

Button::Button(int width, int height, unsigned int textureID, bool hud, Camera* camera) : Sprite::Sprite(width, height, textureID) {
	this->hud = hud;
	this->camera = camera;
	this->text = nullptr;
	hover = false;
	down = false;
}
Button::~Button() {
	if (text != nullptr) {
		delete text;
	}
}

void Button::Update(double deltaTime) {
	glm::vec2 mousePos;
	if (hud) {
		mousePos = Input::GetMousePositionScreenSpace();
	}
	else {
		mousePos = Input::GetMousePositionWorldSpace();
	}
	if (mousePos.x >= (this->position.x - (this->width/2 * scale.x)) && mousePos.x <= (this->position.x + (this->width/2 * scale.x)) && mousePos.y >= (this->position.y - (this->height/2 * scale.y)) && mousePos.y <= (this->position.y + (this->height/2 * scale.y))) {
		hover = true;
		if (Input::MousePress(0)) {
			down = true;
		}
		else {
			down = false;
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
	this->text = new Text(text, font, color, Text::AlignmentX::centerX, Text::AlignmentY::centerY);
	AddChild(this->text);

}

void Button::SetText(std::string text) {
	if (this->text != nullptr) {
		this->text->SetText(text);
	}
}

void Button::SetTextColor(glm::vec4 color)
{
	if (text != nullptr) {
		text->SetColor(color);
	}
}

bool Button::Hover() {
	return hover;
}

bool Button::Down() {
	return down;
}