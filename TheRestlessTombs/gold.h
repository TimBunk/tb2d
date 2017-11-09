/**
 * @file gold.h
 *
 * @brief The gold header file.
 */

#ifndef GOLD_H
#define GOLD_H

#include "item.h"

/**
 * @brief The gold class
 */
class Gold : public Item {
public:
	///< @brief Constructor of the Gold takes a Camera and Shader that is used for rendering and a B2World for the B2Body
	///< @param camera The reason it takes a camera is for drawing the object with the view and projection matrix that can be received from the camera
	///< @param shader The shader is used for the drawing and the shader needs at least to have 3 uniforms matrix4: projection, view and model als the VAO needs to excist of 1. 2Dposition and 2. uv's
	///< @param world The world is need for creating the body and deleting the box2D body
	Gold(int value, Camera* camera, Shader* shader, b2World* world);

	///< @brief Destructor of the Gold
	~Gold();

	/// @brief returns the amount of gold and will automatically destroy the gold you can also reset it by calling Reset()
	int GetGold();
private:
	int value; ///< @brief The amount of gold you get for picking this gold up
};

#endif //!GOLD_H
