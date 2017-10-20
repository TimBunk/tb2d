#include "speedPotion.h"

SpeedPotion::SpeedPotion(float speedBoost, float attackSpeedBoost, float lifeTime, Camera* camera, Shader* shader) : Potion::Potion(camera, shader) {
	this->movementSpeed = speedBoost;
	this->attackSpeed = attackSpeedBoost;
	this->lifeTime = lifeTime;
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
