#include "necromancerOrc.h"

NecromancerOrc::NecromancerOrc(float spawnCooldown, Player* player, float lineOfSight, ResourceManager* rm, Camera* camera, Shader* shader, b2World* world) : Enemy::Enemy(player, lineOfSight, rm, camera, shader, world) {
	// Stats of the necromancerOrc
	damage = 0;
	speed = 0.0f;
	attackSpeed = 0.0f;
	health = 2;
	currentHealth = health;
	// Initialize all of the other variables
	this->spawnCooldown = spawnCooldown;
	currentCooldown = 0.0f;
	babyOrcsHolder = new Entity();
}

NecromancerOrc::~NecromancerOrc() {
	// Iterate through all of the babyOrcs and delete them
	std::vector<BabyOrc*>::iterator it = babyOrcs.begin();
	while (it != babyOrcs.end()) {
		babyOrcsHolder->RemoveChild((*it));
		delete (*it);
		it = babyOrcs.erase(it);
	}
	delete babyOrcsHolder;
}

void NecromancerOrc::Update(double deltaTime) {
	if (IsAlive()) {
		// Look for the player and if he is in range spawn a babyorc
		if (LookForPlayer()) {
			// Check where the player is and rotate towards him
			glm::vec3 anglePlayerEnemy = glm::normalize(player->localPosition - this->localPosition) * 15.0f;
			if (IsTextureFlipped() && anglePlayerEnemy.x < 0.0f) {
				this->FlipTexture();
			}
			else if (!IsTextureFlipped() && anglePlayerEnemy.x > 0.0f) {
				this->FlipTexture();
			}
			if (currentCooldown <= 0.0f && babyOrcs.size() < 4) {
				BabyOrc* bo;
				bo = new BabyOrc(this->player, this->lineOfSight, this->rm, this->camera, this->rm->GetShader("person"), this->world);
				bo->CreateBody(this->localPosition.x + anglePlayerEnemy.x, this->localPosition.y + anglePlayerEnemy.y, 50, 50);
				bo->GiveTexture(this->rm->GetTexture("babyOrc"));
				babyOrcs.push_back(bo);
				babyOrcsHolder->AddChild(bo);
				currentCooldown = spawnCooldown;
			}
			else {
				currentCooldown -= deltaTime;
			}
		}
	}
	// Update the babyOrcs
	std::vector<BabyOrc*>::iterator it = babyOrcs.begin();
	while (it != babyOrcs.end()) {
		if (!(*it)->IsAlive()) {
			babyOrcsHolder->RemoveChild((*it));
			delete (*it);
			it = babyOrcs.erase(it);
		}
		else {
			++it;
		}
	}
	babyOrcsHolder->UpdateChilderen(babyOrcsHolder, deltaTime);
	// Check if the person got damaged
	if (damaged && timerDamaged < cooldownDamaged) {
		timerDamaged += deltaTime;
	}
	else {
		timerDamaged = 0.0f;
		damaged = false;
	}
}

void NecromancerOrc::TakeDamage(int damage) {
	if (currentHealth - damage > 0) {
		currentHealth -= damage;
		damaged = true;
	}
	else {
		currentHealth = 0;
		this->Destroy();
		if (item != nullptr) {
			item->Reset();
		}
	}
}

void NecromancerOrc::Reset() {
	// Set all of the variables back it's origal value
	body->SetTransform(b2Vec2(spawnPosition.x * Window::p2m, spawnPosition.y * Window::p2m), 0.0f);
	playerLastLocation = spawnPosition;
	if (!IsAlive()) {
		alive = true;
		currentHealth = health;
		SetActive(true);
		if (item != nullptr) {
			item->Destroy();
		}
	}
	currentHealth = health;
	std::vector<BabyOrc*>::iterator it = babyOrcs.begin();
	while (it != babyOrcs.end()) {
		babyOrcsHolder->RemoveChild((*it));
		delete (*it);
		it = babyOrcs.erase(it);
	}
}

void NecromancerOrc::CreateBody(int x, int y, int w, int h) {
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
	bodydef.type = b2_staticBody;

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

void NecromancerOrc::SetActive(bool active) {
	if (body != NULL) {
		if (alive || !active) {
			if (alive) {
				currentHealth = health;
			}
			body->SetAwake(active);
			body->SetActive(active);
			body->SetTransform(b2Vec2(spawnPosition.x * Window::p2m, spawnPosition.y * Window::p2m), 0.0f);
			playerLastLocation = spawnPosition;
			std::vector<BabyOrc*>::iterator it = babyOrcs.begin();
			while (it != babyOrcs.end()) {
				babyOrcsHolder->RemoveChild((*it));
				delete (*it);
				it = babyOrcs.erase(it);
			}
		}
	}
}
