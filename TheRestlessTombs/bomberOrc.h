/**
 * @file bomberOrc.h
 *
 * @brief The bomberOrc header file.
 */

#ifndef BOMBERORC_H
#define BOMBERORC_H

#include "enemy.h"
#include "bomb.h"

/**
 * @brief The BomberOrc class
 */
class BomberOrc : public Enemy {
public:
	/// @brief Constructor of the BomberOrc takes a Camera and Shader that is used for rendering and a B2World for the B2Body
	/// @param player The enemy needs to know of the player so that it always can raycast towards the player
	/// @param lineOfSight is a maximum distance for the raycast
	/// @param rm The ResourceManager is used for getting the right textures and shaders for your person
	/// @param camera The reason it takes a camera is for drawing the object with the view and projection matrix that can be received from the camera
	/// @param shader The shader is used for the drawing and the shader needs at least to have 3 uniforms matrix4: projection, view and model als the VAO needs to excist of 1. 2Dposition and 2. uv's
	/// @param world The world is need for creating the body and deleting the box2D body
	BomberOrc(Player* player, float lineOfSight, ResourceManager* rm, Camera* camera, Shader* shader, b2World* world);

	/// @brief Destructor of the BomberOrc
	~BomberOrc();

	/// @brief Update makes a call to LookForPlayer and also updates and spawns Bomb the bombs will be spawned on 75% of the distance between the Player and the BomberOrc
	/// @param deltaTime is the time in seconds between 2 frames you can find the deltaTime in the @file window.h class by calling the function GetDeltaTime()
	/// @return void
	void Update(double deltaTime);

	/// @brief Looks for the player and also makes a call to the function ShootRaycast if the player was found with the raycast and it was in range the move the enemy towards it
	/// @brief If the player gets out of sight move the enemy to the last location he saw the player also the BomberOrc only moves towards the player if the distance between them is lower then half of lineOfSight otherWise move away from the player
	/// @return bool It returns true if the player is in sight
	bool LookForPlayer(float deltaTime);

	/// @brief Apply damage to a BomberOrc the damage goes minus the health
	/// @param damage The amount of damage the person will take the damage goes minus the health
	/// @return void
	void TakeDamage(int damage);

	/// @brief Reset the BomberOrc to it's begin values
	/// @return void
	void Reset();
private:
	float timer; ///< @brief A timer for when to spawn a bomb
	std::vector<Bomb*> bombs; ///< @brief List of bombs that the BomberOrc has thrown
};


#endif //!BOMBERORC_H
