#include "enemy.h"

Enemy::Enemy(Player* player, float lineOfSight, float forceTowardsPlayer, float forceFromAbstacles, int health, float speed, int damage, int width, int height, unsigned int textureID, b2World * world) : Person::Person(health, speed, damage, width, height, textureID, world)
{
	this->player = player;
	this->lineOfSight = lineOfSight;
	this->forceTowardsPlayer = forceTowardsPlayer;
	this->forceFromObstacles = forceFromAbstacles;
	raycast = new Raycast(world);
	//raycast->CreateLine(lineOfSight, 10.0f, camera, ResourceManager::GetShader("defaultColor"), glm::vec3(1, 0, 0));
	distanceObjects = new B2Entity(width, height, 0, world);
	distanceObjects->CreateCircleCollider(125, true, true);
	distanceObjects->SetDebugColor(glm::vec3(1, 0, 0));
	this->AddChild(distanceObjects);
}

Enemy::~Enemy()
{
	delete raycast;
	delete distanceObjects;
}

void Enemy::Update(double deltaTime)
{
	glm::vec2 diff = player->GetGlobalPosition() - position;
	diff = glm::normalize(diff);
	localAngle = glm::atan(diff.y, diff.x);
	diff *= lineOfSight;
	diff += position;
	raycast->Update(position, diff);
	raycast->Draw(glm::vec3(0,1,0));
	float _angle = (angle - M_PI);

	glm::vec2 acceleration;
	bool playerHit = false;
	// Check if the first object hitted by the raycast is the player
	std::vector<RaycastHit> hits = raycast->GetHits();
	for (int i = 0; i < hits.size(); i++) {
		B2Entity* b = static_cast<B2Entity*>(hits[i].fixture->GetUserData());
		if (b == player) {
			// hitted player
			lastPositionPlayer = player->GetGlobalPosition();
			acceleration += (glm::normalize(lastPositionPlayer - position) * forceTowardsPlayer);
			playerHit = true;
			continue;
		}
		// If the raycast hit is a enemy or a sensor continue with the for loop otheriwse break it
		else if (dynamic_cast<Enemy*>(b) != NULL) {
			continue;
		}
		else if (hits[i].fixture->IsSensor()) {
			continue;
		}
		break;
	}
	if (!playerHit && glm::length(position - lastPositionPlayer) > 125.0f) {
		acceleration += (glm::normalize(lastPositionPlayer - position) * forceTowardsPlayer);
	}

	std::vector<B2Entity*> inRangeObjects = distanceObjects->GetAllContacts();
	for (int i = 0; i < inRangeObjects.size(); i++) {
		if (inRangeObjects[i] != this && inRangeObjects[i] != player) {
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
