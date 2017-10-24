#include "bomb.h"

Bomb::Bomb(float bombSize, float explosionTime, float explosionRadius, float impactTime, Texture bomb, Texture explosionTexture, Camera* camera, Shader* shader) : Destructable::Destructable(camera, shader) {
	this->explosionTime = explosionTime;
	this->explosionRadius = explosionRadius;
	this->impactTime = impactTime;
	this->explosionTexture = explosionTexture;
	this->bomb = bomb;
	GiveTexture(bomb);
	color = glm::vec4(0.0f, 0.0f, 0.0f, 0.0f);
	timer = 0.0f;
	explode = false;
	impact = false;
	currentImpactTime = 0.0f;
	w = bombSize;
}

Bomb::~Bomb() {

}

void Bomb::Update(float deltaTime) {
	this->localPosition = glm::vec3(this->GetPositionInPixels().x, this->GetPositionInPixels().y, 1.0f);
	if (IsAlive()) {
		color.r += (deltaTime/(explosionTime*2.0f));
		if (color.r >= 0.5f && !explode) {
			explode = true;
			impact = true;
			color.r = 0.0f;
			if (body != NULL) {
				body->DestroyFixture(fixture);
				world->DestroyBody(body);
				glDeleteVertexArrays(1, &VAO);
				glDeleteBuffers(1, &VBO);
				glDeleteBuffers(1, &EBO);
			}
			CreateBody(this->localPosition.x, this->localPosition.y, explosionRadius, this->world);
			GiveTexture(explosionTexture);
		}
		if (explode) {
			currentImpactTime += deltaTime;
			if (currentImpactTime >= impactTime) {
				impact = false;
				this->Destroy();
			}
		}
	}
}

void Bomb::Draw() {
	if (alive) {
		shader->Use();
		shader->SetMatrix4("projection", camera->GetProjectionMatrix());
		shader->SetMatrix4("view", camera->GetViewMatrix());
		shader->SetVec4Float("color", color);
		glm::mat4 model;
		model = glm::translate(model, glm::vec3(GetPositionInPixels(), this->GetGlobalPosition().z));
		model = glm::rotate(model, GetAngle(), glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::scale(model, glm::vec3(Window::m2p, Window::m2p, 0.0f));
		shader->SetMatrix4("model", model);
		glActiveTexture(GL_TEXTURE0 + texture.id);
		shader->SetInt("ourTexture", texture.id);
		glBindTexture(GL_TEXTURE_2D, texture.id);
		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glActiveTexture(GL_TEXTURE0);
		glBindVertexArray(0);
	}
}

bool Bomb::Impact() {
	if (impact) {
		impact = false;
		return true;
	}
	return false;
}

void Bomb::Reset() {
	alive = true;
	SetActive(true);
	explode = false;
	GiveTexture(bomb);
	if (body != NULL) {
		body->DestroyFixture(fixture);
		world->DestroyBody(body);
		glDeleteVertexArrays(1, &VAO);
		glDeleteBuffers(1, &VBO);
		glDeleteBuffers(1, &EBO);
	}
	CreateBody(this->localPosition.x, this->localPosition.y, w, this->world);
	currentImpactTime = 0.0f;
}

void Bomb::CreateBody(int x, int y, int w, b2World* world) {
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
	shape.SetAsBox(w / 2 * Window::p2m, w / 2 * Window::p2m);
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
	fixture->SetSensor(true);
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
