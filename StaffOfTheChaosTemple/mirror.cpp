#include "mirror.h"

Mirror::Mirror(bool rotatable, Camera * camera, Shader * shader, b2World * world) : B2Entity::B2Entity(camera, shader, world)
{
	if (rotatable) {
		this->CreateBodyBox(0.0f, 0.0f, 45.0f, 240.0f, glm::vec2(0.0f, 0.0f), false, false, true);
		rotator = new Rotator(camera, shader, world);
		rotator->CreateBodyBox(-22, 0, 90, 15, glm::vec2(45.0f, 0.0f), false, false, true);
		rotator->GiveTexture(ResourceManager::GetTexture("player"));
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
