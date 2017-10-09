#include "floor.h"

Floor::Floor(Camera* camera, Shader* shader) : Entity::Entity() {
	this->camera = camera;
	this->shader = shader;
}

Floor::~Floor() {

}

void Floor::Update(float deltaTime) {

}

void Floor::Draw() {
	shader->Use();
	shader->SetMatrix4("projection", camera->GetProjectionMatrix());
	shader->SetMatrix4("view", camera->GetViewMatrix());
	glm::mat4 model;
	model = glm::translate(model, this->GetGlobalPosition());
	model = glm::rotate(model, this->GetGlobalAngle(), glm::vec3(0.0f, 0.0f, 1.0f));
	model = glm::scale(model, glm::vec3(1.0f, 1.0f, 0.0f));
	shader->SetMatrix4("model", model);
	glActiveTexture(GL_TEXTURE0 + texture.id);
	shader->SetInt("ourTexture", texture.id);
	glBindTexture(GL_TEXTURE_2D, texture.id);
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	glActiveTexture(GL_TEXTURE0);
	glBindVertexArray(0);
}

void Floor::GiveTexture(Texture texture) {
	this->texture = texture;
}

void Floor::CreateBody(int x, int y, int w, int h, float textureWidth, float textureHeight) {
	this->localPosition.x = x;
	this->localPosition.y = y;
	float multiplyW = w/textureWidth;
	float multiplyH = h/textureHeight;
	float vertices[] = {
		// position
		-w/2, -h/2, 0.0f, 0.0f,  // lower-left corner
		w/2, -h/2, 1.0f * multiplyW, 0.0f,  // lower-right corner
		w/2, h/2, 1.0f * multiplyW, 1.0f * multiplyH,  // upper-right corner
		-w/2, h/2, 0.0f, 1.0f * multiplyH  // uper left corner
	};

	unsigned int indices[] = {
		0, 1, 3,
		1, 2, 3
	};

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// set the vertices
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid*)(2 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	glBindVertexArray(0);
}
