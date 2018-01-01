#include "laser.h"
#include "mirror.h"
#include "person.h"

Laser::Laser(float damage, float laserRange, int width, int height, unsigned int textureID, b2World* world) : Sprite::Sprite(width, height, textureID)
{
	this->damage = damage;
	this->laserRange = laserRange;
	raycast = new Raycast(world);
	pr = RenderManager::GetParticleRenderer("particle");
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
			UpdateParticles(deltaTime);
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
		// HITTED PLAYER OR ENEMY
		else if (dynamic_cast<Person*>(b) != NULL) {
			// Damage the person
			dynamic_cast<Person*>(b)->Damage(damage * deltaTime);
			localScale.y = rh.fraction;
			hit = false;
			hitPosition = rh.point;
			reflection = glm::vec2();
			UpdateParticles(deltaTime);
			return;
		}
		// HIT B2ENTITY
		else {
			// Scale the laser by the distance of hit
			localScale.y = rh.fraction;
			hit = false;
			hitPosition = rh.point;
			reflection = glm::vec2();
			UpdateParticles(deltaTime);
			return;
		}
	}
	localScale.y = 1.0f;
	hit = false;
	hitPosition = destination;
	reflection = glm::vec2();
	UpdateParticles(deltaTime);
}

void Laser::Draw()
{
	for (int i = 0; i < particles.size(); i++) {
		pr->Submit(particles[i]);
	}
}

void Laser::UpdateParticles(double deltaTime)
{
	glm::vec2 diff = hitPosition - position;
	float distance = glm::length(diff);
	// Iterate through our vectors and update them or delete them if neccesary
	std::vector<Particle>::iterator itParticles = particles.begin();
	std::vector<float>::iterator itRandomPositions = randomLengths.begin();
	std::vector<glm::vec2>::iterator itRandomOffets = randomOffsets.begin();
	while (itParticles != particles.end()) {
		// Delete the particle and its randomPosition if the randomPosition is greather then the distance
		if (glm::length((*itRandomPositions) * diff) > distance) {
			itParticles = particles.erase(itParticles);
			itRandomPositions = randomLengths.erase(itRandomPositions);
			itRandomOffets = randomOffsets.erase(itRandomOffets);
		}
		// Update the position of the particles
		else {
			// Move particle
			(*itRandomPositions) += (glm::normalize((*itRandomPositions)) * deltaTime * 0.25f);
			glm::vec2 randomVec2 = diff * (*itRandomPositions) + (*itRandomOffets);
			(*itParticles).position = randomVec2 + position;
			++itParticles;
			++itRandomPositions;
			++itRandomOffets;
		}
	}
	int amountParticles = ((int)(localScale.y * 100.0f));
	for (int i = particles.size(); i < amountParticles; i++) {
		Particle p;
		
		float randomLength = ((float)(std::rand() % 1000)/1000);
		randomLengths.push_back(randomLength);

		glm::vec2 randomOffset;
		randomOffset.x = ((float)(std::rand() % 20) - 10);
		randomOffset.y = ((float)(std::rand() % 20) -  10);
		randomOffsets.push_back(randomOffset);

		glm::vec2 randomVec2 = diff * randomLength + randomOffset;
		p.position = randomVec2 + position;

		p.textureID = textureID;
		p.width = width;
		p.height = height;
		particles.push_back(p);
	}
	while (particles.size() > amountParticles) {
		particles.pop_back();
		randomLengths.pop_back();
		randomOffsets.pop_back();
	}
}