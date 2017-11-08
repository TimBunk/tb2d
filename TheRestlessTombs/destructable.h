/**
 * @file destructable.h
 *
 * @brief The destructable header file.
 */

#ifndef DESTRUCTABLE_H
#define DESTRUCTABLE_H

#include "b2entity.h"

/**
 * @brief The Destructable class is the main class for all of the B2Entity's that can be destroyed
 */
class Destructable : public B2Entity {
public:
	///< @brief Constructor of the Destructable takes a Camera and Shader that is used for rendering and a B2World for the B2Body
	///< @param camera The reason it takes a camera is for drawing the object with the view and projection matrix that can be received from the camera
	///< @param shader The shahder is used for the drawing and the shader needs atleast to have 3 uniforms matrix4: projection, view and model als the VAO needs to excist of 1. 2Dposition and 2. uv's
	///< @param world The world is need for creating the body and deleting the box2D body
	Destructable(Camera* camera, Shader* shader, b2World* world);

	///< @brief Destructor of the Destructable
	virtual ~Destructable();

	/// @brief Update update function is currently empty it is up to the user to deceide how to use it
	/// @param deltaTime is the time in seconds between 2 frames you can find the deltaTime in the @file window.h class by calling the function GetDeltaTime()
	/// @return void
	virtual void Update(double deltaTime);

	/// @brief Draw draws this Destructable according to the shader and position, angle, scaling of the Entity. (Don't forgot to give it a texture)
	/// @brief NOTE! Whenever the Destructable is not active the draw function will also stop drawing
	/// @return void
	virtual void Draw();

	/// @brief If destroy is called the Destructable will be deactivated and will set it's b2body to not active
	/// @return void
	virtual void Destroy();

	/// @brief If reset is called the Destructable will activated and will set it's b2body to active again.
	/// @return void
	virtual void Reset();

	/// @brief IsAlive check wheter the Destructable is active or not
	/// @return bool It will return true if the Destructable is active
	virtual bool IsAlive();

	/// @brief Is the manual way of setting a this Destructable active or not
	/// @return void
	virtual void SetActive(bool active);
protected:
	bool alive; ///< @brief alive keeps track of if the Destructable is active or not
private:

};

#endif // !DESTRUCTABLE_H
