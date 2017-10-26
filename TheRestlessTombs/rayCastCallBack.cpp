#include "rayCastCallBack.h"
#include "enemy.h"

RayCastCallBack::RayCastCallBack() : b2RayCastCallback::b2RayCastCallback() {
	Camera* camera = nullptr;
	Shader* shader = nullptr;
	glm::vec4 color = glm::vec4(0.0f);
}

RayCastCallBack::~RayCastCallBack() {

}

void RayCastCallBack::CreateLine(float length, float width, Camera* camera, Shader* shader, glm::vec4 color) {
	this->camera = camera;
	this->lineWidth = width;
	this->shader = shader;
	this->color = color;
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

void RayCastCallBack::Draw(glm::vec2 position, float angle) {
	shader->Use();
	glm::mat4 model;
	model = glm::translate(model, glm::vec3(position.x, position.y, 1.0f));
	model = glm::rotate(model, angle, glm::vec3(0.0f, 0.0f, 1.0f));
	shader->SetMatrix4("model", model);
	shader->SetMatrix4("projection", camera->GetProjectionMatrix());
	shader->SetMatrix4("view", camera->GetViewMatrix());
	shader->SetVec4Float("color", color);
	glLineWidth(lineWidth);
	glBindVertexArray(VAO);
	glDrawArrays(GL_LINES, 0, 2);
	glBindVertexArray(0);
}

float32 RayCastCallBack::ReportFixture(b2Fixture* fixture, const b2Vec2& point, const b2Vec2& normal, float32 fraction) {
	// THE RAYCAST IGNORES SENSORS AND ENEMY'S
	if (fixture->IsSensor()) {
		return -1;
	}
	/*else if (static_cast<Enemy*>(fixture->GetUserData()) != NULL) {
		std::cout << "fraction = " << fraction << std::endl;
		return 2;
	}*/
	ro.fixture = fixture;
	ro.point = point;
	ro.normal = normal;
	ro.fraction = fraction;
	return fraction;
}

RaycastOutput RayCastCallBack::GetOutput() {
	return ro;
}
