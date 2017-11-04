#ifndef SHOP_H
#define SHOP_H

#include "b2entity.h"
#include "scene.h"
#include "button.h"
#include "resourceManager.h"
#include "text.h"
#include "healthPotion.h"
#include "speedPotion.h"
#include "damagePotion.h"
#include "hud.h"

class Player;

class Shop : public B2Entity {
public:
	Shop(Player* player, ResourceManager* rm, Input* input, Camera* camera, Shader* shader, b2World* world);
	~Shop();

	void Update(float deltaTime);
	void Draw();

	void _SetActive(bool active);
	bool IsActive();

	void Reset();
private:
	bool active;
	Player* player;
	Scene* shopWrapper;
	Text* textShop;
	Text* textPlayerUpgrades;
	Text* textItems;
	Text* playerGold;
	Text* playerInventory;
	Button* buttonContinue;

	Button* healthUpgrade;
	int health;
	int costHealthUpgrade;
	int currentHealthUpgrade;
	int maxHealthUpgrades;

	Button* speedUpgrade;
	float speed;
	int costSpeedUpgrade;
	int currentSpeedUpgrade;
	int maxSpeedUpgrades;

	Button* damageUpgrade;
	int damage;
	int costDamageUpgrade;
	int currentDamageUpgrade;
	int maxDamageUpgrades;

	Button* buttonHealthPotion;
	HealthPotion* healthPotion;
	Hud* healthPotionTexture;
	int costHealthPotion;

	Button* buttonSpeedPotion;
	SpeedPotion* speedPotion;
	Hud* speedPotionTexture;
	int costSpeedPotion;

	Button* buttonDamagePotion;
	DamagePotion* damagePotion;
	Hud* damagePotionTexture;
	int costDamagePotion;

	std::string CreateUpgradeText(std::string text, int currentUpgrade, int maxUpgrade, int cost);
};
#endif //!SHOP_H
