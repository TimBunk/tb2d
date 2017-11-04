#include "item.h"

Item::Item(Camera* camera, Shader* shader, b2World* world) : Destructable::Destructable(camera, shader, world) {
	name = "item";
}

Item::~Item() {

}

ShowCaseItem Item::PickUp() {
	ShowCaseItem sci;
	sci.name = name;
	sci.texture = texture;
	return sci;
}

std::string Item::GetName() {
	return name;
}
