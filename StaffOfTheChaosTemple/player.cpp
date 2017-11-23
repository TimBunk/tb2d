#include "player.h"

Player::Player(Input* input, ResourceManager* rm, Camera * camera, Shader * shader, b2World * world) : B2Entity::B2Entity(camera, shader, world)
{
	this->input = input;
	this->rm = rm;
	staff = new Staff(world, rm, 50, 150, rm->GetTexture("staff"), rm->GetShader("defaultShader"), camera);
	this->AddChild(staff);
}

Player::~Player()
{
	delete staff;
}

void Player::Update(double deltaTime)
{
	b2Vec2 velocity = b2Vec2(0.0f, 0.0f);
	if (input->KeyDown(GLFW_KEY_W)) {
		velocity.y += 1.0f;
	}
	if (input->KeyDown(GLFW_KEY_S)) {
		velocity.y += -1.0f;
	}
	if (input->KeyDown(GLFW_KEY_A)) {
		velocity.x += -1.0f;
	}
	if (input->KeyDown(GLFW_KEY_D)) {
		velocity.x += 1.0f;
	}
	velocity.Normalize();
	velocity *= 10.0f;
	body->SetLinearVelocity(velocity);
	localPosition = this->GetPositionInPixels();
	// Rotate the player towards the mouse 
	glm::vec2 direction = input->GetMousePositionWorldSpace(camera) - localPosition;
	glm::normalize(direction);
	this->localAngle = std::atan2(direction.y, direction.x);

	staff->localAngle = (90.0f * M_PI / 180.0f);//(90.0f * M_PI / 180.0f);

	staff->localPosition.x = glm::cos(staff->localAngle + localAngle);
	staff->localPosition.y = glm::sin(staff->localAngle + localAngle);
	staff->localPosition = glm::normalize(staff->localPosition);
	staff->localPosition *= 200.0f;
}

void Player::CreateBody(int x, int y, int w, int h, bool dynamic, bool sensor)
{
	// Save the w and h for later use
	width = w;
	height = h;
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
	// the reason for dividing by 2 is because box2D draws from the center
	shape.SetAsBox(w / 2 * p2m, h / 2 * p2m);
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
	vertices[4] = point[1].x; vertices[5] = point[1].y; vertices[6] = 1.0f; vertices[7] = 0.0f;  // lower-right corner
	vertices[8] = point[2].x; vertices[9] = point[2].y; vertices[10] = 1.0f; vertices[11] = 1.0f;  // upper-right corner
	vertices[12] = point[3].x; vertices[13] = point[3].y; vertices[14] = 0.0f; vertices[15] = 1.0f;  // uper left corner

	glBufferData(GL_ARRAY_BUFFER, 16 * sizeof(GLfloat), &vertices[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

	// create the indices on the stack to make sure they won't get out of range
	unsigned int * indices;
	indices = new unsigned int[6];
	indices[0] = 0; indices[1] = 1; indices[2] = 3;
	indices[3] = 1; indices[4] = 2; indices[5] = 3;

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

	this->localPosition = glm::vec2(x, y);
	body->SetTransform(b2Vec2(x * p2m, y * p2m), 0.0f);
}
