#include "wall.h"

Wall::Wall(bool visible, Camera* camera, Shader* shader, b2World* world) : B2Entity::B2Entity(camera, shader, world) {
	this->visible = visible;
	dr = nullptr;
}

Wall::~Wall() {
	if (dr != nullptr) {
		delete dr;
	}
}

void Wall::Update(float deltaTime) {
	glm::mat4 model;
	model = glm::translate(model, glm::vec3(GetPositionInPixels(), 0.0f));
	model = glm::rotate(model, GetAngle(), glm::vec3(0.0f, 0.0f, 1.0f));
	model = glm::scale(model, glm::vec3(Window::m2p, Window::m2p, 0.0f));
	dr->Render(camera->GetViewMatrix(), model, 3.0f);
}

void Wall::Draw() {
	if (visible) {
		shader->Use();
		shader->SetMatrix4("projection", camera->GetProjectionMatrix());
		shader->SetMatrix4("view", camera->GetViewMatrix());
		glm::mat4 model;
		model = glm::translate(model, glm::vec3(GetPositionInPixels(), this->GetGlobalPosition().z));
		model = glm::rotate(model, GetAngle(), glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::scale(model, glm::vec3(Window::m2p, Window::m2p, 0.0f));
		shader->SetMatrix4("model", model);
		glActiveTexture(GL_TEXTURE0 + texture.id);
		shader->SetInt("ourTexture", texture.id);
		glBindTexture(GL_TEXTURE_2D, texture.id);
		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glActiveTexture(GL_TEXTURE0);
		glBindVertexArray(0);
	}
}

void Wall::CreateBody(int x, int y, int w, int h) {
	this->localPosition = glm::vec3(x, y, 1.0f);
	width = w;
	height = h;
	dr = new DebugRenderer(camera->GetProjectionMatrix(), glm::vec4(1.0f));
	// Step 1 defina a body
	b2BodyDef bodydef;
	bodydef.position.Set(x*Window::p2m, y*Window::p2m);
	bodydef.fixedRotation = true;
	bodydef.type = b2_staticBody;

	// Step 2 create a body
	body = world->CreateBody(&bodydef);

	// Step 3 create shape
	b2PolygonShape shape;
	// the reason for dividing by 2 is because box2D draws from the center
	shape.SetAsBox(w / 2 * Window::p2m, h / 2 * Window::p2m);
	// step 4 create fixture
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &shape;
	fixtureDef.density = 1.0;
	fixtureDef.friction = 0.3f;
	fixtureDef.restitution = 0.5f;
	fixture = body->CreateFixture(&fixtureDef);
	fixture->SetUserData(this);
	for (int i = 0; i < 4; i++) {
		point[i] = ((b2PolygonShape*)body->GetFixtureList()->GetShape())->m_vertices[i];
		//std::cout << "point " << i << ": (" << point[i].x << ") (" << point[i].y << ")" << std::endl;
	}
	dr->DrawBox(point);
	dr->Init();
	// FOR EVERY 300 pixels repeat the texture
	float multiply = ((float)w)/300.0f;
	float vertices[] = {
		// position
		point[0].x, point[0].y, 0.0f, 0.0f,  // lower-left corner
		point[1].x, point[1].y, 1.0f * multiply, 0.0f,  // lower-right corner
		point[2].x, point[2].y, 1.0f * multiply, 1.0f,  // upper-right corner
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

void Wall::SetActive(bool active) {
	if (body != NULL) {
		// To set the sensor the body needs to be active
		body->SetActive(true);
		if (!active) {
			fixture->SetSensor(true);
		}
		else {
			fixture->SetSensor(false);
		}
		body->SetActive(active);
		std::cout << "wall body is now not active" << std::endl;
	}
}
