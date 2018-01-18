/**
* @file textinput.h
*
* @brief The Textinput header file.
*/

#ifndef TEXTINPUT_H
#define TEXTINPUT_H

#include "sprite.h"
#include "text.h"
#include "input.h"

/**
* @brief The Textinput class
*/
class Textinput : public Sprite
{
public:
	/// @brief Constructor of the Textinput
	/// @param text is the text that will be rendererd inside the Textinput
	/// @param onlyNumbers specifies if the user is only allowed to type numbers in the Textinput
	/// @param font is the Font to use for the textRendering
	/// @param hud specifies if this TextInput belongs to the hud or the world
	/// @param width is the width
	/// @param height is the height
	/// @param textureID is the textureID for the TextInput this textureID can be received from a texture. If textureID = 0 that means there is no texture and a color will be used instead
	Textinput(std::string text, bool onlyNumbers, Font font, glm::vec3 textColor, bool hud, int width, int height, unsigned int textureID);
	/// @brief Constructor of the Textinput
	/// @param text is the text that will be rendererd inside the Textinput
	/// @param onlyNumbers specifies if the user is only allowed to type numbers in the Textinput
	/// @param font is the Font to use for the textRendering
	/// @param hud specifies if this TextInput belongs to the hud or the world
	/// @param width is the width
	/// @param height is the height
	/// @param color is the color of this Textinput
	Textinput(std::string text, bool onlyNumbers, Font font, glm::vec3 textColor, bool hud, int width, int height, glm::vec4 color);
	/// @brief Deconstructor of the Textinput
	~Textinput();

	/// @brief Update checks if the inputField is active, this can be activated by clicking on it. If it is active the user cans start typing things in to the Textinput also the user can press enter or click anywhere besides the Textinput to deactive it again. To remove charachters the user can use backspace
	/// @param deltaTime is the time in seconds to complete the last frame
	/// @return void
	void Update(double deltaTime);
	/// @brief IsActive checks if the Textinput is active
	/// @return bool
	bool IsActive() { return active; }
	/// @brief SetActive sets the Textinput active or not
	/// @param active specifies if the Textinput should be active or not
	/// @return void
	void SetActive(bool active) { this->active = active; }

	/// @brief SetText sets the text inside of the Textinput
	/// @param text the text you want inside the Textinput
	void SetText(std::string text);
	/// @brief SetMaxLength sets the maximum allowed of characters inside the Textinput
	/// @param maxLength the maximum allowed of characters inside the Textinput
	/// @return void
	void SetMaxLength(int maxLength) { this->maxLength = maxLength; }
	/// @brief SetMaxDecimals sets the maximum allowed of decimals inside a Textinput
	/// @param maxDecimals is the maximum allowed of decimals
	/// @return void
	void SetMaxDecimals(int maxDecimals) { this->maxDecimals = maxDecimals; }
	/// @brief GetFloat converts the text inside the Textinput into a float, if this is not possible it will return 0
	/// @return void
	float GetFloat() { return number; }
	/// @brief GetString return the text inside the Textinput as a string
	/// @return void
	std::string GetString() { return input; }

private:
	bool onlyNumbers; ///< @brief onlyNumbers specifies is onlyNumbers are allowed in the Textinput
	bool hud; ///< @brief hud specifies if this Textinput should be rendered on the hud or in the world
	bool active; ///< @brief active specifies if this Textinput is currently active or not

	int maxLength; ///< @brief maxLength is the maximum allowed length inside the Textinput
	int maxDecimals; ///< @brief maxDecimals is the maximum allowed of decimals inside the Textinput
	int maxDecimalsAfterDot; ///< @brief maxDecimalsAfterDot is the lenght of the currentText + the maxDecimals so that we always know how long the text is allowed to be

	Text* text; ///< @brief text is the Text that will be rendered inside the Textinput
	std::string input; ///< @brief input is the entered text in the Textinput
	float number; ///< @brief number is the input converted to a float
};

#endif // !TEXTINPUT_H
