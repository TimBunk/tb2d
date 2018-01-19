/**
* @file sprite.h
*
* @brief The Sprite header file.
*/

#ifndef SPRITE_H
#define SPRITE_H

#include "entity.h"
#include "camera.h"
#include "resourceManager.h"
#include "renderManager.h"

/**
* @brief The Sprite class
*/
class Sprite : public Entity {
public:
	/// @brief Constructor of the Sprite
	/// @param width is the width of the Sprite
	/// @param height is the height of the Sprite
	/// @param textureID id of a texture, this textureID can be received from the texture class. If textureID is 0 a color will be used instead
	Sprite(int width, int height, unsigned int textureID);
	/// @brief Constructor of the Sprite
	/// @param width is the width of the Sprite
	/// @param height is the height of the Sprite
	/// @param color is the color of the Sprite
	Sprite(int width, int height, glm::vec4 color);
	/// @brief Destructor of the Sprite
	virtual ~Sprite();

	/// @brief Draw submits this Sprite to the renderer which is by default the "default" SimpleRenderer created by the RenderManager
	/// @return void
	virtual void Draw();

	// SETTERS
	/// @brief SetRenderer sets the simpleRenderer of this Sprite
	/// @param renderer is the SimpleRenderer that you want to use
	/// @return void
	void SetRenderer(SimpleRenderer* renderer) { this->renderer = renderer; };
	/// @brief SetTextureID sets the textureID of this Sprite
	/// @param textureID is the new textureID, if set to 0 a color will be used instead of a texture
	/// @return void
	void SetTextureID(unsigned int textureID) { this->textureID = textureID; };
	/// @brief SetRepeatableUV sets the textureCoordinates of this Sprite
	/// @brief by default the uv looks like this 0,0,1,1
	/// @param repeat is how many times you want to repeat on x or y axis
	/// @return void
	void SetUV(glm::vec4 uv) { this->uv = uv; };
	/// @brief SetPivot sets the pivot of this Sprite
	/// @param pivot is the new pivot of this sprite. Note that by default the pivot = 0,0. If you want it to be in the top left corner for example you set the pivot to -0.5, 0.5
	/// @return void
	void SetPivot(glm::vec2 pivot) { this->pivot = pivot; };
	/// @brief SetColor sets the color of this Sprite
	/// @param color is the new color of this Sprite
	/// @return void
	void SetColor(glm::vec4 color) { this->color = color; };
	/// @brief SetWidth sets the width of this Sprite
	/// @param width is the new width of this Sprite
	/// @return void
	void SetWidth(int width) { this->width = width; };
	/// @brief SetHeight sets the height of this Sprite
	/// @param height is the new height of this Sprite
	/// @return void
	void SetHeight(int height) { this->height = height; };
	// GETTERS
	/// @brief GetTextureID return the textureID
	/// @return unsigned int
	unsigned int GetTextureID() { return textureID; };
	/// @brief GetRepeatableUV return the repeatableUV
	/// @return glm::vec2
	glm::vec4 GetUV() { return uv; };
	/// @brief GetPivot return the pivot
	/// @return glm::vec2
	glm::vec2 GetPivot() { return pivot; };
	/// @brief GetColor returns the color
	/// @return glm::vec4
	glm::vec4 GetColor() { return color; };
	/// @brief GetWidth returns the width
	/// @return int
	int	 GetWidth() { return width; };
	/// @brief GetHeight returns the height
	/// @return int
	int	GetHeight() { return height; };

protected:
	unsigned int textureID; ///< @brief textureID is the textureID of this sprite. NOTE that if 0 it will use the color instead
	glm::vec4 uv; ///< @brief uv is the uv coordinates for the texture by default it looks like this 0,0,1,1
	glm::vec2 pivot; ///< @brief pivot is the pivot of this Sprite by default this is 0,0. If you want it to be in the top left corner for example you set the pivot to -0.5, 0.5
	glm::vec4 color; ///< @brief color is the color of this Sprite by default this is 0,0,0,0
	int width; ///< @brief width the width of the Sprite
	int height; ///< @brief height the height of the Sprite
	SimpleRenderer* renderer; ///< @brief renderer the renderer that is being used for rendering this Sprite
};

#endif // !SPRITE_H