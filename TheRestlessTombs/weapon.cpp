#include "weapon.h"
#include "player.h"
#include "enemy.h"

Weapon::Weapon(float damage, float swingAngle, float attackDuration, bool belongsToPlayer, Camera* camera, Shader* shader, b2World* world) : B2Entity::B2Entity(camera, shader, world) {
	this->damage = damage;
	this->swingAngle = swingAngle;
	currentSwingAngle = 0.0f;
	this->attackDuration = attackDuration;
	this->belongsToPlayer = belongsToPlayer;
	rotation = 0.0f;
	angle2 = glm::vec2(0.0f);
	timer = 0.0f;
	attacking = false;
	hit = false;
	flippedBody = true;
	w = 0;
	h = 0;
	dr = new DebugRenderer(camera->GetProjectionMatrix(), glm::vec4(1.0f));
}

Weapon::~Weapon() {
	delete dr;
}

void Weapon::Update(float deltaTime) {
	body->SetAwake(true);
	this->localAngle = rotation + currentSwingAngle;
	if (attacking && timer <= attackDuration) {
		timer += deltaTime;
		currentSwingAngle = timer/attackDuration * swingAngle;
		if (flippedBody) {
			currentSwingAngle = (currentSwingAngle * ((float)M_PI) / 180.0f) * -1;
		}
		else {
			currentSwingAngle = currentSwingAngle * ((float)M_PI) / 180.0f;
		}
		// If the player has lag the swingAngle might go to far and this if statement limits the angle
		if (currentSwingAngle > swingAngle) {
			currentSwingAngle = swingAngle;
		}
		for (unsigned int i=0;i<contacts.size();i++) {
			if (dynamic_cast<Player*>(contacts[i]) != 0) {
				if (!hit && !belongsToPlayer) {
					hit = true;
					dynamic_cast<Player*>(contacts[i])->TakeDamage(damage);
					break;
				}
			}
			else if (dynamic_cast<Enemy*>(contacts[i]) != 0) {
				if (!hit && belongsToPlayer) {
					hit = true;
					dynamic_cast<Enemy*>(contacts[i])->TakeDamage(damage);
					break;
				}
			}
			else if (dynamic_cast<Crate*>(contacts[i]) != 0 || dynamic_cast<LootChest*>(contacts[i]) != 0) {
				if (!hit && belongsToPlayer) {
					hit = true;
					dynamic_cast<Destructable*>(contacts[i])->Destroy();
					break;
				}
			}
			else if (dynamic_cast<Shop*>(contacts[i]) != 0) {
				if (!hit && belongsToPlayer) {
					hit = true;
					dynamic_cast<Shop*>(contacts[i])->_SetActive(true);
					break;
				}
			}
		}
	}
	else {
		timer = 0.0f;
		attacking = false;
		currentSwingAngle = 0.0f;
	}

	glm::mat4 model;
	model = glm::translate(model, glm::vec3(GetPositionInPixels(), 0.0f));
	model = glm::rotate(model, GetAngle(), glm::vec3(0.0f, 0.0f, 1.0f));
	model = glm::scale(model, glm::vec3(Window::m2p, Window::m2p, 0.0f));
	dr->Render(camera->GetViewMatrix(), model, 3.0f);
}

void Weapon::Draw() {
	shader->Use();
	shader->SetMatrix4("projection", camera->GetProjectionMatrix());
	shader->SetMatrix4("view", camera->GetViewMatrix());
	glm::mat4 model;
	model = glm::translate(model, glm::vec3(this->GetGlobalPosition().x, this->GetGlobalPosition().y, this->GetGlobalPosition().z));
	rotation = (float)atan2(angle2.y, angle2.x);
	model = glm::rotate(model, this->GetAngle(), glm::vec3(0.0f, 0.0f, 1.0f));
	model = glm::scale(model, glm::vec3(Window::m2p, Window::m2p, 1.0f));
	shader->SetMatrix4("model", model);
	glActiveTexture(GL_TEXTURE0 + texture.id);
	shader->SetInt("ourTexture", texture.id);
	glBindTexture(GL_TEXTURE_2D, texture.id);
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	glActiveTexture(GL_TEXTURE0);
	glBindVertexArray(0);
}

void Weapon::CreateBody(int x, int y, int w, int h) {
	// Create a pointer to the world the body will be connected to
	this->w = w;
	this->h = h;
	this->localPosition = glm::vec3(x, y, 1.0f);
	// Step 1 defina a body
	b2BodyDef bodydef;
	bodydef.position.Set(x*Window::p2m, y*Window::p2m);
	bodydef.fixedRotation = true;
	bodydef.type = b2_dynamicBody;

	// Step 2 create a body
	body = this->world->CreateBody(&bodydef);

	// Step 3 create shape
	b2PolygonShape shape;
	// the reason for dividing by 2 is because box2D draws from the center
	shape.SetAsBox(w / 2 * Window::p2m, h / 2 * Window::p2m, b2Vec2(0.0f, (w / 2 * Window::p2m) * -1), 0.0f);
	// step 4 create fixture
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &shape;
	fixtureDef.density = 1.0;
	fixtureDef.friction = 0.3f;
	fixtureDef.restitution = 0.5f;
	// Set the collision filters
	fixture = body->CreateFixture(&fixtureDef);
	fixture->SetSensor(true);
	fixture->SetUserData(this);
	for (int i = 0; i < 4; i++) {
		point[i] = ((b2PolygonShape*)body->GetFixtureList()->GetShape())->m_vertices[i];
		//std::cout << "point " << i << ": (" << point[i].x << ") (" << point[i].y << ")" << std::endl;
	}
	dr->DrawBox(point);
	dr->Init();
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
	FlipBody();
}

