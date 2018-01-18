/**
* @file renderer.h
*
* @brief The Renderer header file.
*/

#ifndef RENDERER_H
#define RENDERER_H

#include "resourceManager.h"
#include "camera.h"
#include "scene.h"

class Sprite;

/**
* @brief The Renderer class
*/
class Renderer
{
public:
	/// @brief Constructor of the Renderer
	/// @param shader is the shader that will be used by the Renderer
	Renderer(Shader* shader);
	/// @brief Destructor of the Renderer
	virtual ~Renderer();

	/// @brief Render is currently empty but can be used to do rendering
	virtual void Render(Camera* camera) { }

protected:
	Shader* shader; ///< @brief shader is the shader that can be used for the renderer

};

#endif // !RENDERER_H
