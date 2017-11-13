#include "bomb.h"

Bomb::Bomb(float bombSize, float explosionTime, float explosionRadius, float impactTime, Texture bomb, Texture explosionTexture, Camera* camera, Shader* shader, b2World* world) : Item::Item(camera, shader, world) {
	// Initialize all of the variables
	this->explosionTime = explosionTime;
	this->explosionRadius = explosionRadius;
	this->impactTime = impactTime;
	this->explosionTexture = explosionTexture;
	this->bomb = bomb;
	GiveTexture(bomb);
	color = glm::vec4(0.0f, 0.0f, 0.0f, 0.0f);
	explode = false;
	impact = false;
	currentImpactTime = 0.0f;
	w = bombSize;
}

Bomb::~Bomb() {

}

void Bomb::Update(double deltaTime) {
	if (IsAlive()) {
		// Increase the red value of the color of the bomb
		color.r += (deltaTime/(explosionTime*2.0f));
		// When the bomb is half way red let it explode
		if (color.r >= 0.5f && !explode) {
			explode = true;
			impact = true;
			color.r = 0.0f;
			// delete the old body
			if (body != NULL) {
				body->DestroyFixture(fixture);
				world->DestroyBody(body);
				glDeleteVertexArrays(1, &VAO);
				glDeleteBuffers(1, &VBO);
				glDeleteBuffers(1, &EBO);
			}
			// create the body of the explosion
			CreateBody(this->localPosition.x, this->localPosition.y, explosionRadius);
			GiveTexture(explosionTexture);
		}
		if (explode) {
			// Let the bomb explode and deal possible damage to the player
			currentImpactTime += deltaTime;
			if (currentImpactTime >= impactTime) {
				explode = false;
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
	impact = false;
	GiveTexture(bomb);
	color.r = 0.0f;
	// recreate the bomb and delete the explosion
	if (body != NULL) {
		body->DestroyFixture(fixture);
		world->DestroyBody(body);
		glDeleteVertexArrays(1, &VAO);
		glDeleteBuffers(1, &VBO);
		glDeleteBuffers(1, &EBO);
	}
	CreateBody(this->localPosition.x, this->localPosition.y, w);
	currentImpactTime = 0.0f;
}

void Bomb::CreateBody(int x, int y, int w) {
	this->localPosition = glm::vec3(x, y, 1.0f);
	width = w;
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
