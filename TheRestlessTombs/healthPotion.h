/**
 * @file healthPotion.h
 *
 * @brief The healthPotion header file.
 */

#ifndef HEALTHPOTION_H
#define HEALTHPOTION_H

#include "potion.h"

/**
 * @brief The healthPotion class is inherit by Potion
 */
class HealthPotion : public Potion {
public:
	/// @brief Constructor of the B2Entity takes a Camera and Shader that is used for rendering and a B2World for the B2Body
	/// @brief healing The amount of healing you will get from using this HealthPotion
	/// @param camera The reason it takes a camera is for drawing the object with the view and projection matrix that can be received from the camera
	/// @param shader The shader is used for the drawing and the shader needs at least to have 3 uniforms matrix4: projection, view and model als the VAO needs to excist of 1. 2Dposition and 2. uv's
	/// @param world The world is need for creating the body and deleting the box2D body
	HealthPotion(int healing, Camera* camera, Shader* shader, b2World* world);

	/// @brief Destructor of the HealthPotion
	~HealthPotion();

	/// @brief Whenever you Use the HealthPotion it will return the amount of healing
	/// @return float
	int Use();
private:
	int healing; ///< @brief healing The amount of healing you can get of the HealthPotion
};

#endif // !HEALTHPOTION_H
