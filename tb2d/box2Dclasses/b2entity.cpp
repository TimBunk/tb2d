#include "b2entity.h"

B2Entity::B2Entity(int width, int height, unsigned int textureID, b2World* world) : Sprite::Sprite(width, height, textureID) {
	// Save all of the variables received from the constructor
	this->world = world;

	// Give all of the variables a value because it is bad to leave it not initialized
	fixture = nullptr;
	body = nullptr;
	shape = Shape::box;
	colliderWidth = 0;
	colliderHeight = 0;
	debugColor = glm::vec3(1, 1, 1);
	colliderPivot = glm::vec2(-0.5f, 0.0f);
	filter = 0;
}

B2Entity::~B2Entity() {
	// If the body was created make sure to delete everything as well
	if (body != nullptr) {
		body->DestroyFixture(fixture);
		world->DestroyBody(body);
	}
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
	for (int i = 0; i < childeren.size(); i++) {
		childeren[i]->Draw();
		childeren[i]->Update(deltaTime);
		childeren[i]->UpdateChilderen(this, deltaTime);
	}
}

void B2Entity::DrawChilderen(Entity * parent)
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
	for (int i = 0; i < childeren.size(); i++) {
		childeren[i]->Draw();
		childeren[i]->DrawChilderen(this);
	}
}

void B2Entity::Draw() {
	renderer->Submit(this);
	if (body != nullptr) {
		DebugRenderer::Submit(this);
	}
}

void B2Entity::CreateBoxCollider(int w, int h, glm::vec2 pivot, bool dynamic, bool sensor) {
	/*if (pivot.x != 0.0f) {
		std::cout << "The pivot = " << pivot.x << std::endl;
	}*/
	colliderPivot = pivot;
	shape = Shape::box;
	// If the body was created make sure to delete everything as well
	if (body != nullptr) {
		body->DestroyFixture(fixture);
		world->DestroyBody(body);
	}
	// Save the w and h for later use
	colliderWidth = w;
	colliderHeight = h;
	// Step 1 defina a body
	b2BodyDef bodydef;
	bodydef.position.Set(0.0f, 0.0f);
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
	// pivot has to go times -1 because box2d sets the pivot point the otherway around then I want it
	pivot *= -1;
	// the reason for dividing by 2 is because box2D draws from the center
	shape.SetAsBox(w / 2 * p2m, h / 2 * p2m, b2Vec2((pivot.x * width * p2m) * -1, (pivot.y * height * p2m) * -1), 0.0f);
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
}

void B2Entity::CreateCircleCollider(int radius, bool dynamic, bool sensor)
{
	shape = Shape::circle;
	// If the body was created make sure to delete everything as well
	if (body != nullptr) {
		body->DestroyFixture(fixture);
		world->DestroyBody(body);
	}
	// Save the w and h for later use
	colliderWidth = radius;
	colliderHeight = radius;
	// Step 1 defina a body
	b2BodyDef bodydef;
	bodydef.position.Set(0.0f, 0.0f);
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
}

void B2Entity::SetDebugColor(glm::vec3 color)
{
	debugColor = color;
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

int B2Entity::GetColliderWidth()
{
	return colliderWidth;
}

int B2Entity::GetColliderHeight()
{
	return colliderHeight;
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