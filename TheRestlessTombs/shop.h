/**
 * @file shop.h
 *
 * @brief The shop header file.
 */

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

/**
 * @brief The Shop class
 */
class Shop : public B2Entity {
public:
	/// @brief Constructor of the Shop takes a Camera and Shader that is used for rendering and a B2World for the B2Body
	/// @param player The player is required in order to upgrade him
	/// @param rm The resourceManager in order to get all of the right textures
	/// @param input The input is needed because we are using buttons in the Shop
	/// @param camera The reason it takes a camera is for drawing the object with the view and projection matrix that can be received from the camera
	/// @param shader The shader is used for the drawing and the shader needs at least to have 3 uniforms matrix4: projection, view and model als the VAO needs to excist of 1. 2Dposition and 2. uv's
	/// @param world The world is need for creating the body and deleting the box2D body
	Shop(Player* player, ResourceManager* rm, Input* input, Camera* camera, Shader* shader, b2World* world);

	/// @brief Destructor of the Shop
	virtual ~Shop();

	/// @brief Update update function is currently empty it is up to the user to deceide how to use it
	/// @param deltaTime is the time in seconds between 2 frames you can find the deltaTime in the @file window.h class by calling the function GetDeltaTime()
	/// @return void
	void Update(double deltaTime);

	/// @brief Draw draws this Shop according to the shader and position, angle, scaling of the Entity. (Don't forgot to give it a texture)
	/// @return void
	void Draw();

	/// @brief _SetActive Sets the shop overlay active or not
	/// @param active Deceides wheter the shop overlay is visible or not
	/// @return void
	void _SetActive(bool active);

	/// @brief returns a bool that is true whenever the shop overlay is active
	/// @return bool
	bool IsActive();

	/// @brief Resets the shop and all of the upgrades that it sells
	void Reset();
private:
	bool active; ///< @brief active Is if the shop overlay is active or not
	Player* player; ///< @brief player We need to keep a reference to the player to upgrade him
	Scene* shopWrapper; ///< @brief shopWrapper is a scene for the shop overlay
	Text* textShop; ///< @brief textShop Is a text that says shop
	Text* textPlayerUpgrades; ///< @brief textPlayerUpgrades Is a text that says upgrades
	Text* textItems; ///< @brief textItems Is a text that says items
	Text* playerGold; ///< @brief playerGold Displays the gold of the player
	Text* playerInventory; ///< @brief playerInventory Is a text that says if the inventory of the player is full or not
	Button* buttonContinue; ///< @brief buttonContinue Is a button that when pressed you leave the shop overlay

	Button* healthUpgrade; ///< @brief healthUpgrade Is a button that can upgrade the health of the player
	int health; ///< @brief health Is the health that the upgrade is currently at
	int costHealthUpgrade; ///< @brief costHealthUpgrade The cost of the health upgrade
	int currentHealthUpgrade; ///< @brief currentHealthUpgrade is the currentUpgrade you are on
	int maxHealthUpgrades; ///< @brief maxHealthUpgrades Is the maximum allowed of health upgrades

	Button* speedUpgrade; ///< @brief speedUpgrade Is a button that can upgrade the speed of the player
	float speed; ///< @brief speed Is the speed that the upgrade is currently at
	int costSpeedUpgrade; ///< @brief costSpeedUpgrade The cost of the speed upgrade
	int currentSpeedUpgrade; ///< @brief currentSpeedUpgrade is the currentUpgrade you are on
	int maxSpeedUpgrades; ///< @brief maxSpeedUpgrades Is the maximum allowed of speed upgrades

	Button* damageUpgrade; ///< @brief damageUpgrade Is a button that can upgrade the damage of the player
	int damage; ///< @brief damage Is the damage that the upgrade is currently at
	int costDamageUpgrade; ///< @brief costDamageUpgrade The cost of the damage upgrade
	int currentDamageUpgrade; ///< @brief currentDamageUpgrade is the currentUpgrade you are on
	int maxDamageUpgrades; ///< @brief maxDamageUpgrades Is the maximum allowed of damage upgrades

	Button* buttonHealthPotion; ///< @brief buttonHealthPotion Is a button that when pressed you get a healthPotion at cost of gold
	HealthPotion* healthPotion; ///< @brief healthPotion Is the healthPotion you will receive once you buy it
	Hud* healthPotionTexture; ///< @brief healthPotionTexture Is a texture that display what the Item looks likes
	int costHealthPotion; ///< @brief costHealthPotion Is the cost of this Item

	Button* buttonSpeedPotion; ///< @brief buttonSpeedPotion Is a button that when pressed you get a speedPotion at cost of gold
	SpeedPotion* speedPotion; ///< @brief speedPotion Is the speedPotion you will receive once you buy it
	Hud* speedPotionTexture; ///< @brief speedPotionTexture Is a texture that display what the Item looks likes
	int costSpeedPotion; ///< @brief costSpeedPotion Is the cost of this Item

	Button* buttonDamagePotion;  ///< @brief buttonDamagePotion Is a button that when pressed you get a DamagePotion at cost of gold
	DamagePotion* damagePotion; ///< @brief damagePotion Is the damagePotion you will receive once you buy it
	Hud* damagePotionTexture; ///< @brief damagePotionTexture Is a texture that display what the Item looks likes
	int costDamagePotion; ///< @brief costDamagePotion Is the cost of this Item

	/// @brief CreateUpgradeText returns a standard text for a upgrade
	/// @param text Is the text of what the upgrade is/does
	/// @param currentUpgrade Is the currentUpgrade of the upgrade
	/// @param maxUpgrade Is the maximum amount of upgrades
	/// @param cost Is the cost of the upgrade
	/// @return std::string
	std::string CreateUpgradeText(std::string text, int currentUpgrade, int maxUpgrade, int cost);
};
#endif //!SHOP_H
