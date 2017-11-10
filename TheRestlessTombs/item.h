/**
 * @file item.h
 *
 * @brief The item header file.
 */

#ifndef ITEM_H
#define ITEM_H

#include "destructable.h"

/// @brief ShowCaseItem is a struct that can be given to the showCase class and  contains a name and a texture
struct ShowCaseItem {
	std::string name;
	Texture texture;
};

/**
 * @brief The item class is the main class for all the items
 */
class Item : public Destructable {
public:
	///< @brief Constructor of the Item takes a Camera and Shader that is used for rendering and a B2World for the B2Body
	///< @param camera The reason it takes a camera is for drawing the object with the view and projection matrix that can be received from the camera
	///< @param shader The shahder is used for the drawing and the shader needs atleast to have 3 uniforms matrix4: projection, view and model als the VAO needs to excist of 1. 2Dposition and 2. uv's
	///< @param world The world is need for creating the body and deleting the box2D body
	Item(Camera* camera, Shader* shader, b2World* world);

	///< @brief Destructor of the Item
	virtual ~Item();

	/// @brief This function will give you the struct ShowCaseItem of this item
	/// @return ShowCaseItem
	ShowCaseItem PickUp();

	/// @brief This function will give you the name of the item by default this is "item"
	/// @return std::string
	std::string GetName();
protected:
	std::string name; ///< @brief name is the name of the item
private:

};

#endif //!ITEM_H
