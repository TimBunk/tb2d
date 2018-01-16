#include "mirror.h"

Mirror::Mirror(bool rotatable, int width, int height, unsigned int textureID, b2World* world) : B2Entity::B2Entity(width, height, textureID, world)
{
	rotator = nullptr;
	Rotatable(rotatable);
}

Mirror::~Mirror()
{
	if (rotator != nullptr) {
		delete rotator;
	}
}

void Mirror::Update(double deltaTime)
{
	if (rotator != nullptr) {
		localAngle = rotator->GetRotation();
	}
}

void Mirror::SetRotation(float degrees)
{
	if (rotator == nullptr) { return; }
	rotator->SetRotation(degrees);
}

void Mirror::Rotatable(bool boolean)
{
	if (rotator != nullptr) {
		this->RemoveChild(rotator);
		delete rotator;
		rotator = nullptr;
	}
	if (boolean) {
		rotator = new Rotator(250, 250, ResourceManager::GetTexture("rotator")->GetId(), world);
		rotator->localPosition = glm::vec2(15, 5);
		rotator->SetPivot(glm::vec2(-0.5f, 0.0f));
		rotator->CreateBoxCollider(90, 15, glm::vec2(-0.15f, 0.0f), false, false);
		this->AddChild(rotator);
	}
}

bool Mirror::IsRotatable()
{
	if (rotator == nullptr) {
		return false;
	}
	return true;
}

void Mirror::SetFilter(unsigned int filter)
{
	this->filter = filter;
	if (rotator != nullptr) {
		rotator->SetFilter(filter);
	}
}
