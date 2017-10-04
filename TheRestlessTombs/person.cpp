#include "person.h"

Person::Person(Camera* camera, Shader* shader) : B2Entity::B2Entity(camera, shader) {
	this->camera = camera;
	this->shader = shader;
    health = 0;
    damage = 0;
    attackSpeed = 0;
    speed = 0;
}

Person::~Person() {

}

void Person::Update(float deltaTime) {

}
