#include "potion.h"

Potion::Potion(Camera* camera, Shader* shader, b2World* world) : Item::Item(camera, shader, world) {
	alive = true;
}

Potion::~Potion() {

}
