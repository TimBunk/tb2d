#include "crate.h"

Crate::Crate(Camera* camera, Shader* shader) : Destructable::Destructable(camera, shader) {

}

Crate::~Crate() {

}

void Crate::Update(float deltaTime) {

}

void Crate::Destroy() {
	alive = false;
	SetActive(false);
}

void Crate::Reset() {
	alive = true;
	SetActive(true);
}
