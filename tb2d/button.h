/**
* @file button.h
*
* @brief The Button header file.
*/

#ifndef BUTTON_H
#define BUTTON_H

#include "input.h"
#include "text.h"
#include "sprite.h"

/**
* @brief The Button class
*/
class Button : public Sprite {
public:
	/// @brief Constructor of the Button
	/// @param width is the width of the Button
	/// @param height is the height of the Button
	/// @param textureID id of a texture, this textureID can be received from the texture class
	/// @param hud specifies if it belongs to the hud or to the world
	Button(int width, int height, unsigned int textureID, bool hud);
	/// @brief Destructor of the Button
	virtual ~Button();

	/// @brief Update checks if the button is pressed or if the mouse hovers over it
	/// @param deltaTime is the default parameter for update
	/// @return void
	void Update(double deltaTime);

	/// @brief Creates a text and places it in the center of the Button
	/// @param text is a string that will be rendered on the Button
	/// @param font the font that you want to use for the text, fonts can be received by the ResourceManager
	/// @param color is the color of the text
	/// @return void
	void CreateText(std::string text, Font font, glm::vec3 color);

	/// @brief Change the string of the text of the button
	/// @param text is the new string that will be rendered on the Button
	/// @return void
	void SetText(std::string text);

	/// @brief Change the color of the text of the Button
	/// @param color is the new color of the text
	/// @return void
	void SetTextColor(glm::vec4 color);

	/// @brief Getter for the string of the text
	/// @return std::string
	std::string GetText() { return text->GetText(); }

	/// @brief Returns true whenever the mouse is hovering over the Button
	/// @return bool
	bool Hover() { return hover; }

	/// @brief Returns true whenever the Button has been pressed by the mouse
	/// @return bool
	bool Down() { return down; }

private:
	Text* text; ///< @brief text is the text of the Button

	bool hud; ///< @brief hud boolean for if it is a hud
	bool hover; ///< @brief hover boolean that will be true whenever the mouse is hovering over the Button
	bool down; ///< @brief down boolean that will be true whenever the left button mouse has been pressed and is hovering over the Button
};

#endif //!BUTTON_H