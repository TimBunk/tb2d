/**
 * @file player.h
 *
 * @brief The player header file.
 */

#ifndef PLAYER_H
#define PLAYER_H

#define _USE_MATH_DEFINES

#include "person.h"
#include "camera.h"
#include "input.h"
#include "hand.h"
#include "renderable.h"
#include "door.h"
#include "weapon.h"
#include "healthPotion.h"
#include "damagePotion.h"
#include "speedPotion.h"
#include "showCase.h"
#include "text.h"
#include "bomb.h"
#include "gold.h"

#include <math.h>
#include <string.h>
#include <iomanip> // setprecision
#include <sstream>
#include <glm-0.9.8.4/glm/gtx/rotate_vector.hpp>

/**
 * @brief The Player class
 */
class Player : public Person {
public:
	/// @brief Constructor of the Person takes a Camera and Shader that is used for rendering and a B2World for the B2Body
	/// @param input The input is required for moving the player and attack with sword
	/// @param rm The ResourceManager is used for getting the right textures and shaders for your person
	/// @param camera The reason it takes a camera is for drawing the object with the view and projection matrix that can be received from the camera
	/// @param shader The shader is used for the drawing and the shader needs at least to have 3 uniforms matrix4: projection, view and model als the VAO needs to excist of 1. 2Dposition and 2. uv's
	/// @param world The world is need for creating the body and deleting the box2D body
    Player(Input* input, ResourceManager* rm, Camera* camera, Shader* shader, b2World* world);

    /// @brief Destructor of the Player
    virtual ~Player();

    /// @brief The Update function updates the player's movement, input, health check for collision in the contacts list etc..
	/// @param deltaTime is the time in seconds between 2 frames you can find the deltaTime in the @file window.h class by calling the function GetDeltaTime()
	/// @return void
    void Update(double deltaTime);

    /// @brief Set the room the player is currently located
    /// @param Number the number of the room
    /// @return void
    void SetRoom(int number);

    /// @brief Get the room the player is currently located in
    /// @return int
    int GetRoom();

    /// @brief AddGold to the player's gold
    /// @param gold The amount of gold the player gets
    /// @return void
    void AddGold(int gold);

    /// @brief Get the amount of gold the player is currently carrying
    /// @return int
    int GetGold();

    /// @brief Giva a item to the player so that the player can use it
    /// @param item The item you want to give
    /// @return void
    void GiveItem(Item* item);

    /// @brief Check if the player already contains a item
    /// @return bool
    bool IsInventoryFull();

    /// @brief upgrade the health of the player by setting a new maxHealth
    /// @param newHealth Is the new max health
    /// @return void
    void UpgradeHealth(int newHealth);

    /// @brief upgrade the speed of the player by setting a new speed
	/// @param newSpeed is the new speed
	/// @return void
    void UpgradeSpeed(float newSpeed);

    /// @brief upgrade the damage of the player by setting a new damage
	/// @param damage Is the new max damage
	/// @return void
    void UpgradeDamage(int newDamage);

    /// @brief Reset all of the values of the player health, items upgrades etc..
    void Reset();

private:
    Input* input; ///< @brief input Is used for handling movement with the keyboard and the sword with the mouse
    Weapon* sword; ///< @brief sword Is the weapon the player uses to defeat the enemy's
    ShowCase* showCase; ///< @brief showCase can visualize the item the player is holding
    Text* textGold; ///< @brief textGold is a text that displays the amount of gold you have
    Text* textStats; ///< @brief textStats is a text that display the values of all the player's stats
    std::vector<Hud*> hudHealth; ///< @brief hudHealth is a list with Hud's that represent the health of the player
    Item* item; ///< @brief item Is the item that the player is holding
    DamageBoost damageBoost; ///< @brief damageBoost Is the damageBoost that can be received by a DamagePotion
    SpeedBoost speedBoost; ///< @brief speedBoost is the SpeedBoost that can be receieved by a SpeedPotion

    int lastHealth; ///< @brief lastHealth Is to check if the lastHealth matches the currentHealth if not then the hudHealth will be updated
    int gold; ///< @brief gold Is the amount of gold the player has at the moment
    float currentDamage; ///< @brief currentDamage Is the current damage the player has
    float currentAttackSpeed; ///< @brief currentAttackSpeed Is the current attackSpeed the player has
    float currentSpeed; ///< @brief currentSpeed Is the current speed the player has
    int currentRoom; ///< @brief currentRoom Is the currentRoom the player is in

    /// @brief UpdateStats update all of the text for the stats that the player currently has
    /// @return void
    void UpdateStats();

    /// @brief CreateLives will create new Hud elements that will represent the health of the player this can be called as many times as you want
    /// @param amount Is the amount of lives there need to be created
    /// @return void
    void CreateLives(int amount);
};

#endif // !PLAYER_H
