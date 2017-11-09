/**
 * @file weapon.h
 *
 * @brief The weapon header file.
 */

#ifndef WEAPON_H
#define WEAPON_H

#include "b2entity.h"
#include "camera.h"
#include "shader.h"
#include "debugRenderer.h"
#include "crate.h"
#include "lootChest.h"
#include "shop.h"

/**
 * @brief The Weapon class
 */
class Weapon : public B2Entity {
public:
	/// @brief Constructor of the Weapon takes a Camera and Shader that is used for rendering and a B2World for the B2Body
	/// @param damage Is the amount of damage a weapon can do
	/// @param swingAngle Is in how far the angle swings on a attack
	/// @param attackDuration Is the duration of the swing
	/// @param belongsToPlayer If true that means the weapon is for the player otherwise it is for a enemy we need to know this so we can trigger the right events
	/// @param camera The reason it takes a camera is for drawing the object with the view and projection matrix that can be received from the camera
	/// @param shader The shader is used for the drawing and the shader needs at least to have 3 uniforms matrix4: projection, view and model als the VAO needs to excist of 1. 2Dposition and 2. uv's
	/// @param world The world is need for creating the body and deleting the box2D body
	Weapon(float damage, float swingAngle, float attackDuration, bool belongsToPlayer, Camera* camera, Shader* shader, b2World* world);

	/// @brief Destructor of the Weapon
	virtual ~Weapon();

	/// @brief Update update function is currently empty it is up to the user to deceide how to use it
	/// @param deltaTime is the time in seconds between 2 frames you can find the deltaTime in the @file window.h class by calling the function GetDeltaTime()
	/// @return void
	void Update(double deltaTime);

	/// @brief Create a body and add it to the b2World
	/// @param x The x position
	/// @param y The y position
	/// @param w The width of the box2D body
	/// @param h The height of the box2D body
	/// @return void
	void CreateBody(int x, int y, int w, int h);

	/// @brief Flip the uv coordinates of the body
	/// @return void
	void FlipBody();

	/// @brief Check if the body is already flipped if so return true
	/// @return bool
	bool IsFlipped();

	/// @brief Sets the angle of the Weapon
	/// @param angle Is the new angle for the sword
	/// @return void
	void SetAngle(glm::vec2 angle);

	/// @brief Set the damage of the Weapon
	/// @param damage The amount of damage that the Weapon can deal
	/// @return void
	void SetDamage(float damage);

	/// @brief Sets the attack duration of a swing
	/// @param attackDuration Is the new attackDuration of a swing of the Weapon
	/// @return void
	void SetAttackDuration(float attackDuration);

	/// @brief Start swinging the sword and try to hit something with it
	/// @return void
	virtual void Attack();

	/// @brief Check if the sword is currently attacking
	/// @return bool
	virtual bool IsAttacking();

	/// @brief If the sword hitted something Hit() wil return true
	/// @return bool
	bool Hit();
private:
	bool belongsToPlayer; ///< @brief belongsToPlayer Is a boolean that keeps track from who the Weapon is, if true it means the Weapon belongs to a player otherwise to a Enemy
	bool flippedBody; ///< @brief flippedBody Is a boolean that tells you if the uv's are flipped
	float rotation; ///< @brief rotation Is the rotation that we get from a vector2 inside the SetAngle()

	float timer; ///< @brief timer Is a timer for when the Weapon can be swinged
	bool attacking; ///< @brief attacking Is a boolean that keeps track of if the user is attacking
	bool hit; ///< @brief hit Is a boolean that returns true whenever something got hit by the Weapon

	float damage; ///< @brief damage Is the amount of damage a Weapon can do
	float attackDuration; ///< @brief attackDuration Is the duration of a swing with the Weapon
	float swingAngle; ///< @brief swingAngle Is the angle of the swing in degrees
	float currentSwingAngle; ///< @brief currentSwingAngle keeps track of where the swing currently is

	DebugRenderer* dr; ///< @brief dr Is a debugRendere that can be used to visualize the collider of the weapon
};

#endif // !WEAPON_H