void Weapon::FlipBody() {
	float vertices[16];
	// Delete all the old data and replace it with the new data
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
	body->DestroyFixture(fixture);
	world->DestroyBody(body);

	b2BodyDef bodydef;
	bodydef.position.Set(0.0f * Window::p2m, 0.0f * Window::p2m);
	bodydef.fixedRotation = true;
	bodydef.type = b2_dynamicBody;

	// Step 2 create a body
	body = world->CreateBody(&bodydef);

	// Step 3 create shape
	b2PolygonShape shape;

	if (flippedBody) {
		flippedBody = false;
		// the reason for dividing by 2 is because box2D draws from the center
		shape.SetAsBox(w / 2 * Window::p2m, h / 2 * Window::p2m, b2Vec2(0.0f, (w / 2 * Window::p2m) * -1), 0.0f);
		// step 4 create fixture
		b2FixtureDef fixtureDef;
		fixtureDef.shape = &shape;
		fixtureDef.density = 1.0;
		fixtureDef.friction = 0.3f;
		fixtureDef.restitution = 0.5f;
		// Set the collision filters
		fixture = body->CreateFixture(&fixtureDef);
		fixture->SetSensor(true);
		fixture->SetUserData(this);
		for (int i = 0; i < 4; i++) {
			point[i] = ((b2PolygonShape*)body->GetFixtureList()->GetShape())->m_vertices[i];
			//std::cout << "point " << i << ": (" << point[i].x << ") (" << point[i].y << ")" << std::endl;
		}
		dr->DrawBox(point);
		dr->Init();
		vertices[0] = point[0].x; vertices[1] = point[0].y; vertices[2] = 0.0f; vertices[3] = 0.0f;  // lower-left corner
		vertices[4] = point[1].x; vertices[5] = point[1].y; vertices[6] = 1.0f; vertices[7] = 0.0f;  // lower-right corner
		vertices[8] = point[2].x; vertices[9] = point[2].y; vertices[10] = 1.0f; vertices[11] = 1.0f;  // upper-right corner
		vertices[12] = point[3].x; vertices[13] = point[3].y; vertices[14] = 0.0f; vertices[15] = 1.0f;  // uper left corner
	}
	else {
		flippedBody = true;
		// the reason for dividing by 2 is because box2D draws from the center
		shape.SetAsBox(w / 2 * Window::p2m, h / 2 * Window::p2m, b2Vec2(0.0f, (w / 2 * Window::p2m)), 0.0f);
		// step 4 create fixture
		b2FixtureDef fixtureDef;
		fixtureDef.shape = &shape;
		fixtureDef.density = 1.0;
		fixtureDef.friction = 0.3f;
		fixtureDef.restitution = 0.5f;
		// Set the collision filters
		fixture = body->CreateFixture(&fixtureDef);
		fixture->SetSensor(true);
		fixture->SetUserData(this);
		for (int i = 0; i < 4; i++) {
			point[i] = ((b2PolygonShape*)body->GetFixtureList()->GetShape())->m_vertices[i];
			//std::cout << "point " << i << ": (" << point[i].x << ") (" << point[i].y << ")" << std::endl;
		}
		dr->DrawBox(point);
		dr->Init();
		vertices[0] = point[0].x; vertices[1] = point[0].y; vertices[2] = 0.0f; vertices[3] = 1.0f;  // lower-left corner
		vertices[4] = point[1].x; vertices[5] = point[1].y; vertices[6] = 1.0f; vertices[7] = 1.0f;  // lower-right corner
		vertices[8] = point[2].x; vertices[9] = point[2].y; vertices[10] = 1.0f; vertices[11] = 0.0f;  // upper-right corner
		vertices[12] = point[3].x; vertices[13] = point[3].y; vertices[14] = 0.0f; vertices[15] = 0.0f;  // uper left corner
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

bool Weapon::IsFlipped() {
	return flippedBody;
}

void Weapon::SetAngle(glm::vec2 angle) {
	this->angle2 = angle;
}

void Weapon::SetDamage(float damage) {
	this->damage = damage;
}
void Weapon::SetAttackDuration(float attackDuration) {
	this->attackDuration = attackDuration;
}

void Weapon::Attack() {
	if (!attacking) {
		hit = false;
		attacking = true;
	}
}

bool Weapon::IsAttacking() {
	return attacking;
}

bool Weapon::Hit() {
	return hit;
}
