#include "player.h"

Player::Player(int x, int y, int w, int h, bool dyn, b2World* world, Camera* camera, Shader* shader) {
	this->input = nullptr;
	left = SDL_SCANCODE_0;
	right = SDL_SCANCODE_0;
	this->world = world;
	this->camera = camera;
	this->shader = shader;
	b2BodyDef bodydef;
	bodydef.position.Set(x*Window::p2m, y*Window::p2m);
	if (dyn) {
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
	shape.SetAsBox(w / 2 * Window::p2m, h / 2 * Window::p2m);

	// step 4 create fixture
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &shape;
	fixtureDef.density = 1.0;
	fixtureDef.friction = 0.3f;
	fixtureDef.restitution = 0.5f;
	fixture = body->CreateFixture(&fixtureDef);
	//b2Vec2 point[4];
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

Player::~Player() {

}

void Player::Update(float deltaTime) {
	float speed = 1000.0f * deltaTime;
	if (input->KeyDown(left)) {
		body->SetLinearVelocity(b2Vec2(-speed, 0.0f));
	}
	if (input->KeyDown(right)) {
		body->SetLinearVelocity(b2Vec2(speed, 0.0f));
	}
}

void Player::Draw() {
	shader->Use();
	shader->SetMatrix4("projection", camera->GetProjectionMatrix());
	shader->SetMatrix4("view", camera->GetViewMatrix());
	glm::mat4 model;
	model = glm::translate(model, GetPositionInPixels());
	model = glm::rotate(model, GetAngle(), glm::vec3(0.0f, 0.0f, 1.0f));
	model = glm::scale(model, glm::vec3(Window::m2p, Window::m2p, 0.0f));
	shader->SetMatrix4("model", model);
	glActiveTexture(GL_TEXTURE0 + tex.id);
	shader->SetInt("ourTexture", tex.id);
	glBindTexture(GL_TEXTURE_2D, tex.id);
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
	glActiveTexture(GL_TEXTURE0);
}

void Player::SetMovement(SDL_Scancode left, SDL_Scancode right, Input* input) {
	this->left = left;
	this->right = right;
	this->input = input;
}

void Player::SetTexture(Texture texture) {
	this->tex = texture;
}

glm::vec3 Player::GetPositionInPixels()
{
	glm::vec3 pos;
	pos = glm::vec3(body->GetPosition().x * Window::m2p, body->GetPosition().y * Window::m2p, 0.0f);
	return pos;
}

float Player::GetAngle()
{
	float angle;
	angle = body->GetAngle();
	return angle;
}
