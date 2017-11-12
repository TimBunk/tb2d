#include "person.h"

Person::Person(ResourceManager* rm, Camera* camera, Shader* shader, b2World* world) : Destructable::Destructable(camera, shader, world) {
	// Initialize all of the variables
	this->rm = rm;
    health = 0;
    currentHealth = health;
    damage = 0;
    attackSpeed = 0;
    speed = 0;
    flippedTexture = false;
    currentX = this->localPosition.x;

    damaged = false;
    cooldownDamaged = 0.25f;
    timerDamaged = 0.0f;
}

Person::~Person() {

}

void Person::Draw() {
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
		// If a person got damaged make it red so that it is clearly noticable for the user
		if (damaged) {
			shader->SetFloat("red", 0.5f);
		}
		else {
			shader->SetFloat("red", 0.0f);
		}
		glActiveTexture(GL_TEXTURE0 + texture.id);
		shader->SetInt("ourTexture", texture.id);
		glBindTexture(GL_TEXTURE_2D, texture.id);
		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glActiveTexture(GL_TEXTURE0);
		glBindVertexArray(0);
	}
}

bool Person::IsAlive() {
	// If the person has no health return false
	if (currentHealth <= 0) {
		return false;
	}
	return true;
}

void Person::TakeDamage(int damage) {
	// Make sure the health never drops below 0
	if (currentHealth - damage > 0) {
		currentHealth -= damage;
		damaged = true;
	}
	else {
		currentHealth = 0;
	}
}

void Person::ApplyHealing(int healing) {
	// Make sure that the person doesn't get more currentHealth then it's total health
	if (healing + currentHealth > health) {
		currentHealth = health;
	}
	else {
		currentHealth += healing;
	}
}

void Person::FlipTexture() {
	// Flip the uv coordinates and recreate the VAO
	float vertices[16];
	if (flippedTexture) {
		flippedTexture = false;
		vertices[0] = point[0].x; vertices[1] = point[0].y; vertices[2] = 0.0f; vertices[3] = 0.0f;  // lower-left corner
		vertices[4] = point[1].x; vertices[5] = point[1].y; vertices[6] = 1.0f; vertices[7] = 0.0f;  // lower-right corner
		vertices[8] = point[2].x; vertices[9] = point[2].y; vertices[10] = 1.0f; vertices[11] = 1.0f;  // upper-right corner
		vertices[12] = point[3].x; vertices[13] = point[3].y; vertices[14] = 0.0f; vertices[15] = 1.0f;  // uper left corner
	}
	else {
		flippedTexture = true;
		vertices[0] = point[0].x; vertices[1] = point[0].y; vertices[2] = 1.0f; vertices[3] = 0.0f;  // lower-left corner
		vertices[4] = point[1].x; vertices[5] = point[1].y; vertices[6] = 0.0f; vertices[7] = 0.0f;  // lower-right corner
		vertices[8] = point[2].x; vertices[9] = point[2].y; vertices[10] = 0.0f; vertices[11] = 1.0f;  // upper-right corner
		vertices[12] = point[3].x; vertices[13] = point[3].y; vertices[14] = 1.0f; vertices[15] = 1.0f;  // uper left corner
	}

	unsigned int indices[] = {
		0, 1, 3,
		1, 2, 3
	};

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);

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

bool Person::IsTextureFlipped() {
	return flippedTexture;
}
