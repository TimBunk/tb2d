#include "raycastCallBack.h"

RaycastCallBack::RaycastCallBack(b2World* world) : b2RayCastCallback::b2RayCastCallback() {
	// Initialize all variables with a value to avoid conflicts
	this->world = world;
	camera = nullptr;
	shader = nullptr;
	color = glm::vec4(0.0f);
	lineWidth = 0;
	VAO = 0;
	VBO = 0;
}

RaycastCallBack::~RaycastCallBack() {
	
}

void RaycastCallBack::Update(b2Vec2 startingPoint, b2Vec2 endPoint)
{
	hits.clear();
	world->RayCast(this, startingPoint, endPoint);
	if (hits.size() > 0) {
		// Sort the hits by fraction from low to high
		// The square brackets specify which variables are "captured" by the lambda, and how (by value or reference).
		// More info on lamba's https://stackoverflow.com/questions/7627098/what-is-a-lambda-expression-in-c11
		std::sort(hits.begin(), hits.end(), [](RaycastHit a, RaycastHit b) { return a.fraction < b.fraction; });
	}
}

RaycastHit RaycastCallBack::GetHit(int index)
{
	if (hits.size() > index) {
		return hits[index];
	}
	return RaycastHit();
}

int RaycastCallBack::AmountOfHits()
{
	return hits.size();
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
	RaycastHit rh;
	rh.fixture = fixture;
	rh.point = point;
	rh.normal = normal;
	rh.fraction = fraction;
	hits.push_back(rh);
	// We return 1 to trick box2D in continueing shooting the raycast
	return 1;
}