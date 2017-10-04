#include "wall.h"

Wall::Wall(Camera* camera, Shader* shader, bool visible) : B2Entity::B2Entity(camera, shader) {
	this->visible = visible;
}

Wall::~Wall() {

}

void Wall::Update(float deltaTime) {

}
