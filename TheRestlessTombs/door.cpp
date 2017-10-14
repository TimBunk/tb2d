#include "door.h"

Door::Door(Camera* camera, Shader* shader, int roomNumber) : B2Entity::B2Entity(camera, shader) {
	this->roomNumber = roomNumber;
}

Door::~Door() {

}

void Door::Update(float deltaTime) {
	this->localPosition = glm::vec3(this->GetPositionInPixels(), 9.0f);
	for (int i=0;i<contacts.size();i++) {
		if (dynamic_cast<Player*>(contacts[i]) != 0) {
			glm::vec2 playerPosition = dynamic_cast<Player*>(contacts[i])->GetGlobalPosition();
			switch (direction) {
			case north:
				if (this->GetGlobalPosition().y > playerPosition.y) {
					dynamic_cast<Player*>(contacts[i])->SetRoom(roomNumber);
				}
				break;
			case east:
				if (this->GetGlobalPosition().x < playerPosition.x) {
					dynamic_cast<Player*>(contacts[i])->SetRoom(roomNumber);
				}
				break;
			case south:
				if (this->GetGlobalPosition().y < playerPosition.y) {
					dynamic_cast<Player*>(contacts[i])->SetRoom(roomNumber);
				}
				break;
			case west:
				if (this->GetGlobalPosition().x > playerPosition.x) {
					dynamic_cast<Player*>(contacts[i])->SetRoom(roomNumber);
				}
				break;
			}
			return;
		}
	}
}

void Door::CreateBody(int x, int y, Direction direction, float width, b2World* world) {
	this->direction = direction;
	// Create a pointer to the world the body will be connected to
	this->world = world;
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
	if (direction == Direction::north || direction == Direction::south) {
		shape.SetAsBox(width / 2 * Window::p2m, 50 / 2 * Window::p2m);
	}
	else {
		shape.SetAsBox(50 / 2 * Window::p2m, width / 2 * Window::p2m);
	}
	// step 4 create fixture
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &shape;
	fixtureDef.density = 1.0;
	fixtureDef.friction = 0.3f;
	fixtureDef.restitution = 0.5f;
	// Set the collision filters
	fixture = body->CreateFixture(&fixtureDef);
	fixture->SetUserData(this);
	// Sensor means collision is detected but nothing is done with it
	fixture->SetSensor(true);
	for (int i = 0; i < 4; i++) {
		point[i] = ((b2PolygonShape*)body->GetFixtureList()->GetShape())->m_vertices[i];
		//std::cout << "point " << i << ": (" << point[i].x << ") (" << point[i].y << ")" << std::endl;
	}
	// FOR EVERY 100 pixels repeat the texture
	float multiply = ((float)width)/100.0f;
	float vertices[16];
	if (direction == Direction::north || direction == Direction::south) {
			// position
		vertices[0] = point[0].x; vertices[1] = point[0].y; vertices[2] = 0.0f; vertices[3] = 0.0f;  // lower-left corner
		vertices[4] = point[1].x; vertices[5] = point[1].y; vertices[6] = 1.0f * multiply; vertices[7] = 0.0f;  // lower-right corner
		vertices[8] = point[2].x; vertices[9] = point[2].y; vertices[10] = 1.0f * multiply; vertices[11] = 1.0f;  // upper-right corner
		vertices[12] = point[3].x; vertices[13] =  point[3].y; vertices[14] = 0.0f; vertices[15] = 1.0f;  // uper left corner
	}
	else {
		vertices[0] = point[0].x; vertices[1] = point[0].y; vertices[2] = 0.0f; vertices[3] = 0.0f;  // lower-left corner
		vertices[4] = point[1].x; vertices[5] = point[1].y; vertices[6] = 1.0f; vertices[7] = 0.0f;  // lower-right corner
		vertices[8] = point[2].x; vertices[9] = point[2].y; vertices[10] = 1.0f; vertices[11] = 1.0f * multiply;  // upper-right corner
		vertices[12] = point[3].x; vertices[13] =  point[3].y; vertices[14] = 0.0f; vertices[15] = 1.0f * multiply;  // uper left corner
	}

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
