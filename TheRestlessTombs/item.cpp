#include "item.h"

Item::Item(Camera* camera, Shader* shader, b2World* world) : Destructable::Destructable(camera, shader, world) {

}

Item::~Item() {

}

ShowCaseItem Item::PickUp() {
	ShowCaseItem sci;
	sci.w = width;
	sci.h = height;
	sci.texture = texture;
	return sci;
}

