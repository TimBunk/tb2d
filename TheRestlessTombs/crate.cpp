#include "crate.h"

Crate::Crate(Camera* camera, Shader* shader, b2World* world) : Destructable::Destructable(camera, shader, world) {
	item = nullptr;
}

Crate::~Crate() {

}

void Crate::Store(Item* item) {
	this->item = item;
	this->AddChild(item);
	item->Destroy();
}

void Crate::Destroy() {
	alive = false;
	SetActive(false);
	if (item != nullptr) {
		item->Reset();
	}
}

void Crate::Reset() {
	alive = true;
	SetActive(true);
	if (item != nullptr) {
		item->Destroy();
	}
}
