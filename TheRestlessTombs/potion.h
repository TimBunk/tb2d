/**
 * @file potion.h
 *
 * @brief The potion header file.
 */

#ifndef POTION_H
#define POTION_H

#include "item.h"

/**
 * @brief The Potion class is the base class for all of the Potions
 */
class Potion : public Item {
public:
	///< @brief Constructor of the Potion takes a Camera and Shader that is used for rendering and a B2World for the B2Body
	///< @param camera The reason it takes a camera is for drawing the object with the view and projection matrix that can be received from the camera
	///< @param shader The shader is used for the drawing and the shader needs at least to have 3 uniforms matrix4: projection, view and model als the VAO needs to excist of 1. 2Dposition and 2. uv's
	///< @param world The world is need for creating the body and deleting the box2D body
	Potion(Camera* camera, Shader* shader, b2World* world);

	///< @brief Destructor of the Potion
	virtual ~Potion();

protected:

private:

};

#endif // !POTION_H
