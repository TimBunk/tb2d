#include "mirror.h"

Mirror::Mirror(bool rotatable, int width, int height, Texture* texture, Camera * camera, b2World * world) : B2Entity::B2Entity(width, height, glm::vec2(0,0), texture, camera, world)
{
	if (rotatable) {
		rotator = new Rotator(90, 15, glm::vec2(-0.5f, 0.0f), ResourceManager::GetTexture("player"), camera, world);
		rotator->localPosition = glm::vec2(-22, 0);
		rotator->CreateBoxCollider(90, 15, glm::vec2(-0.5f, 0.0f), false, false);
		this->AddChild(rotator);
	}
	else {
		rotator = nullptr;
	}
}

Mirror::~Mirror()
{
	if (rotator != nullptr) {
		delete rotator;
	}
}

void Mirror::Update(double deltaTime)
{
	localAngle = rotator->GetRotation();
}

void Mirror::SetRotation(float degrees)
{
	rotator->SetRotation(degrees);
}
