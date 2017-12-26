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
		mousePos = Input::GetMousePositionScreenSpace(camera);
	}
	else {
		mousePos = Input::GetMousePositionWorldSpace(camera);
	}
	if (mousePos.x >= (this->localPosition.x - (this->width/2 * scale.x)) && mousePos.x <= (this->localPosition.x + (this->width/2 * scale.x)) && mousePos.y >= (this->localPosition.y - (this->height/2 * scale.y)) && mousePos.y <= (this->localPosition.y + (this->height/2 * scale.y))) {
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

void Button::CreateText(std::string text, int textSize, glm::vec3 color)
{
	// If a text has already been created remove the previous one
	if (this->text != nullptr) {
		RemoveChild(this->text);
		delete this->text;
	}
	this->text = new Text(text, textSize, "fonts/OpenSans-Regular.ttf", color, ResourceManager::GetShader("defaultFreetype"), camera, hud);

	// Drawing the text is needed in order to get the correct width and height

 	this->text->Draw();
	this->text->localPosition = glm::vec2(this->text->GetWidth() / 2 * -1, this->text->GetHeight()/2 * -1);
	AddChild(this->text);

}

void Button::SetText(std::string text) {
	if (this->text != nullptr) {
		this->text->SetText(text);
		// Drawing the text is needed in order to get the correct width and height
		this->text->Draw();
		this->text->localPosition = glm::vec2(this->text->GetWidth() / 2 * -1.0f, this->text->GetHeight()/2 * -1);
	}
}

bool Button::Hover() {
	return hover;
}

bool Button::Down() {
	return down;
}