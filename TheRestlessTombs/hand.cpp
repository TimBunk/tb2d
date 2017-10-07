#include "hand.h"

Hand::Hand(Camera* camera, Shader* shader) : B2Entity(camera, shader) {

}

Hand::~Hand() {

}

void Hand::Update(float deltaTime) {
	body->SetTransform(b2Vec2(this->GetGlobalPosition().x * Window::p2m, this->GetGlobalPosition().y * Window::p2m), this->GetAngle());
}
