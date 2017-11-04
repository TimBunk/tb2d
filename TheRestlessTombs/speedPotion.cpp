#include "speedPotion.h"

SpeedPotion::SpeedPotion(float speedBoost, float attackSpeedBoost, float lifeTime, Camera* camera, Shader* shader, b2World* world) : Potion::Potion(camera, shader, world) {
	this->movementSpeed = speedBoost;
	this->attackSpeed = attackSpeedBoost;
	this->lifeTime = lifeTime;
	name = "speed potion";
}

SpeedPotion::~SpeedPotion() {

}

SpeedBoost SpeedPotion::Use() {
	SpeedBoost sb;
	sb.movemementSpeed = this->movementSpeed;
	sb.attackSpeed = this->attackSpeed;
	sb.lifeTime = this->lifeTime;
	return sb;
}
