#include "item.h"

Item::Item(Camera* camera, Shader* shader, b2World* world) : Destructable::Destructable(camera, shader, world) {
	// Set the name by default as "item"
	name = "item";
}

Item::~Item() {

}

ShowCaseItem Item::PickUp() {
	// Create the ShowCaseItem and return it
	ShowCaseItem sci;
	sci.name = name;
	sci.texture = texture;
	return sci;
}

std::string Item::GetName() {
	// return the name
	return name;
}
