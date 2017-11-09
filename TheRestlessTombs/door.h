/**
 * @file door.h
 *
 * @brief The door header file.
 */

#ifndef DOOR_H
#define DOOR_H

#include "b2entity.h"
#include "player.h"

///< @brief Direction represents the direction of the Door
enum Direction {
	north,
	east,
	south,
	west
};

/**
 * @brief The Door class
 */
class Door : public B2Entity {
public:
	/// @brief Constructor of the Door takes a Camera and Shader that is used for rendering and a B2World for the B2Body
	/// @param roomNumber Is the number of the room this Door leads to
	/// @param direction Is the direction this door is facing
	/// @param camera The reason it takes a camera is for drawing the object with the view and projection matrix that can be received from the camera
	/// @param shader The shader is used for the drawing and the shader needs at least to have 3 uniforms matrix4: projection, view and model als the VAO needs to excist of 1. 2Dposition and 2. uv's
	/// @param world The world is need for creating the body and deleting the box2D body
	Door(int roomNumber, Direction direction, Camera* camera, Shader* shader, b2World* world);

	/// @brief Destructor of the Door
	~Door();

	/// @brief Update update function is currently empty it is up to the user to decide how to use it
	/// @param deltaTime is the time in seconds between 2 frames you can find the deltaTime in the @file window.h class by calling the function GetDeltaTime()
	/// @return void
	void Update(double deltaTime);

	/// @brief Create a body and add it to the b2World. The height is always standard 50
	/// @param x The x position
	/// @param y The y position
	/// @param w The width of the box2D body
	/// @return void
	void CreateBody(int x, int y, float width);
private:
	Direction direction; ///< @brief direction Represents the direction where the door is facing
	int roomNumber; ///< @brief roomNumber Is the room this door leads to
};

#endif // !DOOR_H
