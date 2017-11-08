#include "destructable.h"

Destructable::Destructable(Camera* camera, Shader* shader, b2World* world) : B2Entity::B2Entity(camera, shader, world) {
	// Initialize alive to be true at start
	alive = true;
}

Destructable::~Destructable() {

}

void Destructable::Update(double deltaTime) {

}

void Destructable::Draw() {
	// Draw the destructable only when it is active
	if (alive) {
		shader->Use();
		shader->SetMatrix4("projection", camera->GetProjectionMatrix());
		shader->SetMatrix4("view", camera->GetViewMatrix());
		glm::mat4 model;
		model = glm::translate(model, this->GetGlobalPosition());
		model = glm::rotate(model, this->GetGlobalAngle(), glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::scale(model, glm::vec3(Window::m2p * this->GetGlobalScale().x, Window::m2p * this->GetGlobalScale().y, 0.0f));
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
	// Deactivated the Destructable
	alive = false;
	SetActive(false);
}

void Destructable::Reset() {
	// Set active again
	alive = true;
	SetActive(true);
}

bool Destructable::IsAlive() {
	// Return if alive
	return alive;
}

void Destructable::SetActive(bool active) {
	// Check if the body is initialized
	if (body != NULL) {
		// Check wheter it is alive or the active is false. This prevents from calling it multiply times
		if (alive || !active) {
			body->SetAwake(active);
			body->SetActive(active);
		}
	}
}
