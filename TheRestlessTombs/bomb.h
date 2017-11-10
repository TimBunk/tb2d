/**
 * @file bomb.h
 *
 * @brief The bomb header file.
 */

#ifndef BOMB_H
#define BOMB_H

#include "item.h"

/**
 * @brief The bomb class
 */
class Bomb : public Item {
public:
	///< @brief Constructor of the Bomb takes a Camera and Shader that is used for rendering and a B2World for the B2Body
	///< @param bombSize determines the size of the bomb
	///< @param explosionTime The time it takes to explode
	///< @param explosionRadius The radius of the explosion that inflicts damage up on to the player
	///< @param impactTime The time the explosion will be visible
	///< @param camera The reason it takes a camera is for drawing the object with the view and projection matrix that can be received from the camera
	///< @param shader The shader is used for the drawing and the shader needs atleast to have 3 uniforms matrix4: projection, view and model als the VAO needs to excist of 1. 2Dposition and 2. uv's
	///< @param world The world is need for creating the body and deleting the box2D body
	Bomb(float bombSize, float explosionTime, float explosionRadius, float impactTime, Texture bomb, Texture explosionTexture, Camera* camera, Shader* shader, b2World* world);

	///< @brief Destructor of the Bomb
	virtual ~Bomb();

	/// @brief Update update function is currently empty it is up to the user to deceide how to use it
	/// @param deltaTime is the time in seconds between 2 frames you can find the deltaTime in the @file window.h class by calling the function GetDeltaTime()
	/// @return void
	void Update(double deltaTime);

	/// @brief Draw draws this B2Entity according to the shader and position, angle, scaling of the Entity. (Don't forgot to give it a texture)
	/// @return void
	void Draw();

	/// @brief Gives a bool tell that tells you whenever the explosion of the bomb is happening
	/// @return bool
	bool Impact();

	/// @brief Resets everything back to how the bomb should be
	/// @return void
	void Reset();

	/// @brief Create the b2body for the Bomb
	/// @param x Is the x position of the Bomb
	/// @param y Is the y position of the Bomb
	/// @param w Is the width and at the same time the height of the b2body. NOTE that the explosion is a box and not a circle.
	/// @return void
	void CreateBody(int x, int y, int w);
private:
	float explosionTime; ///< @brief The time for that bomb explodes
	float explosionRadius; ///< @brief The size of the explosion
	float w; ///< @brief The width of the bomb itself
	Texture explosionTexture; ///< @brief texture of the explosion
	Texture bomb; ///< @brief texture of the bomb
	glm::vec4 color; ///< @brief The color of the bomb that overlaps the texture. What I mean by this is that Bomb keeps getting more red so that it looks like the Bomb can explode anytime
	bool explode; ///< @brief keeps track of when the explosion is happening

	bool impact; ///< @brief keeps also track of when the explosion is happening but whenever you ask if an impacht is happening like this Impact() the impact bool will turn false so that the damage will be applied only once
	float currentImpactTime; ///< @brief this is kinda like a counter it counts until it equal or is higher then the actual impactTime and then the impacts happens
	float impactTime;///< @brief The time you can get hit by the bomb
};

#endif //!BOMB_H
