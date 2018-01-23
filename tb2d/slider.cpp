#include "slider.h"

Slider::Slider(int widthButton, int heightButton, glm::vec4 colorButton, bool hud, int width, int height, unsigned int textureID) : Sprite::Sprite(width, height, textureID)
{
	// Initialize variables
	button = new Button(widthButton, heightButton, 0, hud);
	button->SetColor(colorButton);
	this->AddChild(button);
	// Set position of the button
	value = 0.0f;
	SetValue(value);
}

Slider::~Slider()
{
	// Delete the allocated memory
	delete button;
}

void Slider::Update(double deltaTime)
{
	// Move the button according to the mouse's position if the button is being helddown
	if (button->HeldDown()) {
		button->localPosition.y += Input::GetMousePositionScreenSpace().y - button->GetGlobalPosition().y;
		button->UpdateChilderen(this, 0);
		if (this->GetGlobalPosition().y + this->height / 2 < button->GetGlobalPosition().y) {
			button->localPosition.y += (this->GetGlobalPosition().y + this->height / 2) - button->GetGlobalPosition().y;
		}
		else if (this->GetGlobalPosition().y - this->height / 2 > button->GetGlobalPosition().y) {
			button->localPosition.y += (this->GetGlobalPosition().y - this->height / 2) - button->GetGlobalPosition().y;
		}
		// Calculate the value, the value is always between 0 and 1
		button->UpdateChilderen(this, 0);
		value = (this->GetGlobalPosition().y - this->height / 2 - button->GetGlobalPosition().y) / height * -1;
	}
}

void Slider::SetRenderer(SimpleRenderer * renderer)
{
	// Set the renderer both for this and the button
	this->renderer = renderer;
	button->SetRenderer(renderer);
}

void Slider::SetValue(float newValue)
{
	float newPos = this->GetGlobalPosition().y - this->height / 2 + (newValue * this->height);
	button->localPosition.y += newPos - button->GetGlobalPosition().y;
	button->UpdateChilderen(this, 0);
	value = newValue;
}
