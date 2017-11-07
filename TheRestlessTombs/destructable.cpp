#include "destructable.h"

Destructable::Destructable(Camera* camera, Shader* shader, b2World* world) : B2Entity::B2Entity(camera, shader, world) {
	alive = true;
}

Destructable::~Destructable() {

}

void Destructable::Update(double deltaTime) {

}

void Destructable::Draw() {
	if (alive) {
		shader->Use();
		shader->SetMatrix4("projection", camera->GetProjectionMatrix());
		shader->SetMatrix4("view", camera->GetViewMatrix());
		glm::mat4 model;
		model = glm::translate(model, glm::vec3(GetPositionInPixels(), this->GetGlobalPosition().z));
		model = glm::rotate(model, GetAngle(), glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::scale(model, glm::vec3(Window::m2p, Window::m2p, 0.0f));
		shader->SetMatrix4("model", model);
		glActiveTexture(GL_TEXTURE0 + texture.id);
		shader->SetInt("ourTexture", texture.id);
		glBindTexture(GL_TEXTURE_2D, texture.id);
		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glActiveTexture(GL_TEXTURE0);
		glBindVertexArray(0);
	}
}

void Destructable::Destroy() {
	alive = false;
	SetActive(false);
}

void Destructable::Reset() {
	alive = true;
	SetActive(true);
}

bool Destructable::IsAlive() {
	return alive;
}

void Destructable::SetActive(bool active) {
	if (body != NULL) {
		if (alive || !active) {
			body->SetAwake(active);
			body->SetActive(active);
		}
	}
}
