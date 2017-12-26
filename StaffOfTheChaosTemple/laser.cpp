#include "laser.h"
#include "mirror.h"

Laser::Laser(int width, int height, unsigned int textureID, b2World* world) : Sprite::Sprite(width, height, textureID)
{
	reflection = b2Vec2(0.0f, 0.0f);
	raycast = new Raycast(world);
	direction = glm::vec2(0.0f, 0.0f);
}

Laser::~Laser()
{
	delete raycast;
}

void Laser::Update(double deltaTime)
{
	// Draw the ray's direction and length
	raycast->ChangeColor(glm::vec3(1.0f, 1.0f, 1.0f));
	//raycast->Draw(localPosition, glm::atan(-direction.y, -direction.x));

	// Shoot raycast
	b2Vec2 globalPos = b2Vec2(localPosition.x * B2Entity::p2m, localPosition.y * B2Entity::p2m);
	b2Vec2 destination = globalPos + b2Vec2(direction.x * B2Entity::p2m, direction.y * B2Entity::p2m);
	raycast->Update(globalPos, destination);
	//world->RayCast(raycast, globalPos, destination);
	int hits = raycast->AmountOfHits();
	for (int i = 0; i < hits; i++) {
		RaycastHit rh = raycast->GetHit(i);
		B2Entity* b = static_cast<B2Entity*>(rh.fixture->GetUserData());
		// HIT MIRROR
		if (dynamic_cast<Mirror*>(b) != NULL) {
			hit = true;
			hitPosition = rh.point;
			// intersectionPoint is a vector from the ray's starting point and the hitted point
			b2Vec2 intersectionPoint = globalPos - destination;
			intersectionPoint *= rh.fraction;

			// Calculation reflection = d-(2*dot(d-n)*n)
			reflection = intersectionPoint - (2 * b2Dot(intersectionPoint, rh.normal) * rh.normal);
			// Draw the reflection
			raycast->ChangeColor(glm::vec3(1.0f, 0.0f, 0.0f));
			//raycast->Draw(glm::vec2(rh.point.x * B2Entity::m2p, rh.point.y * B2Entity::m2p), glm::atan(reflection.y, reflection.x));

			// Draw the normal
			raycast->ChangeColor(glm::vec3(0.0f, 1.0f, 0.0f));
			//raycast->Draw(glm::vec2((rh.point.x + rh.normal.x) * B2Entity::m2p, (rh.point.y + rh.normal.y) * B2Entity::m2p), glm::atan(rh.normal.y, rh.normal.x));
			// Scale the laser by the distance of hit
			localScale.y = rh.fraction;
			this->SetRepeatableUV(glm::vec2(1.0f, localScale.y * height / width));
			return;

		}
		// HIT CRYSTAL
		else if (dynamic_cast<Crystal*>(b) != NULL) {
			// Activate the crystal
			dynamic_cast<Crystal*>(b)->Hit();
			continue;
		}
		// HIT SENSOR
		else if (rh.fixture->IsSensor()) {
			// IGNORE IT
			continue;
		}
		// HIT B2ENTITY
		else {
			// Scale the laser by the distance of hit
			localScale.y = rh.fraction;
			hit = false;
			hitPosition = b2Vec2(0.0f, 0.0f);
			reflection = b2Vec2(0.0f, 0.0f);
			this->SetRepeatableUV(glm::vec2(1.0f, localScale.y * height / width));
			return;
		}
	}
	hit = false;
	hitPosition = b2Vec2(0.0f, 0.0f);
	reflection = b2Vec2(0.0f, 0.0f);
	localScale.y = 1.0f;
	this->SetRepeatableUV(glm::vec2(1.0f, localScale.y * height / width));
}

void Laser::SetDirection(glm::vec2 direction)
{
	this->direction = direction;
}

bool Laser::Hit()
{
	return hit;
}

glm::vec2 Laser::GetHitPosition()
{
	glm::vec2 hp = glm::vec2(hitPosition.x * B2Entity::m2p, hitPosition.y * B2Entity::m2p);
	return hp;
}

glm::vec2 Laser::GetReflection()
{
	glm::vec2 reflect = glm::vec2(reflection.x * B2Entity::m2p, reflection.y * B2Entity::m2p);
	return reflect;
}