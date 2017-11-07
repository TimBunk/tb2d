#ifndef ENEMY_H
#define ENEMY_H

#include "player.h"
#include "rayCastCallBack.h"
#include "item.h"

class Enemy : public Person {
public:
	Enemy(Player* player, float lineOfSight, ResourceManager* rm, Camera* camera, Shader* shader, b2World* world);
	~Enemy();

	void GiveItem(Item* item);
	virtual void CreateBody(int x, int y, int w, int h);
protected:
	Player* player;
	glm::vec3 playerLastLocation;
	float distancePlayer;
	float lineOfSight;

	glm::vec3 spawnPosition;
	float minimalRange;

	Item* item;

	virtual bool LookForPlayer();
	bool ShootRaycast();

	virtual void SetActive(bool active);
private:
	RayCastCallBack* raycast;
};

#endif // !ENEMY_H
