/**
 * @file speedPotion.h
 *
 * @brief The speedPotion header file.
 */

#ifndef SPEEDPOTION_H
#define SPEEDPOTION_H

#include "potion.h"

/// @brief SpeedBoost is a boost you can get from a speedPotion and will increase your attackSpeed and movemementSpeed
struct SpeedBoost {
	float movemementSpeed = 0.0f; ///< @brief movemementSpeed The amount of movementSpeed you can get from this SpeedBoost
	float attackSpeed = 0.0f; /// @brief atackSpeed The amount of attackSpeed you can get from this SpeedBoost
	float lifeTime = 0.0f; /// @brief lifeTime Is the amount of time you can use it
	bool active = false; /// @brief active keeps track if the SpeedBoost is still valid to use
};

/**
 * @brief The SpeedPotion class
 */
class SpeedPotion : public Potion {
public:
	/// @brief Constructor of the SpeedPotion takes a Camera and Shader that is used for rendering and a B2World for the B2Body
	/// @param speedBoost The amount of extra movemementSpeed you will get from this SpeedPotion
	/// @param attackSpeedBoost The amount of extra attackSpeed you will get from this SpeedPotion
	/// @param lifeTime The lifeTime of this SpeedPotion
	/// @param camera The reason it takes a camera is for drawing the object with the view and projection matrix that can be received from the camera
	/// @param shader The shader is used for the drawing and the shader needs at least to have 3 uniforms matrix4: projection, view and model als the VAO needs to excist of 1. 2Dposition and 2. uv's
	/// @param world The world is need for creating the body and deleting the box2D body
	SpeedPotion(float speedBoost, float attackSpeedBoost, float lifeTime, Camera* camera, Shader* shader, b2World* world);

	/// @brief Destructor of the SpeedPotion
	virtual ~SpeedPotion();

	/// @brief Whenever you use this SpeedPotion it will return a SpeedBoost with all the needed variables
	/// @return SpeedBoost
	SpeedBoost Use();
private:
	float movementSpeed; ///< @brief movementSpeed The amount of movementSpeed You can get from using this SpeedPotion
	float attackSpeed; ///< @brief attackSpeed The amount of attackSpeed You can get from using this SpeedPotion
	float lifeTime; ///< @brief lifeTime the amount of time you are allowed to use the SpeedPotion
};

#endif // !SPEEDPOTION_H
