/**
* @file tickbox.h
*
* @brief The Tickbox header file.
*/

#ifndef TICKBOX_H
#define TICKBOX_H

#include "sprite.h"
#include "input.h"

/**
* @brief The Tickbox class
*/
class Tickbox : public Sprite
{
public:
	/// @brief Constructor of the Tickbox
	/// @param hud specifies if it belongs to the hud or not
	/// @param notActiveTextureID is the Texture that will be used when the Tickbox is not active. If textureID is 0 that means a color will be used instead
	/// @param width is the width of the Tickbox
	/// @param height is the height of the Tickbox
	/// @param activeTextureID is the Texture that will be used when the Tickbox is not active. If textureID is 0 that means a color will be used instead
	Tickbox(bool hud, unsigned int notActiveTextureID, int width, int height, unsigned int activeTextureID);
	/// @brief Constructor of the Tickbox
	/// @param hud specifies if it belongs to the hud or not
	/// @param notActiveColor is the color that will be used when the Tickbox is not active
	/// @param width is the width of the Tickbox
	/// @param height is the height of the Tickbox
	/// @param activeColor is the Texture that will be used when the Tickbox is not active
	Tickbox(bool hud, glm::vec4 notActiveColor, int width, int height, glm::vec4 activeColor);
	/// @brief Destructor of the Tickbox
	~Tickbox();

	/// @brief Update checks if the user clicked left mouse button on the Tickbox to active or deactive it
	/// @param deltaTime is the time in seconds to complete the last frame
	/// @return void
	void Update(double deltaTime);
	/// @brief SetActive sets the Tickbox active or not
	/// @param active specifies if the Tickbox should be active or not
	/// @return void
	void SetActive(bool active);
	/// @brief IsActive tells you if the Tickbox is active or not
	/// @return bool
	bool IsActive() { return active; }

private:
	bool hud; ///< @brief hud specifies if this Tickbox belongs to the hud or not
	bool active; ///< @brief active specifies if this Tickbox is active or not
	glm::vec4 activeColor; ///< @brief activeColor is the color that will be used when the Tickbox is active
	glm::vec4 notActiveColor; ///< @brief notActiveColor is the color that will be used when the Tickbox is not active
	unsigned int activeTextureID; ///< @brief activeTextureID is the texture that will be used when the Tickbox is active
	unsigned int notActiveTextureID; ///< @brief notActiveTextureID is the texture that will be used when the Tickbox is not active
};

#endif // !TICKBOX_H
