#include "mirror.h"

Mirror::Mirror(bool rotatable, int width, int height, unsigned int textureID, b2World* world) : B2Entity::B2Entity(width, height, textureID, world)
{
	// Initialize variables
	rotator = nullptr;
	Rotatable(rotatable);
}

Mirror::~Mirror()
{
	// Delete the rotator if it was created
	if (rotator != nullptr) {
		delete rotator;
	}
}

void Mirror::Update(double deltaTime)
{
	// Update the angle by the rotation of the rotator
	if (rotator != nullptr) {
		localAngle = rotator->GetRotation();
	}
}

void Mirror::SetRotation(float degrees)
{
	if (rotator == nullptr) { return; }
	// Set the rotation of the rotator
	rotator->SetRotation(degrees);
}

void Mirror::Rotatable(bool boolean)
{
	// If a rotator already exist remove it
	if (rotator != nullptr) {
		this->RemoveChild(rotator);
		delete rotator;
		rotator = nullptr;
	}
	// Create a new rotator
	if (boolean) {
		rotator = new Rotator(70, 25, ResourceManager::GetTexture("rotator")->GetId(), world);
		rotator->SetColor(glm::vec4(0, 0, 0, 1));
		rotator->localPosition = glm::vec2(15, 5);
		rotator->SetPivot(glm::vec2(-1.1f, 0.0f));
		rotator->CreateBoxCollider(70, 25, glm::vec2(-1.1f, 0.0f), false, false);
		this->AddChild(rotator);
	}
}

bool Mirror::IsRotatable()
{
	// Check if it has a rotator
	if (rotator == nullptr) {
		return false;
	}
	return true;
}
