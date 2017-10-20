#include "babyOrc.h"

BabyOrc::BabyOrc(Player* player, Camera* camera, Shader* shader, Shader* lineRenderer) : Enemy::Enemy(player, camera, shader, lineRenderer) {
	damage = 1;
	speed = 3.0f;
	attackSpeed = 1.0f;
	health = 1;
}

BabyOrc::~BabyOrc() {

}
