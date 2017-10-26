#include "gold.h"

Gold::Gold(int value, Camera* camera, Shader* shader) : Destructable::Destructable(camera, shader) {
	this->value = value;
}

Gold::~Gold() {

}

int Gold::GetGold() {
	Destroy();
	return value;
}
