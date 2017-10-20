#ifndef ENEMY_H
#define ENEMY_H

#include "person.h"
#include "player.h"
#include "rayCastCallBack.h"

class Enemy : public Person {
public:
	Enemy(Player* player, Camera* camera, Shader* shader, Shader* lineRenderer);
	~Enemy();

	void Update(float deltaTime);

	void CreateBody(int x, int y, int w, int h, b2World* world);
private:
	RayCastCallBack* raycast;
	Player* player;
};

#endif // !ENEMY_H
