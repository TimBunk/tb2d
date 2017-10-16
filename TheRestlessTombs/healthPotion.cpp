#include "healthPotion.h"

HealthPotion::HealthPotion(int healing, Camera* camera, Shader* shader) : Potion::Potion(camera, shader) {
	this->healing = healing;
}

HealthPotion::~HealthPotion() {

}

float HealthPotion::Use() {
	std::cout << "You used the health Potion great" << std::endl;
	return healing;
}
