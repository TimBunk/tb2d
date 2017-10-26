#ifndef ENEMY_H
#define ENEMY_H

#include "person.h"
#include "player.h"
#include "rayCastCallBack.h"

class Enemy : public Person {
public:
	Enemy(Player* player, float lineOfSight, ResourceManager* rm, Camera* camera, Shader* shader, b2World* world);
	~Enemy();

	virtual void CreateBody(int x, int y, int w, int h);
protected:
	Player* player;
	glm::vec3 playerLastLocation;
	float distancePlayer;
	float lineOfSight;

	glm::vec3 spawnPosition;
	float minimalRange;

	virtual bool LookForPlayer(float deltaTime);
	bool ShootRaycast();
private:
	RayCastCallBack* raycast;
};

#endif // !ENEMY_H
