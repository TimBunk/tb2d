#include "healthPotion.h"

HealthPotion::HealthPotion(int healing, Camera* camera, Shader* shader, b2World* world) : Potion::Potion(camera, shader, world) {
	this->healing = healing;
}

HealthPotion::~HealthPotion() {

}

float HealthPotion::Use() {
	return healing;
}
