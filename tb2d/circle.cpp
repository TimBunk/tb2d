#include "circle.h"

Circle::Circle(int x, int y, int radius, bool dynamic, float p2m, b2World* world, glm::mat4 projection) {
	this->projection = projection;
	this->world = world;
	// Step 1 defina a body
	b2BodyDef bodydef;
	bodydef.position.Set(x*p2m, y*p2m);
	if (dynamic) {
		bodydef.type = b2_dynamicBody;
	}
	else {
		bodydef.type = b2_staticBody;
	}

	// Step 2 create a body
	body = world->CreateBody(&bodydef);

	// Step 3 create shape
	b2CircleShape shape;
	shape.m_p.Set(0.0f, 0.0f);
	shape.m_radius = radius * p2m;

	// step 4 create fixture
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &shape;
	fixtureDef.density = 1.0;
	fixtureDef.friction = 0.3f;
	fixtureDef.restitution = 0.5f;
	fixture = body->CreateFixture(&fixtureDef);

	// step 5 setup the debugRenderer
	dr = new DebugRenderer(projection, glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
	dr->DrawCircle(glm::vec3(0.0f), radius * p2m);
	dr->Init();

	float vertices[] = {
		// position
		-radius * p2m, -radius * p2m, 0.0f, 0.0f,  // lower-left corner
		radius * p2m, -radius * p2m, 1.0f, 0.0f,  // lower-right corner
		radius * p2m, radius * p2m, 1.0f, 1.0f,  // upper-left corner
		-radius * p2m, radius * p2m, 0.0f, 1.0f  // uper right corner
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

Circle::~Circle()
{
	body->DestroyFixture(fixture);
	world->DestroyBody(body);
	delete dr;
}

void Circle::Draw(glm::mat4 view, Shader* shader, float m2p)
{
	shader->SetMatrix4("projection", projection);
	shader->SetMatrix4("view", view);
	glm::mat4 model;
	model = glm::translate(model, GetPositionInPixels(m2p));
	model = glm::rotate(model, GetAngle(), glm::vec3(0.0f, 0.0f, 1.0f));
	model = glm::scale(model, glm::vec3(m2p, m2p, 0.0f));
	shader->SetMatrix4("model", model);
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
	dr->Render(view, model, 1.0f);
}

glm::vec3 Circle::GetPositionInPixels(float m2p)
{
	glm::vec3 pos;
	pos = glm::vec3(body->GetPosition().x * m2p, body->GetPosition().y * m2p, 0.0f);
	return pos;
}

float Circle::GetAngle()
{
	float angle;
	angle = body->GetAngle();
	return angle;
}
