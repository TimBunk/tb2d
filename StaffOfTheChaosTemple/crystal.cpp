#include "crystal.h"

Crystal::Crystal(Camera * camera, Shader * shader, b2World * world) : Linkable::Linkable(camera, shader, world)
{

}

Crystal::~Crystal()
{

}

void Crystal::Update(double deltaTime)
{
	if (hit) {
		enabled = true;
		hit = false;
	}
	else {
		enabled = false;
	}
}

void Crystal::Draw()
{
	// Use the shader and draw the texture
	if (body != nullptr && texture != nullptr) {
		shader->Use();
		if (enabled) {
			shader->SetVec4Float("glow", glm::vec4(0.8f, 0.8f, 0.8f, 1.0f));
		}
		else {
			shader->SetVec4Float("glow", glm::vec4(0.0f, 0.0f, 0.0f, 0.0f));
		}
		shader->SetMatrix4("projection", camera->GetProjectionMatrix());
		shader->SetMatrix4("view", camera->GetViewMatrix());
		shader->SetMatrix4("model", model);
		glActiveTexture(GL_TEXTURE0);
		glBindVertexArray(VAO);
		glBindTexture(GL_TEXTURE_2D, texture->GetId());
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
		glBindTexture(GL_TEXTURE_2D, 0);
	}
}
