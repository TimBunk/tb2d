#include "circle.h"

Circle::Circle(Camera* camera, Shader* shader, Shader* debug) : B2Entity::B2Entity(camera, shader) {
    dr = new DebugRenderer(camera, debug, glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));
}

Circle::~Circle()
{
	delete dr;
}

void Circle::Update(float deltaTime) {
	for (int i=0;i<contacts.size();i++) {
		std::cout << "A COLLISION HAPPEND!" << std::endl;
	}
}

void Circle::Draw() {
	shader->Use();
	shader->SetMatrix4("projection", camera->GetProjectionMatrix());
	shader->SetMatrix4("view", camera->GetViewMatrix());
	glm::mat4 model;
	model = glm::translate(model, glm::vec3(body->GetPosition().x * Window::m2p, body->GetPosition().y * Window::m2p, this->GetGlobalPosition().z));
	model = glm::rotate(model, body->GetAngle(), glm::vec3(0.0f, 0.0f, 1.0f));
	model = glm::scale(model, glm::vec3(Window::m2p, Window::m2p, 0.0f));
	shader->SetMatrix4("model", model);
	glActiveTexture(GL_TEXTURE0 + texture.id);
	shader->SetInt("ourTexture", texture.id);
	glBindTexture(GL_TEXTURE_2D, texture.id);
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	glActiveTexture(GL_TEXTURE0);
	glBindVertexArray(0);
	dr->Render(model, 100.0f);
}

void Circle::CreateBody(int x, int y, int radius, b2World* world) {
    this->world = world;
    // Step 1 defina a body
	b2BodyDef bodydef;
	bodydef.position.Set(x*Window::p2m, y*Window::p2m);
	bodydef.type = b2_dynamicBody;

	// Step 2 create a body
	body = world->CreateBody(&bodydef);

	// Step 3 create shape
	b2CircleShape shape;
	shape.m_p.Set(0.0f, 0.0f);
	shape.m_radius = radius * Window::p2m;

	// step 4 create fixture
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &shape;
	fixtureDef.density = 1.0;
	fixtureDef.friction = 0.3f;
	fixtureDef.restitution = 0.5f;
	fixture = body->CreateFixture(&fixtureDef);
	fixture->SetUserData(this);

	// step 5 setup the debugRenderer
	dr->DrawCircle(glm::vec3(0.0f), radius * Window::p2m);
	dr->Init();

	float vertices[] = {
		// position
		-radius * Window::p2m, -radius * Window::p2m, 0.0f, 0.0f,  // lower-left corner
		radius * Window::p2m, -radius * Window::p2m, 1.0f, 0.0f,  // lower-right corner
		radius * Window::p2m, radius * Window::p2m, 1.0f, 1.0f,  // upper-left corner
		-radius * Window::p2m, radius * Window::p2m, 0.0f, 1.0f  // uper right corner
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