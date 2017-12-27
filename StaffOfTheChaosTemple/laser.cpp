#include "laser.h"
#include "mirror.h"

Laser::Laser(int width, int height, unsigned int textureID, b2World* world) : Sprite::Sprite(width, height, textureID)
{
	raycast = new Raycast(world);
}

Laser::~Laser()
{
	delete raycast;
}

void Laser::Update(double deltaTime)
{
	// Shoot raycast
	glm::vec2 destination = localPosition + direction;
	raycast->Update(localPosition, destination);
	raycast->Draw(glm::vec3(1, 1, 1));

	std::vector<RaycastHit> hits = raycast->GetHits();
	for (int i = 0; i < hits.size(); i++) {
		RaycastHit rh = hits[i];
		B2Entity* b = static_cast<B2Entity*>(rh.fixture->GetUserData());
		// HIT MIRROR
		if (dynamic_cast<Mirror*>(b) != NULL) {
			hit = true;
			hitPosition = rh.point;
			// intersectionPoint is a vector from the ray's starting point and the hitted point
			glm::vec2 intersectionPoint = localPosition - destination;
			intersectionPoint *= rh.fraction;
			// Calculation reflection = d-(2*dot(d-n)*n)
			reflection = intersectionPoint - (2 * glm::dot(intersectionPoint, rh.normal) * rh.normal);

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
			hitPosition = glm::vec2();
			reflection = glm::vec2();
			this->SetRepeatableUV(glm::vec2(1.0f, localScale.y * height / width));
			return;
		}
	}
	hit = false;
	hitPosition = glm::vec2();
	reflection = glm::vec2();
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