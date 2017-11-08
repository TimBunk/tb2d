/**
 * @file necromancerOrc.h
 *
 * @brief The necromancerOrc header file.
 */

#ifndef NECROMANCERORC_H
#define NECROMANCERORC_H

#include "babyOrc.h"

/**
 * @brief The NecromancerOrc class
 */
class NecromancerOrc : public Enemy {
public:
	/// @brief Constructor of the NecromancerOrc takes a Camera and Shader that is used for rendering and a B2World for the B2Body
	/// @param spawnCooldown is the cooldown for spawning new babyOrcs
	/// @param player The enemy needs to know of the player so that it always can raycast towards the player
	/// @param lineOfSight is a maximum distance for the raycast
	/// @param rm The ResourceManager is used for getting the right textures and shaders for your person
	/// @param camera The reason it takes a camera is for drawing the object with the view and projection matrix that can be received from the camera
	/// @param shader The shader is used for the drawing and the shader needs at least to have 3 uniforms matrix4: projection, view and model als the VAO needs to excist of 1. 2Dposition and 2. uv's
	/// @param world The world is need for creating the body and deleting the box2D body
	NecromancerOrc(float spawnCooldown, Player* player, float lineOfSight, ResourceManager* rm, Camera* camera, Shader* shader, b2World* world);

	/// @brief Destructor of the NecromancerOrc
	~NecromancerOrc();

	/// @brief Update makes a call to LookForPlayer and also spawns and update babyOrcs
	/// @param deltaTime is the time in seconds between 2 frames you can find the deltaTime in the @file window.h class by calling the function GetDeltaTime()
	/// @return void
	void Update(double deltaTime);

	/// @brief Apply damage to a NecromancerOrc the damage goes minus the health
	/// @param damage The amount of damage the person will take the damage goes minus the health
	/// @return void
	void TakeDamage(int damage);

	/// @brief Reset the NecromancerOrc to it's begin values
	/// @return void
	void Reset();

	/// @brief Create a body and add it to the b2World. NOTE that the body of the NecromancerOrc is static because the NecromancerOrc doesn't move
	/// @param x The x position
	/// @param y The y position
	/// @param w The width of the box2D body
	/// @param h The height of the box2D body
	/// @return void
	void CreateBody(int x, int y, int w, int h);

	/// @brief Set the NecromancerOrc active or not if you choose to deactivate it all of the babyOrc will get rid of as well
	void SetActive(bool active);
private:
	float spawnCooldown; ///< @brief spawnCooldown The cooldown that it takes to spawn a new BabyOrc
	float currentCooldown; ///< @brief currentCooldown Is a counter toward the spawnCooldown and when it is equal or higher then the spawnCooldown spawn a new BabyOrc

	Entity* babyOrcsHolder; ///< @brief babyOrcsHolder is a empty entity that stores all of the babyOrcs
	std::vector<BabyOrc*> babyOrcs; ///< @brief babyOrcs also keeps track of the bayOrcs so that we can easily delete them because the babyOrcsHolder won't do that for us
};

#endif //!NECROMANCERORC_H
