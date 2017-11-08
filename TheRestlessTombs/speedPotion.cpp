#include "speedPotion.h"

SpeedPotion::SpeedPotion(float speedBoost, float attackSpeedBoost, float lifeTime, Camera* camera, Shader* shader, b2World* world) : Potion::Potion(camera, shader, world) {
	// Intialize the variables with the value received from the constructor
	this->movementSpeed = speedBoost;
	this->attackSpeed = attackSpeedBoost;
	this->lifeTime = lifeTime;
	// Name the Item "speed potion"
	name = "speed potion";
}

SpeedPotion::~SpeedPotion() {

}

SpeedBoost SpeedPotion::Use() {
	// Create and return the SpeedBoost
	SpeedBoost sb;
	sb.movemementSpeed = this->movementSpeed;
	sb.attackSpeed = this->attackSpeed;
	sb.lifeTime = this->lifeTime;
	return sb;
}
