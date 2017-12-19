#include "enemy.h"

Enemy::Enemy(Player* player, float lineOfSight, float forceTowardsPlayer, float forceFromAbstacles, int health, float speed, int damage, int width, int height, Texture* texture, Camera * camera, b2World * world) : Person::Person(health, speed, damage, width, height, texture, camera, world)
{
	this->player = player;
	this->lineOfSight = lineOfSight;
	this->forceTowardsPlayer = forceTowardsPlayer;
	this->forceFromObstacles = forceFromAbstacles;
	raycast = new Raycast(world);
	raycast->CreateLine(lineOfSight, 10.0f, camera, ResourceManager::GetShader("debug"), glm::vec3(1, 0, 0));
	distanceObjects = new B2Entity(width, height, glm::vec2(0,0), nullptr, camera, world);
	distanceObjects->CreateCircleCollider(125, true, true);
	distanceObjects->EnableDebugRendering(glm::vec3(1, 0, 0));
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
	raycast->Update(b2Vec2(position.x * p2m, position.y * p2m), b2Vec2(diff.x * p2m, diff.y * p2m));
	float _angle = (angle - M_PI);
	raycast->Draw(position, _angle);

	glm::vec2 acceleration;
	bool playerHit = false;
	// Check if the first object hitted by the raycast is the player
	if (raycast->AmountOfHits() > 0) {
		int size = raycast->AmountOfHits();
		for (int i = 0; i < size; i++) {
			B2Entity* b = static_cast<B2Entity*>(raycast->GetHit(i).fixture->GetUserData());
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
			else if (raycast->GetHit(i).fixture->IsSensor()) {
				continue;
			}
			break;
		}
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
