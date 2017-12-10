#include "button.h"

Button::Button(int width, int height, bool HUD, glm::vec3 color, Camera* camera) : Entity::Entity() {
	this->width = width;
	this->height = height;
	this->HUD = HUD;
	this->color = color;
	this->camera = camera;
	this->text = nullptr;
	if (HUD) {
		shader = ResourceManager::GetShader("colorHUD");
	}
	else {
		shader = ResourceManager::GetShader("color");
	}
	hover = false;
	down = false;
	quadData = ResourceManager::GetQuad(glm::vec2(0, 0));
}
Button::~Button() {
	if (text != nullptr) {
		delete text;
	}
}

void Button::Update(double deltaTime) {
	glm::vec2 mousePos;
	if (HUD) {
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

void Button::Draw() {
	shader->Use();
	shader->SetVec3Float("color", color);
	shader->SetMatrix4("projection", camera->GetProjectionMatrix());
	if (!HUD) {
		shader->SetMatrix4("view", camera->GetViewMatrix());
	}
	glm::mat4 _model = glm::scale(model, glm::vec3(width * GetGlobalScale().x, height * GetGlobalScale().y, 0.0f));
	shader->SetMatrix4("model", _model);
	glBindVertexArray(quadData.VAO);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glBindVertexArray(0);
}

void Button::SetColor(glm::vec3 color) {
	this->color = color;
}

void Button::CreateText(std::string text, int textSize, glm::vec3 color)
{
	// If a text has already been created remove the previous one
	if (this->text != nullptr) {
		RemoveChild(this->text);
		delete this->text;
	}
	if (HUD) {
		this->text = new Text(text, textSize, "fonts/OpenSans-Regular.ttf", color, ResourceManager::GetShader("defaultFreetypeHUD"), camera, true);
	}
	else {
		this->text = new Text(text, textSize, "fonts/OpenSans-Regular.ttf", color, ResourceManager::GetShader("defaultFreetype"), camera, false);
	}

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