#include "damagePotion.h"

DamagePotion::DamagePotion(int damageBoost, float lifeTime, Camera* camera, Shader* shader, b2World* world) : Potion::Potion(camera, shader, world) {
	this->damageBoost = damageBoost;
	this->lifeTime = lifeTime;
}

DamagePotion::~DamagePotion() {

}

DamageBoost DamagePotion::Use() {
	DamageBoost db;
	db.value = damageBoost;
	db.lifeTime = this->lifeTime;
	return db;
}

