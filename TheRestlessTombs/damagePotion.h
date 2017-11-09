/**
 * @file damagePotion.h
 *
 * @brief The damagePotion header file.
 */

#ifndef DAMAGEPOTION_H
#define DAMAGEPOTION_H

#include "potion.h"

/// @brief The DamageBoost struct is usefull for the player when he uses a DamagePotion he automatically gets all of the values delivered
struct DamageBoost {
	int value = 1; ///< @brief value can be used for the amount of extra damage you will get from this DamageBoost
	float lifeTime = 0.0f; ///< @brief lifeTime is the lifeTime of the boost
	bool active = false; ///< @brief active is a boolean that keeps track if the DamageBoost is active or not
};

/**
 * @brief The DamagePotion class
 */
class DamagePotion : public Potion {
public:
	///< @brief Constructor of the B2Entity takes a Camera and Shader that is used for rendering and a B2World for the B2Body
	///< @param damageBoost the amount of extra damage that the user will receive
	///< @param lifeTime the The time that the DamagePotion will affect the user
	///< @param camera The reason it takes a camera is for drawing the object with the view and projection matrix that can be received from the camera
	///< @param shader The shader is used for the drawing and the shader needs atleast to have 3 uniforms matrix4: projection, view and model als the VAO needs to excist of 1. 2Dposition and 2. uv's
	///< @param world The world is need for creating the body and deleting the box2D body
	DamagePotion(int damageBoost, float lifeTime, Camera* camera, Shader* shader, b2World* world);

	///< @brief Destructor of the DamagePotion
	~DamagePotion();

	/// @brief Whenever you use the DamagePotion you will receive a struct with all of the values then it us up to the user to make sure the values are used right
	/// @return DamageBoost
	DamageBoost Use();
private:
	int damageBoost; ///< @brief The amount of extra damage
	float lifeTime; ///< @brief The lifeTime of the DamagePotion
};

#endif // !DAMAGEPOTION_H
