#include "bomberOrc.h"

BomberOrc::BomberOrc(Player* player, float lineOfSight, ResourceManager* rm, Camera* camera, Shader* shader, b2World* world) : Enemy::Enemy(player, lineOfSight, rm, camera, shader, world) {
	this->rm = rm;
	timer = 0.0f;
	// stats of the bomberOrc
	damage = 1;
	speed = 4.5f;
	attackSpeed = 1.25f;
	health = 3;
	currentHealth = health;
}

BomberOrc::~BomberOrc() {
	std::vector<Bomb*>::iterator it = bombs.begin();
	while (it != bombs.end()) {
		delete (*it);
		it = bombs.erase(it);
	}
}

void BomberOrc::Update(float deltaTime) {
	if (IsAlive()) {
		if (LookForPlayer(deltaTime)) {
			timer += deltaTime;
			if (timer >= attackSpeed) {
				Bomb* b = new Bomb(30.0f, 3.0f, 150.0f, 0.2f, this->rm->GetTexture("bomb"), this->rm->GetTexture("explosion"), this->camera, this->rm->GetShader("bomb"), this->world);
				glm::vec3 bombPos = ((player->localPosition - this->localPosition) *= 0.75f) + this->localPosition;
				b->CreateBody(bombPos.x, bombPos.y, 30);
				bombs.push_back(b);
				timer = 0.0f;
			}
		}
	}
	std::vector<Bomb*>::iterator it = bombs.begin();
	while (it != bombs.end()) {
		if (!(*it)->IsAlive()) {
			delete (*it);
			it = bombs.erase(it);
		}
		else {
			(*it)->Update(deltaTime);
			(*it)->Draw();
			++it;
		}
	}
}

bool BomberOrc::LookForPlayer(float deltaTime) {
	this->localPosition = glm::vec3(this->GetPositionInPixels().x, this->GetPositionInPixels().y, 1.0f);
	b2Vec2 vel = b2Vec2(0.0f, 0.0f);
	if (this->ShootRaycast()) {
		if (distancePlayer > lineOfSight - minimalRange) {
			vel = b2Vec2(player->localPosition.x - this->localPosition.x, player->localPosition.y - this->localPosition.y);
		}
		else if (distancePlayer <= lineOfSight/2 + minimalRange){
			vel = b2Vec2(this->localPosition.x - player->localPosition.x, this->localPosition.y - player->localPosition.y);
		}
		vel.Normalize();
		vel *= (speed * 500.0f * deltaTime);
		body->SetLinearVelocity(vel);
		if (IsTextureFlipped() && vel.x < 0.0f) {
			FlipTexture();
		}
		else if (!IsTextureFlipped() && vel.x > 0.0f) {
			FlipTexture();
		}
		return true;
	}
	else if (glm::distance(this->localPosition, playerLastLocation) > minimalRange) {
		vel = b2Vec2(playerLastLocation.x - this->localPosition.x, playerLastLocation.y - this->localPosition.y);
		vel.Normalize();
		vel *= (speed * 500.0f * deltaTime);
		body->SetLinearVelocity(vel);
		return false;
	}
	body->SetLinearVelocity(vel);
	return false;
}

void BomberOrc::TakeDamage(int damage) {
	if (currentHealth - damage > 0) {
		currentHealth -= damage;
	}
	else {
		currentHealth = 0;
		this->Destroy();
		if (item != nullptr) {
			item->Reset();
		}
	}
}

void BomberOrc::Reset() {
	body->SetTransform(b2Vec2(spawnPosition.x * Window::p2m, spawnPosition.y * Window::p2m), 0.0f);
	playerLastLocation = spawnPosition;
	if (!IsAlive()) {
		alive = true;
		currentHealth = health;
		SetActive(true);
		if (item != nullptr) {
			item->Destroy();
		}
	}
	currentHealth = health;
}
