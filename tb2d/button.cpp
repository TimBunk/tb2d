#include "button.h"

Button::Button(int width, int height, bool HUD, glm::vec3 color, Input* input, Camera* camera, ResourceManager* rm) : Entity::Entity() {
	this->width = width;
	this->height = height;
	this->HUD = HUD;
	this->color = color;
	this->input = input;
	this->camera = camera;
	this->rm = rm;
	this->text = nullptr;
	if (HUD) {
		shader = rm->GetShader("colorHUD");
	}
	else {
		shader = rm->GetShader("color");
	}
	hover = false;
	down = false;
	VAO = 0;
	VBO = 0;
	EBO = 0;

	// Create the vertex array object
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	// create vertices on the stack to make sure they won't get out of range
	GLfloat* vertices;
	vertices = new GLfloat[8];
	// position
	vertices[0] = -width/2; vertices[1] = -height/2; // lower-left corner
	vertices[2] = width/2; vertices[3] = -height/2; // lower-right corner
	vertices[4] = width/2; vertices[5] = height/2; // upper-right corner
	vertices[6] = -width/2; vertices[7] = height/2; // uper left corner

	glBufferData(GL_ARRAY_BUFFER, 8 * sizeof(GLfloat), &vertices[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

	// create the indices on the stack to make sure they won't get out of range
	unsigned int * indices;
	indices = new unsigned int[6];
	indices[0] = 0; indices[1] = 1; indices[2] = 3;
	indices[3] = 1; indices[4] =  2; indices[5] = 3;

	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

	// set the vertices
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	glBindVertexArray(0);

	// delete the vertices and indices created on the stack
	delete vertices;
	delete indices;
}
Button::~Button() {
	if (text != nullptr) {
		delete text;
	}
}

void Button::Update(double deltaTime) {
	float mouseX, mouseY;
	if (HUD) {
		mouseX = input->GetMousePositionScreenSpace(camera).x;
		mouseY = input->GetMousePositionScreenSpace(camera).y;
	}
	else {
		mouseX = input->GetMousePositionWorldSpace(camera).x;
		mouseY = input->GetMousePositionWorldSpace(camera).y;
	}
	if (mouseX >= (this->localPosition.x - (this->width/2 * scale.x)) && mouseX <= (this->localPosition.x + (this->width/2 * scale.x)) && mouseY >= (this->localPosition.y - (this->height/2 * scale.y)) && mouseY <= (this->localPosition.y + (this->height/2 * scale.y))) {
		hover = true;
		if (input->MousePress(0)) {
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
	shader->SetMatrix4("model", model);
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
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
		this->text = new Text(text, textSize, "fonts/OpenSans-Regular.ttf", color, rm->GetShader("defaultFreetypeHUD"), camera, true);
	}
	else {
		this->text = new Text(text, textSize, "fonts/OpenSans-Regular.ttf", color, rm->GetShader("defaultFreetype"), camera, false);
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