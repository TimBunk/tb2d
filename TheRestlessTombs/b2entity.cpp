#include "b2entity.h"

B2Entity::B2Entity(Camera* camera, Shader* shader, b2World* world) : Entity::Entity() {
	this->camera = camera;
	this->shader = shader;
	this->world = world;
	fixture = nullptr;
	body = nullptr;
	VBO = 0;
	VAO = 0;
	EBO = 0;
	width = 0;
	height = 0;
}

B2Entity::~B2Entity() {
	if (body != NULL) {
		body->DestroyFixture(fixture);
		world->DestroyBody(body);
		glDeleteVertexArrays(1, &VAO);
		glDeleteBuffers(1, &VBO);
		glDeleteBuffers(1, &EBO);
	}
}

void B2Entity::Update(double deltaTime) {

}

void B2Entity::UpdateChilderen(Entity * parent, double deltaTime)
{
	if (parent != NULL) {
		this->position = this->localPosition + parent->GetGlobalPosition();
		this->angle = this->localAngle + parent->GetGlobalAngle();
		this->scale = this->localScale * parent->GetGlobalScale();
		if (dynamic_cast<B2Entity*>(this) != NULL && this->body != nullptr) {
			// Check whether the parent is a b2entity as well and if it's body is already initialized
			if (dynamic_cast<B2Entity*>(parent) != NULL && dynamic_cast<B2Entity*>(parent)->body != nullptr) {
				body->SetTransform(b2Vec2(this->GetGlobalPosition().x * Window::p2m, this->GetGlobalPosition().y * Window::p2m), this->angle + dynamic_cast<B2Entity*>(parent)->GetGlobalAngle());
			}
			else {
				body->SetTransform(b2Vec2(this->GetGlobalPosition().x * Window::p2m, this->GetGlobalPosition().y * Window::p2m), this->angle);
			}
		}
	}
	else {
		this->position = this->localPosition;
		this->angle = this->localAngle;
		this->scale = this->localScale;
		if (dynamic_cast<B2Entity*>(this) != NULL && this->body != nullptr) {
			this->angle = body->GetAngle();
			body->SetTransform(b2Vec2(this->GetGlobalPosition().x * Window::p2m, this->GetGlobalPosition().y * Window::p2m), this->angle);
		}
	}
	for (int i = 0; i < entities.size(); i++) {
		entities[i]->Draw();
		entities[i]->Update(deltaTime);
		entities[i]->UpdateChilderen(this, deltaTime);
	}
}

void B2Entity::Draw() {
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

void B2Entity::CreateBody(int x, int y, int w, int h, bool dynamic, bool sensor) {
	this->localPosition = glm::vec3(x, y, 1.0f);
	width = w;
	height = h;
	// Step 1 defina a body
	b2BodyDef bodydef;
	bodydef.position.Set(x*Window::p2m, y*Window::p2m);
	bodydef.fixedRotation = true;
	if (dynamic) {
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
	shape.SetAsBox(w / 2 * Window::p2m, h / 2 * Window::p2m);
	// step 4 create fixture
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &shape;
	fixtureDef.density = 1.0;
	fixtureDef.friction = 0.3f;
	fixtureDef.restitution = 0.5f;
	// Set the collision filters
	//fixtureDef.filter.categoryBits = 0x0002;
	//fixtureDef.filter.maskBits = 0x0004;
	fixture = body->CreateFixture(&fixtureDef);
	if (sensor) {
		fixture->SetSensor(true);
	}
	fixture->SetUserData(this);
	for (int i = 0; i < 4; i++) {
		point[i] = ((b2PolygonShape*)body->GetFixtureList()->GetShape())->m_vertices[i];
		//std::cout << "point " << i << ": (" << point[i].x << ") (" << point[i].y << ")" << std::endl;
	}
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

void B2Entity::GiveTexture(Texture texture) {
	this->texture = texture;
}

glm::vec2 B2Entity::GetPositionInPixels()
{
	glm::vec2 pos;
	pos = glm::vec2(body->GetPosition().x * Window::m2p, body->GetPosition().y * Window::m2p);
	return pos;
}

float B2Entity::GetAngle()
{
	float angle;
	angle = body->GetAngle();
	return angle;
}

void B2Entity::AddContact(B2Entity* contact) {
	this->contacts.push_back(contact);
}

void B2Entity::RemoveContact(B2Entity* contact) {
	std::vector<B2Entity*>::iterator it = contacts.begin();
	while (it != contacts.end()) {
		if ((*it) == contact) {
			it = contacts.erase(it);
			return;
		}
		++it;
	}
	std::cout << "You tried to remove a contact, but that contact could not be found!" << std::endl;
}

void B2Entity::SetActive(bool active) {
	if (body != NULL) {
		body->SetActive(active);
	}
}

void B2Entity::Reset() {

}
