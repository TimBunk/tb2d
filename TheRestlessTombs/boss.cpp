#include "boss.h"

Boss::Boss(std::string nameBoss, Player* player, float lineOfSight, ResourceManager* rm, Camera* camera, Shader* shader, b2World* world) : Enemy::Enemy(player, lineOfSight, rm, camera, shader, world) {
	// Initalize the healthbar and texBoss
	healthbar = rm->GetShader("healthbar");
	textBoss = new Text("fonts/OpenSans-Regular.ttf", nameBoss, 60, glm::vec4(0.5f, 1.0f, 0.5f, 1.0f), true, camera, rm->GetShader("textHud"));
	textBoss->localPosition = glm::vec3(camera->screenWidth/2 - (textBoss->GetWidth()/4), 25, 1);
	this->AddChild(textBoss);

	// Create the healthbar
	float vertices[] = {
		// position
		0.0f, -15.0f,  // lower-left corner
		400.0f, -15.0f, // lower-right corner
		400.0f, 15.0f,  // upper-right corner
		0.0f, 15.0f // uper left corner
	};

	unsigned int indices[] = {
		0, 1, 3,
		1, 2, 3
	};

	glGenVertexArrays(1, &HealthVAO);
	glGenBuffers(1, &HealthVBO);
	glGenBuffers(1, &HealthEBO);

	glBindVertexArray(HealthVAO);

	glBindBuffer(GL_ARRAY_BUFFER, HealthVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, HealthEBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// set the vertices
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	glBindVertexArray(0);
}

Boss::~Boss() {
	delete textBoss;
	glDeleteVertexArrays(1, &HealthVAO);
	glDeleteBuffers(1, &HealthVBO);
	glDeleteBuffers(1, &HealthEBO);
}

void Boss::Draw() {
	if (IsAlive()) {
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
	// Draw the red health
	healthbar->Use();
	healthbar->SetMatrix4("projection", camera->GetProjectionMatrix());
	healthbar->SetVec4Float("color", glm::vec4(1.0f, 0.0f, 0.0f, 0.4f));
	glm::mat4 model2;
	model2 = glm::translate(model2, glm::vec3(200.0f, 80.0f, 1.0f));
	model2 = glm::rotate(model2, GetAngle(), glm::vec3(0.0f, 0.0f, 1.0f));
	model2 = glm::scale(model2, glm::vec3(1.0f, 1.0f, 0.0f));
	healthbar->SetMatrix4("model", model2);
	glBindVertexArray(HealthVAO);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
	// Draw the green health
	healthbar->Use();
	healthbar->SetMatrix4("projection", camera->GetProjectionMatrix());
	healthbar->SetVec4Float("color", glm::vec4(0.0f, 1.0f, 0.0f, 0.4f));
	glm::mat4 model;
	model = glm::translate(model, glm::vec3(200.0f, 80.0f, 1.0f));
	model = glm::rotate(model, GetAngle(), glm::vec3(0.0f, 0.0f, 1.0f));
	model = glm::scale(model, glm::vec3((float)currentHealth/(float)health, 1.0f, 0.0f));
	healthbar->SetMatrix4("model", model);
	glBindVertexArray(HealthVAO);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}
