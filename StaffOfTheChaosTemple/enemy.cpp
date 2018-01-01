#include "enemy.h"

Enemy::Enemy(Player* player, float lineOfSight, float forceTowardsPlayer, float forceFromAbstacles, float health, float speed, float damage, int width, int height, unsigned int textureID, b2World * world) : Person::Person(health, speed, damage, width, height, textureID, world)
{
	this->player = player;
	this->lineOfSight = lineOfSight;
	this->forceTowardsPlayer = forceTowardsPlayer;
	this->forceFromObstacles = forceFromAbstacles;
	raycast = new Raycast(world);

	distanceObjects = new B2Entity(width, height, 0, world);
	distanceObjects->CreateCircleCollider(75, true, true);
	distanceObjects->SetDebugColor(glm::vec3(1, 0, 0));
	this->AddChild(distanceObjects);

	mirror = new Mirror(false, 45.0f, 120.0f, ResourceManager::GetTexture("mirror")->GetId(), world);
	mirror->localPosition.x = 100;
	mirror->CreateBoxCollider(45.0f, 120.0f, glm::vec2(0.0f, 0.0f), false, false);
	mirror->SetFilter(2);
	AddChild(mirror);

	attackRadius = 250.0f;
	sword = new B2Entity(100, 200, ResourceManager::GetTexture("sword")->GetId(), world);
	sword->SetPivot(glm::vec2(0.0f, -0.5f));
	sword->CreateBoxCollider(100, 200, glm::vec2(0, -0.5f), true, true);
	sword->localPosition = glm::vec2(50,85);
	sword->localAngle = glm::radians(90.0f);
	sword->SetFilter(2);
	AddChild(sword);

	redHealthbar = new Sprite(150, 15, 0);
	redHealthbar->SetColor(glm::vec4(1, 0, 0, 1));
	redHealthbar->SetPivot(glm::vec2(0.5f, 0.0f));
	AddChild(redHealthbar);
	greenHealthbar = new Sprite(150, 15, 0);
	greenHealthbar->SetColor(glm::vec4(0, 1, 0, 1));
	greenHealthbar->SetPivot(glm::vec2(0.5f, 0.0f));
	AddChild(greenHealthbar);

	dead = false;
}

Enemy::~Enemy()
{
	if (dead == false) {
		delete raycast;
		delete distanceObjects;
		delete mirror;
		delete sword;
		delete redHealthbar;
		delete greenHealthbar;
	}
}

void Enemy::Update(double deltaTime)
{
	// Update the healthbars
	redHealthbar->localPosition = glm::vec2(position.x - 75, position.y + 125);
	greenHealthbar->localPosition = glm::vec2(position.x - 75, position.y + 125);
	greenHealthbar->SetWidth(currentHealth / maxHealth * 150);
	redHealthbar->UpdateChilderen(NULL, deltaTime);
	redHealthbar->Draw();
	greenHealthbar->UpdateChilderen(NULL, deltaTime);
	greenHealthbar->Draw();

	glm::vec2 rayDestination = player->GetGlobalPosition() - position;
	rayDestination = glm::normalize(rayDestination);
	rayDestination *= lineOfSight;
	rayDestination += position;
	raycast->Update(position, rayDestination);
	raycast->Draw(glm::vec3(0,1,0));

	glm::vec2 acceleration;
	bool playerHit = false;
	// Check if the first object hitted by the raycast is the player
	std::vector<RaycastHit> hits = raycast->GetHits();
	for (int i = 0; i < hits.size(); i++) {
		B2Entity* b = static_cast<B2Entity*>(hits[i].fixture->GetUserData());
		if (b == player) {
			// hitted player
			lastPositionPlayer = player->GetGlobalPosition();
			if (glm::length(lastPositionPlayer - position) < attackRadius) {
				sword->localAngle -= glm::radians(180.0f) * deltaTime;
				if (sword->localAngle < 0) {//glm::radians(90.0f) * -1) {
					sword->localAngle = glm::radians(90.0f);
				}
				if (sword->Contact(player)) {
					player->Damage(damage * deltaTime);
				}
			}
			else {
				sword->localAngle = glm::radians(90.0f);
				acceleration += (glm::normalize(lastPositionPlayer - position) * forceTowardsPlayer);
			}
			playerHit = true;
			glm::vec2 diff = player->GetGlobalPosition() - position;
			diff = glm::normalize(diff);
			float _angle = glm::atan(diff.y, diff.x);
			localAngle = _angle;
			continue;
		}
		// If the raycast hit is a enemy or a sensor continue with the for loop otheriwse break it
		else if (dynamic_cast<Enemy*>(b) != NULL || hits[i].fixture->IsSensor() || b == mirror || b->GetFilter() == 2) {
			continue;
		}
		break;
	}
	if (!playerHit && glm::length(position - lastPositionPlayer) > 75.0f) {
		acceleration += (glm::normalize(lastPositionPlayer - position) * forceTowardsPlayer);
		glm::vec2 diff = lastPositionPlayer - position;
		diff = glm::normalize(diff);
		float _angle = glm::atan(diff.y, diff.x);
		localAngle = _angle;
	}

	std::vector<B2Entity*> inRangeObjects = distanceObjects->GetAllContacts();
	for (int i = 0; i < inRangeObjects.size(); i++) {
		if (inRangeObjects[i] != this && inRangeObjects[i] != player && inRangeObjects[i]->GetFilter() != 2) {
			// hitted a wall or something
			acceleration += (glm::normalize(position - inRangeObjects[i]->GetGlobalPosition()) * forceFromObstacles);
		}
	}
	if (acceleration.x != 0 || acceleration.y != 0) {
		velocity += acceleration;
		velocity = glm::normalize(velocity);
		velocity *= speed;
		this->localPosition = this->ApplyVelocityB2body(velocity);
	}
}

void Enemy::Die()
{
	dead = true;
	delete raycast;
	delete distanceObjects;
	delete mirror;
	delete sword;
	delete redHealthbar;
	delete greenHealthbar;
}
