#ifndef WEAPON_H
#define WEAPON_H

#include "b2entity.h"
#include "camera.h"
#include "shader.h"
#include "debugRenderer.h"
//#include "destructable.h"
#include "crate.h"
#include "lootChest.h"

class Weapon : public B2Entity {
public:
	Weapon(float damage, float swingAngle, float attackDuration, bool belongsToPlayer, Camera* camera, Shader* shader, b2World* world);
	~Weapon();

	void Update(float deltaTime);
	void Draw();

	void CreateBody(int x, int y, int w, int h);
	void FlipBody();
	bool IsFlipped();

	void SetAngle(glm::vec2 angle);
	void SetDamage(float damage);
	void SetAttackDuration(float attackDuration);

	virtual void Attack();
	virtual bool IsAttacking();
	bool Hit();
private:
	bool belongsToPlayer;
	bool flippedBody;
	int w, h;
	glm::vec2 angle2;
	float rotation;

	float timer;
	bool attacking;
	bool hit;

	float damage;
	float attackDuration;
	float swingAngle;
	float currentSwingAngle;

	DebugRenderer* dr;
};

#endif // !WEAPON_H
