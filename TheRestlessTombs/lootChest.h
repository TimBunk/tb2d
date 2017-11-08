/**
 * @file lootChest.h
 *
 * @brief The lootChest header file.
 */

#ifndef LOOTCHEST_H
#define LOOTCHEST_H

#include "destructable.h"
#include "text.h"

#include <string.h>

class Player; // Say Player exists without defining it.

/**
 * @brief The LootChest class is an inherit class from Destructable.
 */
class LootChest : public Destructable {
public:
	///< @brief Constructor of the LootChest takes a Camera and Shader that is used for rendering and a B2World for the B2Body
	///< @param gold The amount of gold the LootChest stores
	///< @param player We need to know about the player so that whenever the lootChest will be opened the player will receive the gold
	///< @param camera The reason it takes a camera is for drawing the object with the view and projection matrix that can be received from the camera
	///< @param shader The shahder is used for the drawing and the shader needs atleast to have 3 uniforms matrix4: projection, view and model als the VAO needs to excist of 1. 2Dposition and 2. uv's
	///< @param world The world is need for creating the body and deleting the box2D body
	LootChest(int gold, Player* player, Shader* text, Camera* camera, Shader* shader, b2World* world);

	///< @brief Destructor of the LootChest
	~LootChest();

	/// @brief Update update function is currently empty it is up to the user to deceide how to use it
	/// @param deltaTime is the time in seconds between 2 frames you can find the deltaTime in the @file window.h class by calling the function GetDeltaTime()
	/// @return void
	void Update(double deltaTime);

	/// @brief Draw draws this LootChest according to the shader and position, angle, scaling of the Entity. (Don't forgot to give it a texture)
	/// @return void
	void Draw();

	/// @brief Give the LootChest two texture one for when the lootChest is closed and one for when it is opened
	/// @param chestClosed Specify the texture that you want to use for when the lootChest is closed
	/// @param chestOpened specify the texture that you want to use for when the lootChest is openend
	/// @return void
	void GiveTexture(Texture chestClosed, Texture chestOpened);

	/// @brief Destroy the lootChest but doesn't stop drawing the lootChest and it also doesn't set the body to not active. It gives the player the money that is in the lootChest\
	/// @return void
	void Destroy();

	/// @brief Reset the lootChest and reset the Text that comes out of the lootChest
	/// @return void
	void Reset();

	/// @brief Set the body active or not
	/// @param active If true the body will be active otherwise it will be not active
	void SetActive(bool active);
private:
	int gold; ///< @brief gold The amount of gold that is inside of the lootChest
	Texture chestOpened; ///< @brief chestOpened is the texture for when the lootChest is destroyed
	Player* player; ///< @brief the player needs to be saved in order to send gold to the player

	Text* text; ///< @brief text shows the amount of gold you get of the lootChest
};

#endif // !LOOTCHEST_H
