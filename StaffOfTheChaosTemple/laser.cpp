#include "laser.h"
#include "mirror.h"
#include "person.h"

Laser::Laser(float damage, int width, int height, unsigned int textureID, b2World* world) : Sprite::Sprite(width, height, textureID)
{
	this->damage = damage;
	raycast = new Raycast(world);
	pr = RenderManager::GetParticleRenderer("particle");
	particleTextureID = ResourceManager::GetTexture("laserParticle")->GetId();
	color = glm::vec4(0.6f, 0.9f, 0.84f, 1);
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
			SpawnParticles();
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
			SpawnParticles();
			return;
		}
		// HIT B2ENTITY
		else {
			// Scale the laser by the distance of hit
			localScale.y = rh.fraction;
			hit = false;
			hitPosition = rh.point;
			reflection = glm::vec2();
			SpawnParticles();
			return;
		}
	}
	localScale.y = 1.0f;
	hit = false;
	hitPosition = destination;
	reflection = glm::vec2();
}

void Laser::Draw()
{
	if (renderer != nullptr) {
		renderer->Submit(this);
	}
}

void Laser::DrawParticles(double deltaTime)
{
	for (int i = 0;i < particles.size(); ) {
		particles[i].color.a -= deltaTime;
		glm::vec2 velocity = particles[i].direction;
		velocity *= deltaTime;
		particles[i].position += velocity;
		if (particles[i].color.a <= 0) {
			particles.erase(particles.begin() + i);
		}
		else {
			pr->Submit(particles[i]);
			i++;
		}
	}
}

void Laser::SpawnParticles()
{
	for (int i = particles.size(); i < 100; i++) {
		Particle p;
		p.angle = (((float)(std::rand() % (int)((float)M_PI * 2 * 1000.0f))) / 1000.0f);
		p.textureID = particleTextureID;
		p.color = glm::vec4(0, 0, 0, ((float)(std::rand() % 2000)) / 1000.0f);
		p.width = 32;
		p.height = 32;
		p.position = hitPosition;
		float _angle = localAngle + glm::radians(90.0f);
		_angle += (((float)(std::rand() % (int)((float)M_PI * 1000.0f))) - (float)M_PI_2 * 1000.0f) / 1000.0f;
		glm::vec2 _direction = glm::vec2(glm::cos(_angle), glm::sin(_angle));
		p.direction = _direction;
		p.direction = glm::normalize(p.direction);
		p.direction *= 10.0f + ((float)(std::rand() % 40));
		particles.push_back(p);
	}
}
