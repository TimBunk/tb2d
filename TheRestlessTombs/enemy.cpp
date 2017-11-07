#include "enemy.h"

Enemy::Enemy(Player* player, float lineOfSight, ResourceManager* rm, Camera* camera, Shader* shader, b2World* world) : Person::Person(rm, camera, shader, world) {
	this->player = player;
	this->lineOfSight = lineOfSight;
	raycast = new RayCastCallBack(this);
	raycast->CreateLine(lineOfSight, 25.0f, camera, this->rm->GetShader("debugRenderer"), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
	playerLastLocation = this->localPosition;
	distancePlayer = 10000.0f;
	minimalRange = 0.0f;
	item = nullptr;
}

Enemy::~Enemy() {
	delete raycast;
}

void Enemy::GiveItem(Item* item) {
	this->item = item;
	this->AddChild(item);
	item->Destroy();
}

bool Enemy::LookForPlayer() {
	this->localPosition = glm::vec3(this->GetPositionInPixels().x, this->GetPositionInPixels().y, 1.0f);
	b2Vec2 vel = b2Vec2(0.0f, 0.0f);
	if (this->ShootRaycast()) {
		vel = b2Vec2(player->localPosition.x - this->localPosition.x, player->localPosition.y - this->localPosition.y);
		vel.Normalize();
		vel *= speed;
		body->SetLinearVelocity(vel);
		if (IsTextureFlipped() && vel.x < 0.0f) {
			FlipTexture();
		}
		else if (!IsTextureFlipped() && vel.x > 0.0f) {
			FlipTexture();
		}
		return true;
	}
	else if (glm::distance(this->localPosition, playerLastLocation) > minimalRange) {
		vel = b2Vec2(playerLastLocation.x - this->localPosition.x, playerLastLocation.y - this->localPosition.y);
		vel.Normalize();
		vel *= speed;
		body->SetLinearVelocity(vel);
		return false;
	}
	body->SetLinearVelocity(vel);
	return false;
}

bool Enemy::ShootRaycast() {
	// DRAW
	glm::vec2 angle = this->localPosition - player->localPosition;
	angle = glm::normalize(angle);
	angle *= (((float)M_PI) * 180.0f);
	float newAngle = glm::atan(angle.y, angle.x);
	// Raycast drawing
	//raycast->Draw(glm::vec2(this->localPosition.x, this->localPosition.y), newAngle);

	// UPDATE
	distancePlayer = glm::distance(this->localPosition, player->localPosition);
	if (distancePlayer < lineOfSight) {
		world->RayCast(raycast, b2Vec2(this->localPosition.x * Window::p2m, this->localPosition.y * Window::p2m), b2Vec2(player->localPosition.x * Window::p2m, player->localPosition.y * Window::p2m));
		RaycastOutput ro = raycast->GetOutput();
		if (static_cast<B2Entity*>(ro.fixture->GetUserData()) == NULL) { return false; }
		B2Entity* b2entity = static_cast<B2Entity*>(ro.fixture->GetUserData());
		if (dynamic_cast<Player*>(b2entity) != NULL) {
			playerLastLocation = player->localPosition;
			return true;
		}
	}
	return false;
}

void Enemy::CreateBody(int x, int y, int w, int h) {
	this->localPosition = glm::vec3(x, y, 1.0f);
	width = w;
	height = h;
	spawnPosition = this->localPosition;
	playerLastLocation = this->localPosition;
	minimalRange = glm::length(glm::vec2(w, h));
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


void Enemy::SetActive(bool active) {
	if (body != NULL) {
		if (alive || !active) {
			if (alive) {
				currentHealth = health;
			}
			body->SetAwake(active);
			body->SetActive(active);
		}
	}
}
