#include "healthPotion.h"

HealthPotion::HealthPotion(int healing, Camera* camera, Shader* shader, b2World* world) : Potion::Potion(camera, shader, world) {
	// Intialize the healing with the healing from the constructor
	this->healing = healing;
	// Name the Item "health potion"
	name = "health potion";
}

HealthPotion::~HealthPotion() {

}

int HealthPotion::Use() {
	// return the healing
	return healing;
}
