/**
 * @file bossOrc.h
 *
 * @brief The bossOrc header file.
 */

#ifndef BOSSORC_H
#define BOSSORC_H

#include "boss.h"

/**
 * @brief The BossOrc class
 */
class BossOrc : public Boss {
public:
	/// @brief Constructor of the Boss takes a Camera and Shader that is used for rendering and a B2World for the B2Body
	/// @param nameBoss Is the name that will be displayed when the boss appears
	/// @param player The enemy needs to know of the player so that it always can raycast towards the player
	/// @param lineOfSight is a maximum distance for the raycast
	/// @param rm The ResourceManager is used for getting the right textures and shaders for your person
	/// @param camera The reason it takes a camera is for drawing the object with the view and projection matrix that can be received from the camera
	/// @param shader The shader is used for the drawing and the shader needs at least to have 3 uniforms matrix4: projection, view and model als the VAO needs to excist of 1. 2Dposition and 2. uv's
	/// @param world The world is need for creating the body and deleting the box2D body
	BossOrc(std::string nameBoss, Player* player, float lineOfSight, ResourceManager* rm, Camera* camera, Shader* shader, b2World* world);

	/// @brief Destructor of the BossOrc
	~BossOrc();

	/// @brief Update makes a call to LookForPlayer and also makes sure the weapon is used right
	/// @param deltaTime is the time in seconds between 2 frames you can find the deltaTime in the @file window.h class by calling the function GetDeltaTime()
	/// @return void
	void Update(double deltaTime);

	/// @brief LookForPlayer looks for the player and at the same times takes care of doing the BossOrc's special ability
	/// @param deltaTime is the time in seconds between 2 frames you can find the deltaTime in the @file window.h class by calling the function GetDeltaTime()
	/// @return bool
	bool LookForPlayer(double deltaTime);

	/// @brief Apply damage to a person the damage goes minus the health
	/// @param damage The amount of damage the person will take the damage goes minus the health
	/// @return void
	void TakeDamage(int damage);

	/// @brief Reset the BossOrc to it's begin values
	/// @return void
	void Reset();
private:
	Weapon* hammer; ///< @brief hammer Is the weapon the BossOrc has

	float timer; ///< @brief timer Is the timer that counts towards specialAbilityCooldown and once reached the special ability will be true
	float specialAbilityCooldown; ///< @brief specialAbilityCooldown is the cooldown for using the specialAbility
	float specialAbilityTimer; ///< @brief specialAbilityTimer is the timer that counts towards the specialabilityCooldown is the duration timer of the special ability and once reached the special ability will be false
	bool specialAbility; ///< @brief specialAbility True means that the specialAbility is active
	b2Vec2 specialAttackDirection; ///< @brief specialAttackDirection Is the last direction of the player where the BossOrc has been seen and charges in that direction
	float originalSpeed; ///< @brief orginalSpeed Is the orginalSpeed that is not affect by the specialAbility of the BossOrc
};

#endif //!BOSSORC_H
