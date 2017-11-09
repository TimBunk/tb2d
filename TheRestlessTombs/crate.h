/**
 * @file crate.h
 *
 * @brief The crate header file.
 */

#ifndef CRATE_H
#define CRATE_H

#include "item.h"

/**
 * @brief The Crate class
 */
class Crate : public Destructable {
public:
	///< @brief Constructor of the Crate takes a Camera and Shader that is used for rendering and a B2World for the B2Body
	///< @param camera The reason it takes a camera is for drawing the object with the view and projection matrix that can be received from the camera
	///< @param shader The shahder is used for the drawing and the shader needs atleast to have 3 uniforms matrix4: projection, view and model als the VAO needs to excist of 1. 2Dposition and 2. uv's
	///< @param world The world is need for creating the body and deleting the box2D body
	Crate(Camera* camera, Shader* shader, b2World* world);

	///< @brief Destructor of the Crate
	~Crate();

	/// @brief The store function saves the item as a child of the crate and also Destroys the item so that it won't be drawn over the Crate
	/// @param item The item you want to save as a child in the Crate
	/// @return void
	void Store(Item* item);

	/// @brief Destroy's the crate(meaning it won't be visible and the body won't be active) but reset's the item.
	/// @param item The item you want to save as a child in the Crate
	/// @return void
	void Destroy();

	/// @brief Reset's the crate(meaning it will be visible again and the body' is active again) but the Item will be destroyed.
	void Reset();

private:
	Item* item; ///< @brief item is the item given by Store()
};

#endif // !CRATE_H
