#include "hud.h"

Hud::Hud(int x, int y, int w, int h, Camera* camera, Shader* shader, Texture texture) : Entity::Entity() {
	this->localPosition.x = x;
	this->localPosition.y = y;
	this->w = w;
	this->h = h;
	this->camera = camera;
	this->shader = shader;
	this->texture = texture;

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	// create vertices on the heap
	GLfloat* vertices;
	vertices = new GLfloat[16];
	// position
	vertices[0] = this->w/2 * -1; vertices[1] = this->h/2 * -1; vertices[2] = 0.0f; vertices[3] = 0.0f;  // lower-left corner
	vertices[4] = this->w/2; vertices[5] = this->h/2 * -1; vertices[6] = 1.0f; vertices[7]  = 0.0f;  // lower-right corner
	vertices[8] = this->w/2; vertices[9] = this->h/2; vertices[10] = 1.0f; vertices[11] = 1.0f;  // upper-right corner
	vertices[12] = this->w/2 * -1; vertices[13] = this->h/2; vertices[14] =  0.0f; vertices[15] =  1.0f;  // uper left corner

	glBufferData(GL_ARRAY_BUFFER, 16 * sizeof(GLfloat), &vertices[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

	// create the indices on the heap
	GLuint * indices;
	indices = new GLuint[6];
	indices[0] = 0; indices[1] = 1; indices[2] = 3;
	indices[3] = 1; indices[4] =  2; indices[5] = 3;

	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(GLuint), &indices[0], GL_STATIC_DRAW);

	// set the vertices
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLuint), (GLvoid*)(2 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	glBindVertexArray(0);

	// delete the vertices and indices created on the heap
	delete vertices;
	delete indices;
}

Hud::~Hud() {

}

void Hud::Update(double deltaTime) {

}

void Hud::Draw() {
	shader->Use();
	shader->SetMatrix4("projection", camera->GetProjectionMatrix());
	glm::mat4 model;
	model = glm::translate(model, this->localPosition);
	model = glm::rotate(model, glm::radians(this->GetGlobalAngle()), glm::vec3(0.0f, 0.0f, 1.0f));
	model = glm::scale(model, glm::vec3(this->GetGlobalScale().x, this->GetGlobalScale().y, 1.0f));
	shader->SetMatrix4("model", model);
	glActiveTexture(GL_TEXTURE0 + texture.id);
	shader->SetInt("ourTexture", texture.id);
	glBindTexture(GL_TEXTURE_2D, texture.id);
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	glActiveTexture(GL_TEXTURE0);
	glBindVertexArray(0);
}

void Hud::SetTexture(Texture texture) {
	this->texture = texture;
}
