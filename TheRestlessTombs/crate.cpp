#include "crate.h"

Crate::Crate(Camera* camera, Shader* shader, b2World* world) : Destructable::Destructable(camera, shader, world) {
	potion = nullptr;
}

Crate::~Crate() {

}

void Crate::Store(Potion* potion) {
	this->potion = potion;
	potion->Destroy();
}

void Crate::Destroy() {
	alive = false;
	SetActive(false);
	if (potion != nullptr) {
		potion->Reset();
	}
}

void Crate::Reset() {
	alive = true;
	SetActive(true);
	if (potion != nullptr) {
		potion->Destroy();
	}
}
