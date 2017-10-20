#include "enemy.h"

Enemy::Enemy(Player* player, Camera* camera, Shader* shader, Shader* lineRenderer) : Person::Person(camera, shader) {
	this->player = player;
	raycast = new RayCastCallBack();
	raycast->CreateLine(500.0f, 25.0f, camera, lineRenderer, glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
}

Enemy::~Enemy() {
	delete raycast;
}

void Enemy::Update(float deltaTime) {
	/*b2RayCastOutput output;
	b2RayCastInput input;
	input.p1 = this->GetPositionInPixels().x;
	input.p2 = this->GetPositionInPixels().y;
	input.maxFraction = 1;
	if (fixture->RayCast(&output, input, 1)) {

	}
	b2RayCastCallback callBack;*/
	this->localPosition = glm::vec3(this->GetPositionInPixels().x, this->GetPositionInPixels().y, 1.0f);
	world->RayCast(raycast, b2Vec2(0.0f, 0.0f), b2Vec2(800.0f * Window::p2m, 600.0f * Window::p2m));
	glm::vec2 angle = this->localPosition - player->localPosition;
	angle = glm::normalize(angle);
	angle *= (((float)M_PI) * 180.0f);
	float newAngle = glm::atan(angle.y, angle.x);
	//std::cout << "Angle in radius between player and enemy = " << newAngle << std::endl;
	raycast->Draw(glm::vec2(this->localPosition.x, this->localPosition.y), newAngle);
	RaycastOutput ro = raycast->GetOutput();
	if (static_cast<B2Entity*>(ro.fixture->GetUserData()) == NULL) { return; }
	B2Entity* b2entity = static_cast<B2Entity*>(ro.fixture->GetUserData());
	if (dynamic_cast<Player*>(b2entity) != NULL) {
		//std::cout << "PLAYER HAS BEEN HIT" << std::endl;
	}

}

void Enemy::CreateBody(int x, int y, int w, int h, b2World* world) {
	// Create a pointer to the world the body will be connected to
	this->localPosition = glm::vec3(x, y, 1.0f);
	this->world = world;
	// Step 1 defina a body
	b2BodyDef bodydef;
	bodydef.position.Set(x*Window::p2m, y*Window::p2m);
	bodydef.fixedRotation = true;
	bodydef.type = b2_dynamicBody;

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
