#include "b2entity.h"

B2Entity::B2Entity(Camera* camera, Shader* shader, b2World* world) : Entity::Entity() {
	// Save all of the variables received from the constructor
	this->camera = camera;
	this->shader = shader;
	this->world = world;
	// Give all of the variables a value because it is bad to leave it not initialized
	fixture = nullptr;
	body = nullptr;
	VBO = 0;
	VAO = 0;
	EBO = 0;
	width = 0;
	height = 0;
}

B2Entity::~B2Entity() {
	// If the body was created make sure to delete everything as well
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

// This function is normally called by the parent
void B2Entity::UpdateChilderen(Entity * parent, double deltaTime)
{
	// Check if the parent does not equals NULL and set this's position/angle and scale
	if (parent != NULL) {
		this->position = this->localPosition + parent->GetGlobalPosition();
		this->angle = this->localAngle + parent->GetGlobalAngle();
		this->scale = this->localScale * parent->GetGlobalScale();
		// If the parent is a B2Entity as well makes sure to transform the position and angle as well by the body of the B2Entity
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
		// If the parent is null set the global position/angle/scale equal to the localPosition of this B2Entity
		this->position = this->localPosition;
		this->angle = this->localAngle;
		this->scale = this->localScale;
		// Check if the body of this B2Entity is initialized if so get the angle from the b2Body
		if (dynamic_cast<B2Entity*>(this) != NULL && this->body != nullptr) {
			this->angle = body->GetAngle();
			body->SetTransform(b2Vec2(this->GetGlobalPosition().x * Window::p2m, this->GetGlobalPosition().y * Window::p2m), this->angle);
		}
	}
	// Update and draw all of the childeren and their childeren
	for (int i = 0; i < entities.size(); i++) {
		entities[i]->Draw();
		entities[i]->Update(deltaTime);
		entities[i]->UpdateChilderen(this, deltaTime);
	}
}

void B2Entity::Draw() {
	// Use the shader and draw the texture
	shader->Use();
	shader->SetMatrix4("projection", camera->GetProjectionMatrix());
	shader->SetMatrix4("view", camera->GetViewMatrix());
	// Create a model matrix that gets the global position angle and scale of this B2Entity
	glm::mat4 model;
	model = glm::translate(model, this->GetGlobalPosition());
	model = glm::rotate(model, this->GetGlobalAngle(), glm::vec3(0.0f, 0.0f, 1.0f));
	// The reason I multiply with m2p is because the body's size is in meters but we want to draw it in pixels
	model = glm::scale(model, glm::vec3(Window::m2p * this->GetGlobalScale().x, Window::m2p * this->GetGlobalScale().y, 0.0f));
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
	// Save the x and y the localPosition
	this->localPosition = glm::vec3(x, y, 1.0f);
	// Save the w and h for later use
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
	fixture = body->CreateFixture(&fixtureDef);
	if (sensor) {
		fixture->SetSensor(true);
	}
	fixture->SetUserData(this);
	for (int i = 0; i < 4; i++) {
		point[i] = ((b2PolygonShape*)body->GetFixtureList()->GetShape())->m_vertices[i];
		//std::cout << "point " << i << ": (" << point[i].x << ") (" << point[i].y << ")" << std::endl;
	}

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	// create vertices on the heap to make sure they won't get out of range
	GLfloat* vertices;
	vertices = new GLfloat[16];
	// position
	vertices[0] = point[0].x; vertices[1] = point[0].y; vertices[2] = 0.0f; vertices[3] = 0.0f;  // lower-left corner
	vertices[4] = point[1].x; vertices[5] = point[1].y; vertices[6] = 1.0f; vertices[7]  = 0.0f;  // lower-right corner
	vertices[8] = point[2].x; vertices[9] = point[2].y; vertices[10] = 1.0f; vertices[11] = 1.0f;  // upper-right corner
	vertices[12] = point[3].x; vertices[13] = point[3].y; vertices[14] =  0.0f; vertices[15] =  1.0f;  // uper left corner

	glBufferData(GL_ARRAY_BUFFER, 16 * sizeof(GLfloat), &vertices[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

	// create the indices on the stack to make sure they won't get out of range
	unsigned int * indices;
	indices = new unsigned int[6];
	indices[0] = 0; indices[1] = 1; indices[2] = 3;
	indices[3] = 1; indices[4] =  2; indices[5] = 3;

	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

	// set the vertices
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid*)(2 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	glBindVertexArray(0);

	// delete the vertices and indices created on the heap
	delete vertices;
	delete indices;
}

void B2Entity::GiveTexture(Texture texture) {
	this->texture = texture;
}

glm::vec2 B2Entity::GetPositionInPixels()
{
	// Get the position directly from the box2d body and it will automatically be converted to pixels for you
	glm::vec2 pos;
	pos = glm::vec2(body->GetPosition().x * Window::m2p, body->GetPosition().y * Window::m2p);
	return pos;
}

float B2Entity::GetAngle()
{
	// Get the angle in radians from the body
	float angle;
	angle = body->GetAngle();
	return angle;
}

void B2Entity::AddContact(B2Entity* contact) {
	this->contacts.push_back(contact);
}

void B2Entity::RemoveContact(B2Entity* contact) {
	// Iterate through all of the contacts and find the right contact to delete
	std::vector<B2Entity*>::iterator it = contacts.begin();
	while (it != contacts.end()) {
		if ((*it) == contact) {
			it = contacts.erase(it);
			return;
		}
		++it;
	}
	// This cout line should never be called if it is something might be very wrong
	std::cout << "You tried to remove a contact, but that contact could not be found!" << std::endl;
}

void B2Entity::SetActive(bool active) {
	// Set active or deactive but only if the body is initialized
	if (body != NULL) {
		body->SetActive(active);
	}
}

void B2Entity::Reset() {
	// This is empty it's up to the user's to deceide what it does
}
