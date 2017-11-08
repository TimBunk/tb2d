#include "gold.h"

Gold::Gold(int value, Camera* camera, Shader* shader, b2World* world) : Item::Item(camera, shader, world) {
	this->value = value;
}

Gold::~Gold() {

}

int Gold::GetGold() {
	// Destroy the gold automatically and returns the value of the gold
	Destroy();
	return value;
}
