#include "showCase.h"

ShowCase::ShowCase(int x, int y, int w, int h, Camera* camera, Shader* shader, Shader* textHud, Texture texture) : Hud::Hud(x, y, w, h, camera, shader, texture) {
	// Initialze variables
	item = false;
	nameItem = new Text("fonts/OpenSans-Regular.ttf", " ", 30, glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), true, camera, textHud);
	nameItem->localPosition = glm::vec3(x - nameItem->GetWidth()/4, y - nameItem->GetHeight(), 1.0f);
	this->AddChild(nameItem);
}

ShowCase::~ShowCase() {
	delete nameItem;
}

void ShowCase::Draw() {
	// Draw ShowCase
	shader->Use();
	shader->SetMatrix4("projection", camera->GetProjectionMatrix());
	glm::mat4 model;
	model = glm::translate(model, this->localPosition);
	model = glm::rotate(model, glm::radians(this->GetGlobalAngle()), glm::vec3(0.0f, 0.0f, 1.0f));
	model = glm::scale(model, glm::vec3(this->GetGlobalScale(), 1.0f));
	shader->SetMatrix4("model", model);
	glActiveTexture(GL_TEXTURE0 + texture.id);
	shader->SetInt("ourTexture", texture.id);
	glBindTexture(GL_TEXTURE_2D, texture.id);
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	glActiveTexture(GL_TEXTURE0);
	glBindVertexArray(0);
	// Draw Item if there is one
	if (item) {
		shader->Use();
		shader->SetMatrix4("projection", camera->GetProjectionMatrix());
		glm::mat4 model2;
		model2 = glm::translate(model2, this->localPosition);
		model2 = glm::rotate(model2, glm::radians(this->GetGlobalAngle()), glm::vec3(0.0f, 0.0f, 1.0f));
		model2 = glm::scale(model2, glm::vec3(this->GetGlobalScale(), 1.0f));
		shader->SetMatrix4("model", model2);
		glActiveTexture(GL_TEXTURE0 + sci.texture.id);
		shader->SetInt("ourTexture", sci.texture.id);
		glBindTexture(GL_TEXTURE_2D, sci.texture.id);
		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glActiveTexture(GL_TEXTURE0);
		glBindVertexArray(0);
	}
}

void ShowCase::Give(ShowCaseItem sci) {
	// Set the sci
	item = true;
	this->sci = sci;
	// Set the nameItem and display it
	nameItem->SetText(this->sci.name);
	nameItem->localPosition = glm::vec3(this->localPosition.x - nameItem->GetWidth()/4, this->localPosition.y - nameItem->GetHeight(), 1.0f);
}

bool ShowCase::IsFull() {
	return item;
}

void ShowCase::Clear() {
	// Removes item and clears the text
	item = false;
	nameItem->SetText(" ");
}
