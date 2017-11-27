#include "mirror.h"

Mirror::Mirror(bool rotatable, ResourceManager* rm, Camera * camera, Shader * shader, b2World * world) : B2Entity::B2Entity(camera, shader, world)
{
	if (rotatable) {
		rotator = new Rotator(camera, shader, world);
		rotator->CreateBody(0, -50, 50, 300, glm::vec2(0.0f, 150.0f), true, false, false);
		rotator->GiveTexture(rm->GetTexture("awesome"));
		//this->AddChild(rotator);
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
	//this->localAngle = rotator->localAngle;
	localAngle = rotator->GetAngleB2body();
	rotator->localPosition.x = glm::cos(localAngle);
	rotator->localPosition.y = glm::sin(localAngle);
	rotator->localPosition = glm::normalize(rotator->localPosition);
	rotator->localPosition *= 50.0f;
}
