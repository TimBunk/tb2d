#include "b2entity.h"

B2Entity::B2Entity(Camera* camera, Shader* shader, b2World* world) : Entity::Entity() {
	// Save all of the variables received from the constructor
	this->camera = camera;
	this->shader = shader;
	this->world = world;
	// Give all of the variables a value because it is bad to leave it not initialized
	fixture = nullptr;
	body = nullptr;
	texture = nullptr;
	VBO = 0;
	VAO = 0;
	EBO = 0;
	width = 0;
	height = 0;
}

B2Entity::~B2Entity() {
	// If the body was created make sure to delete everything as well
	if (body != nullptr) {
		body->DestroyFixture(fixture);
		world->DestroyBody(body);
		glDeleteVertexArrays(1, &VAO);
		glDeleteBuffers(1, &VBO);
		glDeleteBuffers(1, &EBO);
	}
}

void B2Entity::Update(double deltaTime) {
	body->SetAwake(true);
	body->SetActive(true);
}

// This function is normally called by the parent
void B2Entity::UpdateChilderen(Entity * parent, double deltaTime)
{
	// Check if the parent does not equals NULL and set this's position/angle and scale
	if (parent != NULL) {
		model = parent->GetModelMatrix();
		model = glm::translate(model, glm::vec3(localPosition.x, localPosition.y, 0.0f));
		model = glm::rotate(model, localAngle, glm::vec3(0.0f, 0.0f, 1.0f));
		// The third row is the position of the 
		this->position = model[3];
		// The first two values in the mat4 can be used to get the z-rotation according to: https://stackoverflow.com/questions/39251412/get-the-angle-from-a-rotated-matrix-using-glm
		this->angle = glm::atan(model[0][1], model[0][0]);
	}
	else {
		// If the parent is null set the global position/angle/scale equal to the localPosition of this B2Entity
		this->position = this->localPosition;
		this->angle = this->localAngle;
		model = glm::mat4();
		model = glm::translate(model, glm::vec3(position.x, position.y, 0.0f));
		model = glm::rotate(model, angle, glm::vec3(0.0f, 0.0f, 1.0f));
	}
	// If the body is intialized update the position and angle of the body
	if (this->body != nullptr) {
		body->SetTransform(b2Vec2(this->position.x * p2m, this->position.y * p2m), this->angle);
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
	if (body != nullptr && texture != nullptr) {
		shader->Use();
		shader->SetMatrix4("projection", camera->GetProjectionMatrix());
		shader->SetMatrix4("view", camera->GetViewMatrix());
		glm::mat4 _model;
		_model = glm::translate(_model, glm::vec3(GetGlobalPosition().x, GetGlobalPosition().y, 0.0f));
		_model = glm::rotate(_model, GetGlobalAngle(), glm::vec3(0.0f, 0.0f, 1.0f));
		_model = glm::scale(_model, glm::vec3(m2p, m2p, 1.0f));
		shader->SetMatrix4("model", _model);
		glActiveTexture(GL_TEXTURE0 + texture->GetId());
		shader->SetInt("ourTexture", texture->GetId());
		glBindTexture(GL_TEXTURE_2D, texture->GetId());
		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glActiveTexture(GL_TEXTURE0);
		glBindVertexArray(0);
	}
}

void B2Entity::CreateBody(int x, int y, int w, int h, glm::vec2 pivot, bool dynamic, bool sensor, bool fixedRotation) {
	// If the body was created make sure to delete everything as well
	if (body != nullptr) {
		body->DestroyFixture(fixture);
		world->DestroyBody(body);
		glDeleteVertexArrays(1, &VAO);
		glDeleteBuffers(1, &VBO);
		glDeleteBuffers(1, &EBO);
	}
	// Save the w and h for later use
	width = w;
	height = h;
	// Step 1 defina a body
	b2BodyDef bodydef;
	bodydef.position.Set(0.0f, 0.0f);
	if (fixedRotation) {
		bodydef.fixedRotation = true;
	}
	else {
		bodydef.fixedRotation = false;
	}
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
	// pivot has to go times -1 because box2d sets the pivot point the otherway around then I want it
	pivot *= -1;
	// the reason for dividing by 2 is because box2D draws from the center
	shape.SetAsBox(w / 2 * p2m, h / 2 * p2m, b2Vec2(pivot.x * p2m, pivot.y * p2m), 0.0f);
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
	body->SetActive(true);
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
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	glBindVertexArray(0);

	// delete the vertices and indices created on the heap
	delete vertices;
	delete indices;

	this->localPosition = glm::vec2(x, y);
	body->SetTransform(b2Vec2(x * p2m, y * p2m), 0.0f);
}

void B2Entity::GiveTexture(Texture* texture) {
	this->texture = texture;
}

glm::vec2 B2Entity::ApplyVelocityB2body(glm::vec2 velocity)
{
	// Set the velocity to a b2Vec2 and apply it
	b2Vec2 vel = b2Vec2(velocity.x, velocity.y);
	body->SetLinearVelocity(vel);
	// Receive the new position and return it in world space
	glm::vec2 pos = glm::vec2(body->GetPosition().x * m2p, body->GetPosition().y * m2p);
	return pos;
}

glm::vec2 B2Entity::GetPositionInPixelsB2body()
{
	// Get the position directly from the box2d body and it will automatically be converted to pixels for you
	glm::vec2 pos;
	pos = glm::vec2(body->GetPosition().x * m2p, body->GetPosition().y * m2p);
	return pos;
}

float B2Entity::GetAngleB2body()
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