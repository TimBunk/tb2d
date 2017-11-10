/**
 * @file enemy.h
 *
 * @brief The enemy header file.
 */


#ifndef ENEMY_H
#define ENEMY_H

#include "player.h"
#include "rayCastCallBack.h"
#include "item.h"

/**
 * @brief The Enemy class
 */
class Enemy : public Person {
public:
	/// @brief Constructor of the Enemy takes a Camera and Shader that is used for rendering and a B2World for the B2Body
	/// @param player The enemy needs to know of the player so that it always can raycast towards the player
	/// @param lineOfSight is a maximum distance for the raycast
	/// @param rm The ResourceManager is used for getting the right textures and shaders for your person
	/// @param camera The reason it takes a camera is for drawing the object with the view and projection matrix that can be received from the camera
	/// @param shader The shader is used for the drawing and the shader needs at least to have 3 uniforms matrix4: projection, view and model als the VAO needs to excist of 1. 2Dposition and 2. uv's
	/// @param world The world is need for creating the body and deleting the box2D body
	Enemy(Player* player, float lineOfSight, ResourceManager* rm, Camera* camera, Shader* shader, b2World* world);

	/// @brief Destructor of the Enemy
	virtual ~Enemy();

	/// @brief Give a item to the enemy, that item will be a child of the enemy and the item will be dropped whenever the enemy dies
	/// @param item The item you want to give
	/// @return void
	void GiveItem(Item* item);

	/// @brief Create a body and add it to the b2World
	/// @param x The x position
	/// @param y The y position
	/// @param w The width of the box2D body
	/// @param h The height of the box2D body
	/// @return void
	virtual void CreateBody(int x, int y, int w, int h);
protected:
	Player* player; ///< @brief player Is a pointer to the actual player
	glm::vec3 playerLastLocation; ///< @brief playerLastLocation Is the location that enemy last saw the player
	float distancePlayer; ///< @brief distancePlayer the distance between the player and the enemy
	float lineOfSight; ///< @brief lineOfSight Is the maximum length of the raycast

	glm::vec3 spawnPosition; ///< @brief spawnPosition Is the start position of the Enemy
	float minimalRange; ///< @brief minimalRange the minimalRange between the Enemy and the Player

	Item* item; ///< @brief item The item the enemy can have

	/// @brief Looks for the player and also makes a call to the function ShootRaycast if the player was found with the raycast and it was in range the move the enemy towards it
	/// @brief If the player gets out of sight move the enemy to the last location he saw the player
	/// @return bool It returns true if the player is in sight
	virtual bool LookForPlayer();

	/// @brief shoots a raycast whenever the player is in lineOfSight and if the raycast reached the player it returns true
	/// @return bool
	bool ShootRaycast();

	/// @brief Sets the b2Body active or not and also sets the health back to original if true
	//// @return void
	virtual void SetActive(bool active);
private:
	RayCastCallBack* raycast; ///< @brief raycast Is the raycast used to look if the player is in lineOfSight
};

#endif // !ENEMY_H
