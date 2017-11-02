#ifndef SHOP_H
#define SHOP_H

#include "b2entity.h"
#include "scene.h"
#include "button.h"
#include "resourceManager.h"
#include "text.h"

class Player;

class Shop : public B2Entity {
public:
	Shop(Player* player, ResourceManager* rm, Input* input, Camera* camera, Shader* shader, b2World* world);
	~Shop();

	void Update(float deltaTime);
	void Draw();

	void _SetActive(bool active);
	bool IsActive();
private:
	bool active;
	Player* player;
	Scene* shopWrapper;
	Text* textShop;
	Text* textPlayerUpgrades;
	Text* textItems;
	Button* healthUpgrade;
	Button* speedUpgrade;
	Button* damageUpgrade;
	Button* buttonContinue;

	int health;
	int costHealthUpgrade;
	int currentHealthUpgrade;
	int maxHealthUpgrades;
	float speed;
	int costSpeedUpgrade;
	int currentSpeedUpgrade;
	int maxSpeedUpgrades;
	int damage;
	int costDamageUpgrade;
	int currentDamageUpgrade;
	int maxDamageUpgrades;

	std::string CreateUpgradeText(std::string text, int currentUpgrade, int maxUpgrade, int cost);
};
#endif //!SHOP_H
