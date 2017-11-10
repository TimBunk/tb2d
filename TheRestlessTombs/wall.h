/**
 * @file wall.h
 *
 * @brief The wall header file.
 */

#ifndef WALL_H
#define WALL_H

#include "b2entity.h"
#include "debugRenderer.h"

/**
 * @brief The Wall class
 */
class Wall : public B2Entity {
public:
	/// @brief Constructor of the B2Entity takes a Camera and Shader that is used for rendering and a B2World for the B2Body
	/// @param visible Visible means if the Wall should be rendered
	/// @param camera The reason it takes a camera is for drawing the object with the view and projection matrix that can be received from the camera
	/// @param shader The shader is used for the drawing and the shader needs at least to have 3 uniforms matrix4: projection, view and model als the VAO needs to excist of 1. 2Dposition and 2. uv's
	/// @param world The world is need for creating the body and deleting the box2D body
	Wall(bool visible, Camera* camera, Shader* shader, b2World* world);

	/// @brief Destructor of the Wall
	virtual ~Wall();

	/// @brief Update update function is currently empty it is up to the user to deceide how to use it
	/// @param deltaTime is the time in seconds between 2 frames you can find the deltaTime in the @file window.h class by calling the function GetDeltaTime()
	/// @return void
	void Update(double deltaTime);

	/// @brief Draw draws this B2Entity according to the shader and position, angle, scaling of the Entity. (Don't forgot to give it a texture)
	/// @return void
	void Draw();

	/// @brief Create a body and add it to the b2World
	/// @param x The x position
	/// @param y The y position
	/// @param w The width of the box2D body
	/// @param h The height of the box2D body
	/// @return void
	void CreateBody(int x, int y, int w, int h);

	/// @brief This function will set the b2Body active or deactive
	/// @param active If true the body will be active othterwise it will be deactive
	/// @return void
	void SetActive(bool active);

private:
	bool visible; ///< @brief visible If visible is true the wall will be rendered otherwise not
	DebugRenderer* dr; ///< @brief dr Is a debugRender this is handy for seeing the outlines of the walls
};

#endif // !WALL_H
