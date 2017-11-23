#include "laser.h"
#include "player.h"

Laser::Laser(Shader* debug, Camera * camera, Shader * shader, b2World * world) : B2Entity::B2Entity(camera, shader, world)
{
	raycast = new RaycastCallBack();
	raycast->CreateLine(500.0f, 50.0f, camera, debug, glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
}

Laser::~Laser()
{
	delete raycast;
}

void Laser::Update(glm::vec2 direction)
{
	// Draw the ray's direction and length
	raycast->ChangeColor(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
	raycast->Draw(this->GetGlobalPosition(), glm::atan(-direction.y, -direction.x));

	// Shoot raycast
	b2Vec2 destination = b2Vec2((this->GetGlobalPosition().x + direction.x) * p2m, (this->GetGlobalPosition().y + direction.y) * p2m);
	world->RayCast(raycast, b2Vec2(this->GetGlobalPosition().x * p2m, this->GetGlobalPosition().y * p2m), destination);
	RaycastOutput ro = raycast->GetOutput();
	if (ro.fixture != nullptr && static_cast<B2Entity*>(ro.fixture->GetUserData()) != NULL) {
		// intersectionPoint is a vector that points towards the hitted point and is also the length between the ray starting point and the hitted point
		b2Vec2 intersectionPoint = (b2Vec2(this->GetGlobalPosition().x * p2m, this->GetGlobalPosition().y * p2m) - destination);
		intersectionPoint *= ro.fraction;
		// Calculation reflection = d-(2*dot(d-n)*n)
		b2Vec2 reflection = intersectionPoint - (2 * b2Dot(intersectionPoint, ro.normal) * ro.normal);
		// Draw the reflection
		raycast->ChangeColor(glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));
		raycast->Draw(glm::vec2(ro.point.x * m2p, ro.point.y * m2p), glm::atan(reflection.y, reflection.x));

		// Draw the normal
		raycast->ChangeColor(glm::vec4(0.0f, 1.0f, 0.0f, 1.0f));
		raycast->Draw(glm::vec2((ro.point.x + ro.normal.x) * m2p, (ro.point.y + ro.normal.y) * m2p), glm::atan(ro.normal.y, ro.normal.x));
	}
}
