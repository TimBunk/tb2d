#include "armoredOrc.h"

ArmoredOrc::ArmoredOrc(Player* player, float lineOfSight, ResourceManager* rm, Camera* camera, Shader* shader, b2World* world) : Enemy::Enemy(player, lineOfSight, rm, camera, shader, world) {
	// stats of the ArmoredOrc
	damage = 1;
	speed = 3.0f;
	attackSpeed = 1.0f;
	health = 4;
	currentHealth = health;
	// Create the sword
	sword = new Weapon(damage, 135.0f, attackSpeed, false, camera, shader, this->world);
	sword->GiveTexture(this->rm->GetTexture("orcWeapon"));
	sword->CreateBody(0, 0, 27, 54);
	sword->SetAngle(glm::vec2(0.0f, 0.0f));
	sword->localPosition.x = 40.0f;
	this->AddChild(sword);
}

ArmoredOrc::~ArmoredOrc() {

}

void ArmoredOrc::Update(double deltaTime) {
	if (LookForPlayer()) {
		// Calculate the angle between the player and piviot of the enemy
		glm::vec2 angle = glm::vec2(player->localPosition.x, player->localPosition.y) - glm::vec2(this->GetPositionInPixels().x, this->GetPositionInPixels().y);
		// Normalize the angle
		angle = glm::normalize(angle);
		// Set the length of the angle to 40 pixels away from the psychoorc's piviot
		angle *= 40.0f;
		sword->SetAngle(angle);
		sword->localPosition.x = angle.x;
		sword->localPosition.y = angle.y;
		// flip the texture of the sword
		if (IsTextureFlipped() && sword->IsFlipped()) {
			sword->FlipBody();
		}
		else if (!IsTextureFlipped() && !sword->IsFlipped()) {
			sword->FlipBody();
		}
		// atack the player when it is in range
		if (distancePlayer < minimalRange) {
			sword->Attack();
		}
	}
}

void ArmoredOrc::TakeDamage(int damage) {
	if (currentHealth - damage > 0) {
		currentHealth -= damage;
	}
	// If the ArmoredOrc dies destroy it and it's sword
	else {
		currentHealth = 0;
		this->Destroy();
		sword->SetActive(false);
		this->RemoveChild(sword);
		if (item != nullptr) {
			item->Reset();
		}
	}
}

void ArmoredOrc::Reset() {
	// Reset the ArmoredOrc to it's base values
	body->SetTransform(b2Vec2(spawnPosition.x * Window::p2m, spawnPosition.y * Window::p2m), 0.0f);
	playerLastLocation = spawnPosition;
	if (!IsAlive()) {
		alive = true;
		sword->SetActive(true);
		this->AddChild(sword);
		currentHealth = health;
		SetActive(true);
		if (item != nullptr) {
			item->Destroy();
		}
	}
	currentHealth = health;
}
