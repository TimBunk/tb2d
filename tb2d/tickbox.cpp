#include "tickbox.h"

Tickbox::Tickbox(bool hud, unsigned int notActiveTextureID, int width, int height, unsigned int activeTextureID) : Sprite(width, height, notActiveTextureID)
{
	this->hud = hud;
	this->notActiveTextureID = notActiveTextureID;
	this->activeTextureID = activeTextureID;
	active = false;
}

Tickbox::Tickbox(bool hud, glm::vec4 notActiveColor, int width, int height, glm::vec4 activeColor) : Sprite(width, height, 0)
{
	this->hud = hud;
	this->notActiveColor = notActiveColor;
	this->activeColor = activeColor;
	active = false;

	this->SetColor(notActiveColor);
	notActiveTextureID = 0;
	activeTextureID = 0;
}

Tickbox::~Tickbox()
{
}

void Tickbox::Update(double deltaTime)
{
	glm::vec2 mousePos;
	if (hud) {
		mousePos = Input::GetMousePositionScreenSpace();
	}
	else {
		mousePos = Input::GetMousePositionWorldSpace();
	}
	if (mousePos.x >= (this->position.x - (this->width / 2 * scale.x)) && mousePos.x <= (this->position.x + (this->width / 2 * scale.x)) && mousePos.y >= (this->position.y - (this->height / 2 * scale.y)) && mousePos.y <= (this->position.y + (this->height / 2 * scale.y))) {
		if (Input::MousePress(0)) {
			if (active) {
				SetActive(false);
			}
			else {
				SetActive(true);
			}
		}
	}
}

void Tickbox::SetActive(bool active)
{
	this->active = active;
	if (active) {
		this->SetColor(activeColor);
		this->SetTextureID(activeTextureID);
	}
	else {
		this->SetColor(notActiveColor);
		this->SetTextureID(notActiveTextureID);
	}
}
