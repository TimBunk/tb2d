#include "babyOrc.h"

BabyOrc::BabyOrc(Player* player, float lineOfSight, Texture _sword, Camera* camera, Shader* shader, Shader* lineRenderer, b2World* world) : Enemy::Enemy(player, lineOfSight, camera, shader, lineRenderer, world) {
	// stats of the babyorc
	damage = 1;
	speed = 3.0f;
	attackSpeed = 1.0f;
	health = 2;
	currentHealth = health;

	sword = new Weapon(damage, 135.0f, attackSpeed, false, camera, shader);
	sword->GiveTexture(_sword);
	sword->CreateBody(0, 0, 18, 36, world);
	sword->SetAngle(glm::vec2(0.0f, 0.0f));
	sword->localPosition.x = 30.0f;
	this->AddChild(sword);
}

BabyOrc::~BabyOrc() {
	delete sword;
}

void BabyOrc::Update(float deltaTime) {
	if (LookForPlayer(deltaTime)) {
		// Calculate the angle between the player and piviot of the enemy
		glm::vec2 angle = glm::vec2(player->localPosition.x, player->localPosition.y) - glm::vec2(this->GetPositionInPixels().x, this->GetPositionInPixels().y);
		// Normalize the angle
		angle = glm::normalize(angle);
		// Set the length of the angle to 30 pixels away from the player's piviot
		angle *= 30.0f;
		sword->SetAngle(angle);
		sword->localPosition.x = angle.x;
		sword->localPosition.y = angle.y;
		if (IsTextureFlipped() && sword->IsFlipped()) {
			sword->FlipBody();
		}
		else if (!IsTextureFlipped() && !sword->IsFlipped()) {
			sword->FlipBody();
		}
		if (distancePlayer < minimalRange) {
			sword->Attack();
		}
	}
}

void BabyOrc::TakeDamage(int damage) {
	if (currentHealth - damage > 0) {
		currentHealth -= damage;
	}
	else {
		currentHealth = 0;
		this->Destroy();
		sword->SetActive(false);
		this->RemoveChild(sword);
	}
}

void BabyOrc::Reset() {
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
