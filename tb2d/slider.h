/**
* @file slider.h
*
* @brief The Slider header file.
*/

#ifndef SLIDER_H
#define SLIDER_H

#include "button.h"

/**
* @brief The Slider class
*/
class Slider : public Sprite
{
public:
	/// @brief Constructor of the Slider
	/// @param widthButton is the width of the button
	/// @param heihgtButton is the height of the button
	/// @param colorButton is the color of the button
	/// @param hud specifies if this belongs to the hud or not
	/// @param width is the width
	/// @param height is the height
	/// @param textureID id of a texture, this textureID can be received from the texture class. If textureID is 0 a color will be used instead
	Slider(int widthButton, int heightButton, glm::vec4 colorButton, bool hud, int width, int height, unsigned int textureID);
	/// @brief Destructor of the Slider
	~Slider();

	/// @brief Update keeps checks if the mouse is being heldDown on the button and moves it according to the position of the mouse but it can't move further then the height of the slider
	/// @return void
	void Update(double deltaTime);
	/// @brief SetRenderer sets the renderer for both the Slider as well as for the Button
	/// @param renderer is the renderer for the Slider and the Button
	void SetRenderer(SimpleRenderer* renderer);

	/// @brief SetValue sets the value and moves the button according to that value, the value has to be between 0 and 1
	/// @param newValue is the new value
	/// @return void
	void SetValue(float newValue);

	/// @brief GetValue returns a value between 0 and 1 depending on the button it's position
	/// @return float
	float GetValue() { return value; }

private:
	float value; ///< @brief value a value between 0 and 1 depending on the button's position
	Button* button; ///< @brief button a button that can be moved on y-axis
};

#endif // !SLIDER_H
