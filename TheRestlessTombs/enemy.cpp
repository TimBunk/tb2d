#include "enemy.h"

Enemy::Enemy(Player* player, float lineOfSight, ResourceManager* rm, Camera* camera, Shader* shader, b2World* world) : Person::Person(rm, camera, shader, world) {
	// Intialize all of the variables with a value
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
	// The item will be a child of the enemy also it will be destroyed but whenever the player dies it will be reseted again
	this->item = item;
	this->AddChild(item);
	item->Destroy();
}

bool Enemy::LookForPlayer() {
	// Get the position in pixels from the b2Body and make that the localPosition
	this->localPosition = glm::vec3(this->GetPositionInPixels().x, this->GetPositionInPixels().y, 1.0f);
	b2Vec2 vel = b2Vec2(0.0f, 0.0f);
	// If the raycast reached the player move towards it
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
	// Draw raycast
	/*glm::vec2 angle = this->localPosition - player->localPosition;
	angle = glm::normalize(angle);
	angle *= (((float)M_PI) * 180.0f);
	float newAngle = glm::atan(angle.y, angle.x);
	raycast->Draw(glm::vec2(this->localPosition.x, this->localPosition.y), newAngle);*/

	// Check if the player is in range
	distancePlayer = glm::distance(this->localPosition, player->localPosition);
	if (distancePlayer < lineOfSight) {
		// Set the raycast
		world->RayCast(raycast, b2Vec2(this->localPosition.x * Window::p2m, this->localPosition.y * Window::p2m), b2Vec2(player->localPosition.x * Window::p2m, player->localPosition.y * Window::p2m));
		RaycastOutput ro = raycast->GetOutput();
		if (static_cast<B2Entity*>(ro.fixture->GetUserData()) == NULL) { return false; }
		B2Entity* b2entity = static_cast<B2Entity*>(ro.fixture->GetUserData());
		// Check if the hitted b2Entity is a player if so return true
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

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	// create vertices on the stack to make sure they won't get out of range
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

	// delete the vertices and indices created on the stack
	delete vertices;
	delete indices;
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
