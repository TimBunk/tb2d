#include "room.h"

Room::Room(Camera* camera) : Scene::Scene(camera){

}

Room::~Room() {

}

void Room::Update(double deltaTime) {
	this->UpdateChilderen(this, deltaTime);
}

void Room::Reset() {
	for (int i=0;i<entities.size();i++) {
		if (dynamic_cast<B2Entity*>(entities[i]) != NULL) {
			dynamic_cast<B2Entity*>(entities[i])->Reset();
		}
	}
}

void Room::SetActive(bool active) {
	for (int i=0;i<entities.size();i++) {
		if (dynamic_cast<B2Entity*>(entities[i]) != NULL) {
			dynamic_cast<B2Entity*>(entities[i])->SetActive(active);
		}
	}
}
