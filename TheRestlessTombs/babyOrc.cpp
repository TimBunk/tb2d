#include "babyOrc.h"

BabyOrc::BabyOrc(Player* player, float lineOfSight, ResourceManager* rm, Camera* camera, Shader* shader, b2World* world) : Enemy::Enemy(player, lineOfSight, rm, camera, shader, world) {
	// stats of the babyorc
	damage = 1;
	speed = 5.0f;
	attackSpeed = 1.0f;
	health = 1;
	currentHealth = health;
	// Create the sword
	sword = new Weapon(damage, 135.0f, attackSpeed, false, camera, shader, this->world);
	sword->GiveTexture(this->rm->GetTexture("orcWeapon"));
	sword->CreateBody(0, 0, 18, 36);
	sword->SetAngle(glm::vec2(0.0f, 0.0f));
	sword->localPosition.x = 30.0f;
	this->AddChild(sword);
}

BabyOrc::~BabyOrc() {
	delete sword;
}

void BabyOrc::Update(double deltaTime) {
	if (LookForPlayer()) {
		// Calculate the angle between the player and piviot of the enemy
		glm::vec2 angle = glm::vec2(player->localPosition.x, player->localPosition.y) - glm::vec2(this->GetPositionInPixels().x, this->GetPositionInPixels().y);
		// Normalize the angle
		angle = glm::normalize(angle);
		// Set the length of the angle to 30 pixels away from the player's piviot
		angle *= 30.0f;
		sword->SetAngle(angle);
		sword->localPosition.x = angle.x;
		sword->localPosition.y = angle.y;
		// Flip the textures
		if (IsTextureFlipped() && sword->IsFlipped()) {
			sword->FlipBody();
		}
		else if (!IsTextureFlipped() && !sword->IsFlipped()) {
			sword->FlipBody();
		}
		// Attack the player if in range
		if (distancePlayer < minimalRange) {
			sword->Attack();
		}
	}
	// Check if the person got damaged
	if (damaged && timerDamaged < cooldownDamaged) {
		timerDamaged += deltaTime;
	}
	else {
		timerDamaged = 0.0f;
		damaged = false;
	}
}

void BabyOrc::TakeDamage(int damage) {
	if (currentHealth - damage > 0) {
		currentHealth -= damage;
		damaged = true;
	}
	else {
		currentHealth = 0;
		this->Destroy();
		sword->SetActive(false);
		this->RemoveChild(sword);
	}
}

void BabyOrc::Reset() {
	// Set variables back to original value
	body->SetTransform(b2Vec2(spawnPosition.x * Window::p2m, spawnPosition.y * Window::p2m), 0.0f);
	playerLastLocation = spawnPosition;
	if (!IsAlive()) {
		alive = true;
		sword->SetActive(true);
		this->AddChild(sword);
		currentHealth = health;
		SetActive(true);
	}
	currentHealth = health;
}
