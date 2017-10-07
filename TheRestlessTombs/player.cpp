#include "player.h"

Player::Player(Input* input, Camera* camera, Shader* shader, Texture textureHand, b2World* world) : Person::Person(camera, shader) {
	this->input =  input;
	hand = new Hand(camera, shader);
	hand->GiveTexture(textureHand);
	hand->CreateBody(200, 200, 20, 20, false, world);
	this->AddChild(hand);
}

Player::~Player() {
	delete hand;
}

void Player::Update(float deltaTime) {
	float speed = 2000.0f * deltaTime;
	b2Vec2 vel = b2Vec2(0.0f, 0.0f);
	if (input->KeyDown(SDL_SCANCODE_W) || input->KeyDown(SDL_SCANCODE_UP)) {
		vel.y -= speed;
	}
	if (input->KeyDown(SDL_SCANCODE_D) || input->KeyDown(SDL_SCANCODE_RIGHT)) {
		vel.x += speed;
	}
	if (input->KeyDown(SDL_SCANCODE_S) || input->KeyDown(SDL_SCANCODE_DOWN)) {
		vel.y += speed;
	}
	if (input->KeyDown(SDL_SCANCODE_A) || input->KeyDown(SDL_SCANCODE_LEFT)) {
		vel.x -= speed;
	}
	body->SetLinearVelocity(vel);
	this->camera->SetPosition(glm::vec2(-this->GetPositionInPixels().x - -camera->screenWidth/2, -this->GetPositionInPixels().y - -camera->screenHeight/2));

	// Get the mouse position in world space
	glm::vec2 mp = input->GetMousePositionWorldSpace(camera);
	// Calculate the angle between the mouse and piviot of the player
	glm::vec2 angle = mp - glm::vec2(this->GetPositionInPixels().x, this->GetPositionInPixels().y);
	// Normalize the angle
	angle = glm::normalize(angle);
	// Set the length of the angle to 60 pixels away from the player's piviot
	angle *= 60;
	// Save the player's current rotation and set the distance of the hand from the player
	this->localPosition.x = this->GetPositionInPixels().x;
	this->localPosition.y = this->GetPositionInPixels().y;
	hand->localPosition.x = angle.x;
	hand->localPosition.y = angle.y;
	hand->Draw();
}
