#include "staff.h"

Staff::Staff(b2World* world, ResourceManager* rm, int width, int height, Texture* texture, Shader* shader, Camera* camera) : Sprite::Sprite(width, height, texture, shader, camera, false)
{
	this->rm = rm;
	laser = new Laser(rm->GetShader("debug"), camera, shader, world);
	this->AddChild(laser);
}

Staff::~Staff()
{
	//delete laser;
}

void Staff::Update(double deltaTime)
{
	float tmpAngle = GetGlobalAngle() +(90.0f * M_PI / 180.0f);
	glm::vec2 tmpDirection;
	tmpDirection.x = glm::cos(tmpAngle);
	tmpDirection.y = glm::sin(tmpAngle);
	tmpDirection = glm::normalize(tmpDirection);
	tmpDirection *= 500.0f;
	tmpDirection = tmpDirection * -1.0f;
	//std::cout << "direction.x = " << tmpDirection.x << " direction.y = " << tmpDirection.y << std::endl;
	laser->Update(tmpDirection);
}

