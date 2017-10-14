#include "player.h"

Player::Player(Input* input, Camera* camera, Shader* shader, Texture textureHand, Texture textureSword, b2World* world) : Person::Person(camera, shader) {
	this->input =  input;
	sword = new Weapon(1.0f, 135.0f, 0.25f, true, camera, shader);
	sword->GiveTexture(textureSword);
	sword->CreateBody(0, 0, 30, 60, world);
	this->AddChild(sword);
	currentRoom = 0;
}

Player::~Player() {
	delete sword;
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
	if (input->MousePress(1)) {
		if (!sword->IsAttacking()) {
			sword->Attack();
			std::cout << "Mouse clicked" << std::endl;
		}
	}

	body->SetLinearVelocity(vel);
	this->camera->SetPosition(glm::vec2(-this->GetPositionInPixels().x - -camera->screenWidth/2, -this->GetPositionInPixels().y - -camera->screenHeight/2));

	this->localPosition.x = this->GetPositionInPixels().x;
	this->localPosition.y = this->GetPositionInPixels().y;
	this->localPosition.z = 5.0f;
	// FLIP the player's texture according to the mouse it's location
	if (input->GetMousePositionScreenSpace(camera).x > camera->screenWidth/2 && this->IsTextureFlipped()) {
		this->FlipTexture();
		sword->FlipBody();
	}
	else if (input->GetMousePositionScreenSpace(camera).x < camera->screenWidth/2 && !this->IsTextureFlipped()) {
		this->FlipTexture();
		sword->FlipBody();
	}

	// Get the mouse position in world space
	glm::vec2 mp = input->GetMousePositionWorldSpace(camera);
	// Calculate the angle between the mouse and piviot of the player
	glm::vec2 angle = mp - glm::vec2(this->GetPositionInPixels().x, this->GetPositionInPixels().y);
	// Normalize the angle
	angle = glm::normalize(angle);
	// Set the length of the angle to 40 pixels away from the player's piviot
	angle *= 40;
	sword->SetAngle(angle);
	sword->localPosition.x = angle.x;
	sword->localPosition.y = angle.y;
}

void Player::SetRoom(int number) {
	this->currentRoom = number;
}

int Player::GetRoom() {
	return currentRoom;
}
