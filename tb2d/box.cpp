#include "box.h"

Box::Box(int x, int y, int w, int h, bool dyn, float p2m, b2World * world, glm::mat4 projection)
{
	this->projection = projection;
	this->world = world;
	// Step 1 defina a body
	b2BodyDef bodydef;
	bodydef.position.Set(x*p2m, y*p2m);
	if (dyn) {
		bodydef.type = b2_dynamicBody;
	}
	else {
		bodydef.type = b2_staticBody;
	}

	// Step 2 create a body
	body = world->CreateBody(&bodydef);

	// Step 3 create shape
	b2PolygonShape shape;
	// the reason for dividing by 2 is because box2D draws from the center
	shape.SetAsBox(w / 2 * p2m, h / 2 * p2m);

	// step 4 create fixture
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &shape;
	fixtureDef.density = 1.0;
	fixtureDef.friction = 0.3f;
	fixtureDef.restitution = 0.5f;
	fixture = body->CreateFixture(&fixtureDef);
	//b2Vec2 point[4];
	dr = new DebugRenderer(projection, glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
	for (int i = 0; i < 4; i++) {
		point[i] = ((b2PolygonShape*)body->GetFixtureList()->GetShape())->m_vertices[i];
		//std::cout << "point " << i << ": (" << point[i].x << ") (" << point[i].y << ")" << std::endl;
	}
	dr->DrawBox(point);
	dr->Init();

	float vertices[] = {
		// position
		point[0].x, point[0].y, 0.0f, 0.0f,  // lower-left corner
		point[1].x, point[1].y, 1.0f, 0.0f,  // lower-right corner
		point[2].x, point[2].y, 1.0f, 1.0f,  // upper-right corner
		point[3].x, point[3].y, 0.0f, 1.0f  // uper left corner
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

Box::~Box()
{
	body->DestroyFixture(fixture);
	world->DestroyBody(body);
	delete dr;
}

void Box::Draw(glm::mat4 view, Shader* shader, float m2p)
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

glm::vec3 Box::GetPositionInPixels(float m2p)
{
	glm::vec3 pos;
	pos = glm::vec3(body->GetPosition().x * m2p, body->GetPosition().y * m2p, 0.0f);
	return pos;
}

float Box::GetAngle()
{
	float angle;
	angle = body->GetAngle();
	return angle;
}
