#include "damagePotion.h"

DamagePotion::DamagePotion(int damageBoost, float lifeTime, Camera* camera, Shader* shader) : Potion::Potion(camera, shader) {
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

