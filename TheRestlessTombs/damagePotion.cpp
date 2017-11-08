#include "damagePotion.h"

DamagePotion::DamagePotion(int damageBoost, float lifeTime, Camera* camera, Shader* shader, b2World* world) : Potion::Potion(camera, shader, world) {
	// Save the values received from the constructor
	this->damageBoost = damageBoost;
	this->lifeTime = lifeTime;
	// Set the name of this item to "damage potion"
	name = "damage potion";
}

DamagePotion::~DamagePotion() {

}

DamageBoost DamagePotion::Use() {
	// Create a DamageBoost and return it
	DamageBoost db;
	db.value = damageBoost;
	db.lifeTime = this->lifeTime;
	return db;
}

