#include "b2entity.h"

B2Entity::B2Entity(Camera* camera, b2World* world) : Entity::Entity() {
	// Save all of the variables received from the constructor
	this->camera = camera;
	this->world = world;

	shader = ResourceManager::GetShader("defaultShader");
	dr = nullptr;
	// Give all of the variables a value because it is bad to leave it not initialized
	fixture = nullptr;
	body = nullptr;
	texture = nullptr;
	shape = Shape::box;
	width = 0;
	height = 0;
}

B2Entity::~B2Entity() {
	// If the body was created make sure to delete everything as well
	if (body != nullptr) {
		body->DestroyFixture(fixture);
		world->DestroyBody(body);
	}
	if (dr != nullptr) {
		delete dr;
	}
}

void B2Entity::Update(double deltaTime) {
	
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
	if (body != nullptr) {
		if (dr != nullptr) {
			dr->Render(model, 10.0f);
		}
		if (texture != nullptr) {
			shader->Use();
			glm::mat4 _model = glm::scale(model, glm::vec3(width, height, 0.0f));
			shader->SetMatrix4("model", _model);
			shader->SetMatrix4("projection", camera->GetProjectionMatrix());
			shader->SetMatrix4("view", camera->GetViewMatrix());

			glActiveTexture(GL_TEXTURE0);
			glBindVertexArray(quadData.VAO);
			glBindTexture(GL_TEXTURE_2D, texture->GetId());

			glDrawArrays(GL_TRIANGLES, 0, 6);
			// Set the currently binded VAO and texture to 0
			glBindVertexArray(0);
			glBindTexture(GL_TEXTURE_2D, 0);
		}
	}
}

void B2Entity::CreateBodyBox(int x, int y, int w, int h, glm::vec2 pivot, bool dynamic, bool sensor, bool fixedRotation) {
	shape = Shape::box;
	// If the body was created make sure to delete everything as well
	if (body != nullptr) {
		body->DestroyFixture(fixture);
		world->DestroyBody(body);
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
	shape.SetAsBox(w / 2 * p2m, h / 2 * p2m, b2Vec2(pivot.x * width * p2m, pivot.y * height * p2m), 0.0f);
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

	this->localPosition = glm::vec2(x, y);
	body->SetTransform(b2Vec2(x * p2m, y * p2m), 0.0f);

	quadData = ResourceManager::GetQuad(pivot);
}

void B2Entity::CreateBodyCircle(int x, int y, int radius, bool dynamic, bool sensor, bool fixedRotation)
{
	shape = Shape::circle;
	// If the body was created make sure to delete everything as well
	if (body != nullptr) {
		body->DestroyFixture(fixture);
		world->DestroyBody(body);
	}
	// Save the w and h for later use
	width = radius * 2.0f;
	height = radius * 2.0f;
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
	b2CircleShape shape;
	shape.m_radius = radius * p2m;
	shape.m_type = shape.e_circle;
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

	this->localPosition = glm::vec2(x, y);
	body->SetTransform(b2Vec2(x * p2m, y * p2m), 0.0f);

	quadData = ResourceManager::GetQuad(glm::vec2(0,0));
}

void B2Entity::EnableDebugRendering(glm::vec3 color)
{
	if (body == nullptr) {
		std::cout << "You can not enable debug rendering if you have not yet created a body!" << std::endl;
		return;
	}
	if (dr != nullptr) {
		delete dr;
	}
	dr = new DebugRenderer(camera, color);
	switch (shape)
	{
	case box:
		GLfloat* vertices;
		vertices = new GLfloat[8];
		vertices[0] = -width/2; vertices[1] = -height/2; // lower-left corner
		vertices[2] = width/2; vertices[3] = -height/2;  // lower-right corner
		vertices[4] = width/2; vertices[5] = height/2; // upper-right corner
		vertices[6] = -width/2; vertices[7] = height/2;  // uper left corner
		dr->DrawBox(vertices);
		delete vertices;
		break;
	case circle:
		dr->DrawCircle(glm::vec2(0, 0), width / 2);
		break;
	}
}

void B2Entity::SetTexture(Texture* texture) {
	this->texture = texture;
}

void B2Entity::SetShader(Shader * shader)
{
	this->shader = shader;
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

bool B2Entity::Contact(B2Entity * contact)
{
	int count = contacts.size();
	for (int i = 0; i < count; i++) {
		if (contacts[i] == contact) {
			return true;
		}
	}
	return false;
}

std::vector<B2Entity*> B2Entity::GetAllContacts()
{
	return contacts;
}

void B2Entity::SetActive(bool active) {
	// Set active or deactive but only if the body is initialized
	if (body != NULL) {
		body->SetActive(active);
	}
}