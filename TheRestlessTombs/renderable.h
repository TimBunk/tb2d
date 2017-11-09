/**
 * @file renderable.h
 *
 * @brief The renderable header file.
 */

#ifndef RENDERABLE_H
#define RENDERABLE_H

#include "entity.h"
#include "texture.h"
#include "camera.h"
#include "shader.h"

/**
 * @brief The Renderable class
 */
class Renderable : public Entity {
public:
	/// @brief Constructor of the Renderable takes a Camera and Shader that is used for rendering and a B2World for the B2Body
	/// @param texture Is the texture that will be drawm on the renderable
	/// @param camera The reason it takes a camera is for drawing the object with the view and projection matrix that can be received from the camera
	/// @param shader The shader is used for the drawing and the shader needs at least to have 3 uniforms matrix4: projection, view and model als the VAO needs to excist of 1. 2Dposition and 2. uv's
	Renderable(Texture texture, Camera* camera, Shader* shader);

	/// @brief Destructor of the Renderable
	~Renderable();

	/// @brief Draw draws this B2Entity according to the shader and position, angle, scaling of the Entity. (Don't forgot to give it a texture)
	/// @return void
	virtual void Draw();

	/// @brief Create a body and add it to the b2World
	/// @param x The x position
	/// @param y The y position
	/// @param w The width of the box2D body
	/// @param h The height of the box2D body
	/// @param textureWidth Example textureWidth: Lets say your w = 50 but your textureWidth is 25 that means your texture will fit in 2 times in the width
	/// @param textureHeight Example textureHeight: Lets say your h = 50 but your textureHeight is 25 that means your texture will fit in 2 times in the height
	/// @return void
	virtual void CreateBody(int x, int y, int w, int h, float textureWidth, float textureHeight);

protected:
	GLuint VAO; ///< @brief VAO (Vertex Array Object) Stores all of the data needed to draw
	GLuint VBO; ///< @brief VBO (Vertex Buffer Object) Stores all of the vertices
	GLuint EBO; ///< @brief EBO (Vertex Buffer Object) Stores all of the indices for the vertices
	Camera* camera; ///< @brief camera The camera is needed in order to draw to the right place
	Shader* shader; ///< @brief shader Is needed for drawing
	Texture texture; ///< @brief texture The texture that needs to be drawn

};

#endif // !RENDERABLE_H
