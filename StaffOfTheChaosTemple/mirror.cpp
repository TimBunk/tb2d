#include "mirror.h"

Mirror::Mirror(bool rotatable, int width, int height, unsigned int textureID, b2World* world) : B2Entity::B2Entity(width, height, textureID, world)
{
	if (rotatable) {
		rotator = new Rotator(90, 15, ResourceManager::GetTexture("rotator")->GetId(), world);
		rotator->localPosition = glm::vec2(-22, 0);
		rotator->SetPivot(glm::vec2(-0.5f, 0.0f));
		rotator->CreateBoxCollider(90, 15, glm::vec2(-0.5f, 0.0f), false, false);
		this->AddChild(rotator);
	}
	else {
		rotator = nullptr;
	}
	notHitableArea = new B2Entity(width + 2, height, 0, world);
	notHitableArea->CreateBoxCollider(width, height + 20, glm::vec2(0, 0), false, false);
	notHitableArea->localPosition.x = -2.0f;
	AddChild(notHitableArea);
}

Mirror::~Mirror()
{
	if (rotator != nullptr) {
		delete rotator;
	}
	delete notHitableArea;
}

void Mirror::Update(double deltaTime)
{
	if (rotator != nullptr) {
		localAngle = rotator->GetRotation();
	}
}

void Mirror::SetRotation(float degrees)
{
	rotator->SetRotation(degrees);
}

void Mirror::SetFilter(unsigned int filter)
{
	this->filter = filter;
	notHitableArea->SetFilter(filter);
	if (rotator != nullptr) {
		rotator->SetFilter(filter);
	}
}
