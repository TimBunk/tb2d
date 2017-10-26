/*#include "hand.h"

Hand::Hand(Camera* camera, Shader* shader, float radius) : Renderable(camera, shader) {
	this->radius = radius;
	angle = glm::vec2(0.0f);
}

Hand::~Hand() {

}

void Hand::Update(float deltaTime) {

}

void Hand::Draw() {
	shader->Use();
	shader->SetMatrix4("projection", camera->GetProjectionMatrix());
	shader->SetMatrix4("view", camera->GetViewMatrix());
	glm::mat4 model;
	model = glm::translate(model, glm::vec3(this->GetGlobalPosition().x, this->GetGlobalPosition().y, this->GetGlobalPosition().z));
	rotation = (float)atan2(angle.y, angle.x);
	model = glm::rotate(model, (float)atan2(angle.y, angle.x), glm::vec3(0.0f, 0.0f, 1.0f));
	model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
	shader->SetMatrix4("model", model);
	glActiveTexture(GL_TEXTURE0 + texture.id);
	shader->SetInt("ourTexture", texture.id);
	glBindTexture(GL_TEXTURE_2D, texture.id);
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	glActiveTexture(GL_TEXTURE0);
	glBindVertexArray(0);
}

void Hand::SetAngle(glm::vec2 angle) {
	this->angle = angle;
}

float Hand::GetAngle() {
	return rotation;
}
*/
