#include "button.h"

Button::Button(int x, int y, int width, int height, bool HUD, std::string text, glm::vec4 color, Input* input, Camera* camera, ResourceManager* rm) : Entity::Entity() {
	this->localPosition = glm::vec3(x, y, 1.0f);
	this->width = width;
	this->height = height;
	this->HUD = HUD;
	this->input = input;
	this->camera = camera;
	if (HUD) {
		this->text = new Text("fonts/OpenSans-Regular.ttf", text, 60, glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), true, camera, rm->GetShader("textHud"));
		shader = rm->GetShader("colorHUD");
	}
	else {
		this->text = new Text("fonts/OpenSans-Regular.ttf", text, 60, glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), false, camera, rm->GetShader("text"));
		shader = rm->GetShader("color");
	}
	this->text->localPosition = glm::vec3(x - this->text->GetWidth()/4, y, 1.0f);
	this->AddChild(this->text);
	this->color = color;
	hover = false;
	down = false;
	VAO = 0;
	VBO = 0;
	EBO = 0;
	float vertices[] = {
		// position
		-width/2, -height/2,  // lower-left corner
		width/2, -height/2,  // lower-right corner
		width/2, height/2,  // upper-right corner
		-width/2, height/2,  // uper left corner
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
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	glBindVertexArray(0);
}
Button::~Button() {
	delete text;
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
	if (mouseX >= (this->localPosition.x - (this->width/2)) && mouseX <= (this->localPosition.x + (this->width/2)) && mouseY >= (this->localPosition.y - (this->height/2)) && mouseY <= (this->localPosition.y + (this->height/2))) {
		hover = true;
		if (input->MousePress(1)) {
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
	shader->SetVec4Float("color", color);
	shader->SetMatrix4("projection", camera->GetProjectionMatrix());
	if (!HUD) {
		shader->SetMatrix4("view", camera->GetViewMatrix());
	}
	glm::mat4 model;
	model = glm::translate(model, this->GetGlobalPosition());
	model = glm::rotate(model, this->GetGlobalAngle(), glm::vec3(0.0f, 0.0f, 1.0f));
	model = glm::scale(model, glm::vec3(1.0f, 1.0f, 0.0f));
	shader->SetMatrix4("model", model);
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}

void Button::SetColor(glm::vec4 color) {
	this->color = color;
}

void Button::SetText(std::string text) {
	this->text->localPosition = glm::vec3(this->text->localPosition.x + this->text->GetWidth()/4, this->text->localPosition.y, 1.0f);
	this->text->SetText(text);
	this->text->localPosition = glm::vec3(this->text->localPosition.x - this->text->GetWidth()/4, this->text->localPosition.y, 1.0f);
}

void Button::SetTextFontSize(int fontSize) {
	this->text->localPosition = glm::vec3(this->text->localPosition.x + this->text->GetWidth()/4, this->text->localPosition.y, 1.0f);
	text->SetFontSize(fontSize);
	this->text->localPosition = glm::vec3(this->text->localPosition.x - this->text->GetWidth()/4, this->text->localPosition.y, 1.0f);
}
void Button::SetTextColor(glm::vec4 color) {
	this->text->localPosition = glm::vec3(this->text->localPosition.x + this->text->GetWidth()/4, this->text->localPosition.y, 1.0f);
	text->SetColor(color);
	this->text->localPosition = glm::vec3(this->text->localPosition.x - this->text->GetWidth()/4, this->text->localPosition.y, 1.0f);
}

bool Button::Hover() {
	return hover;
}

bool Button::Down() {
	return down;
}
