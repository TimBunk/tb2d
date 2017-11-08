#include "crate.h"

Crate::Crate(Camera* camera, Shader* shader, b2World* world) : Destructable::Destructable(camera, shader, world) {
	// Set the item to a nullptr to avoid conflicts
	item = nullptr;
}

Crate::~Crate() {

}

void Crate::Store(Item* item) {
	// Save the item and make it a child of the crate
	this->item = item;
	this->AddChild(item);
	// Also destroy the item so that it won't be drawn on top of the crate
	item->Destroy();
}

void Crate::Destroy() {
	// Set the crate to not be active and reset the item
	alive = false;
	SetActive(false);
	if (item != nullptr) {
		item->Reset();
	}
}

void Crate::Reset() {
	// Set the crate active again and destroy the item
	alive = true;
	SetActive(true);
	if (item != nullptr) {
		item->Destroy();
	}
}
