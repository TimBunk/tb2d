#include "raycastCallBack.h"

RaycastCallBack::RaycastCallBack() : b2RayCastCallback::b2RayCastCallback() {
	// Initialize all variables with a value to avoid conflicts
	camera = nullptr;
	shader = nullptr;
	color = glm::vec4(0.0f);
	lineWidth = 0;
	VAO = 0;
	VBO = 0;
}

RaycastCallBack::~RaycastCallBack() {
	
}

void RaycastCallBack::CreateLine(float length, float width, Camera* camera, Shader* shader, glm::vec3 color) {
	// Save all of the given parameters
	this->camera = camera;
	this->lineWidth = width;
	this->shader = shader;
	this->color = color;
	// Create the line
	float vertices[] = {
		0.0f, 0.0f ,
		-1.0f * length, 0.0f
	};

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	glBindVertexArray(0);
}

void RaycastCallBack::ChangeColor(glm::vec3 color)
{
	this->color = color;
}

void RaycastCallBack::Draw(glm::vec2 position, float angle) {
	// Draw the line according to the debugRendere's shader
	shader->Use();
	glm::mat4 model;
	model = glm::translate(model, glm::vec3(position.x, position.y, 1.0f));
	model = glm::rotate(model, angle, glm::vec3(0.0f, 0.0f, 1.0f));
	shader->SetMatrix4("model", model);
	shader->SetMatrix4("projection", camera->GetProjectionMatrix());
	shader->SetMatrix4("view", camera->GetViewMatrix());
	shader->SetVec3Float("color", color);
	glLineWidth(lineWidth);
	glBindVertexArray(VAO);
	glDrawArrays(GL_LINES, 0, 2);
	glBindVertexArray(0);
}

float32 RaycastCallBack::ReportFixture(b2Fixture* fixture, const b2Vec2& point, const b2Vec2& normal, float32 fraction) {
	// The Raycast will detect the crystals but ingores them
	B2Entity* b = static_cast<B2Entity*>(fixture->GetUserData());
	if (dynamic_cast<Crystal*>(b) != NULL) {
		Crystal* c = dynamic_cast<Crystal*>(b);
		c->Hit();
		linkables.push_back(c);
		return -1;
	}
	// Set all of the values in a RaycastOutput struct that can be received by calling GetOutput()
	ro.fixture = fixture;
	ro.point = point;
	ro.normal = normal;
	ro.fraction = fraction;
	return fraction;
}

RaycastOutput RaycastCallBack::GetOutput() {
	// Return the RaycastOutput
	RaycastOutput ro2 = ro;
	ro.fixture = nullptr;
	return ro2;
}
