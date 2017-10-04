#include "player.h"

Player::Player(Input* input, Camera* camera, Shader* shader) : Person::Person(camera, shader) {
	this->input =  input;
}

Player::~Player() {

}

void Player::Update(float deltaTime) {
	float speed = 2000.0f * deltaTime;
	b2Vec2 vel = b2Vec2(0.0f, 0.0f);
	if (input->KeyDown(SDL_SCANCODE_W) || input->KeyDown(SDL_SCANCODE_UP)) {
		std::cout << "KEY UP" << std::endl;
		vel.y -= speed;
	}
	if (input->KeyDown(SDL_SCANCODE_D) || input->KeyDown(SDL_SCANCODE_RIGHT)) {
		std::cout << "KEY RIGHT" << std::endl;
		vel.x += speed;
	}
	if (input->KeyDown(SDL_SCANCODE_S) || input->KeyDown(SDL_SCANCODE_DOWN)) {
		std::cout << "KEY DOWN" << std::endl;
		vel.y += speed;
	}
	if (input->KeyDown(SDL_SCANCODE_A) || input->KeyDown(SDL_SCANCODE_LEFT)) {
		std::cout << "KEY LEFT" << std::endl;
		vel.x -= speed;
	}
	body->SetLinearVelocity(vel);
}
