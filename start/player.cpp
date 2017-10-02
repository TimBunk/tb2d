#include "player.h"

Player::Player(b2World* world, Camera* camera) : Entity::Entity(camera) {
	//Box* box = new Box(0, 0, 50, 50, true, Configure::P2M, world, camera->GetProjectionMatrix());
	//box->Draw(camera->GetViewMatrix())
}

Player::~Player() {
	
}

void Player::Update(float deltaTime) {

}
