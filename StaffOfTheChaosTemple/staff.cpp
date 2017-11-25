#include "staff.h"

Staff::Staff(b2World* world, ResourceManager* rm, int width, int height, Texture* texture, Shader* shader, Camera* camera) : Sprite::Sprite(texture, shader, camera, false)
{
	this->rm = rm;
	laser = new Laser(world, rm->GetShader("debug"), 500.0f, rm->GetTexture("awesome"), shader, camera, false);
	this->AddChild(laser);
	this->CreateBody(height, width, glm::vec2(0.0f, 0.0f));
}

Staff::~Staff()
{
	delete laser;
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
	laser->SetDirection(tmpDirection);
	//laser->Update(tmpDirection);
}

