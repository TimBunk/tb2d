/**
 * @file showCase.h
 *
 * @brief The showCase header file.
 */

#ifndef SHOWCASE_H
#define SHOWCASE_H

#include "hud.h"
#include "item.h"
#include "window.h"
#include "text.h"

/**
 * @brief The ShowCase class
 */
class ShowCase : public Hud {
public:
	/// @brief Constructor of the ShowCase takes a Camera and Shader that is used for rendering and a B2World for the B2Body
	/// @param x Is the x position in screenSpace
	/// @param y Is the y position in screenSpace
	/// @param w Represents the width
	/// @param h Represents the height
	/// @param camera The reason it takes a camera is for drawing the object with the view and projection matrix that can be received from the camera
	/// @param shader The shader is used for the drawing and the shader needs at least to have 3 uniforms matrix4: projection, view and model als the VAO needs to excist of 1. 2Dposition and 2. uv's
	/// @param world The world is need for creating the body and deleting the box2D body
	ShowCase(int x, int y, int w, int h, Camera* camera, Shader* shader, Shader* textHud, Texture texture);

	/// @brief Destructor of the ShowCase
	virtual ~ShowCase();

	/// @brief Draw draws this ShowCase and Item according to the shader and position, angle, scaling of the Entity. (Don't forgot to give it a texture)
	/// @return void
	void Draw();


	/// @brief You can give it a ShowCaseItem struct to display
	/// @param sci Is a ShowCaseItem that can be given to display in the ShowCase
	/// @return void
	void Give(ShowCaseItem sci);

	/// @brief Checks if there is already a item in the ShowCase if so return true
	/// @return void
	bool IsFull();

	/// @brief Removes the item from the ShowCase
	/// @return void
	void Clear();
private:
	bool item; ///< @brief item Is a boolean that keeps of if there is already a item in the ShowCase
	ShowCaseItem sci; ///< @brief sci Has all of the data of the item that is needed
	Text* nameItem; ///< @brief nameItem can be drawn to the screen and displays the name of the Item that is currently in the ShowCase
};

#endif // !SHOWCASE_H
