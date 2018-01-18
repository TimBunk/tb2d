/**
* @file simplerenderer.h
*
* @brief The SimpleRenderer header file.
*/

#ifndef SIMPLERENDERER_H
#define SIMPLERENDERER_H

#include "renderer.h"

/**
* @brief The SimpleRenderer class
*/
class SimpleRenderer : public Renderer
{
public:
	/// @brief Constructor of the SimpleRenderer
	/// @param shader is the shader that will be used for rendering
	/// @param hud specifies if the this renderer should draw to the hud or not
	SimpleRenderer(Shader* shader, bool hud);
	/// @brief Destructor of the SimpleRenderer
	~SimpleRenderer();

	/// @brief Submit submit a sprite that you want to be rendered
	/// @param sprite the sprite tha you want rendered
	/// @return void
	void Submit(Sprite* sprite);

	/// @brief Render renders all of the submitted sprites
	/// @param camera a camera to set the some uniforms of the shader
	/// @return void
	void Render(Camera* camera);

private:
	/// \todo OpenGL allows 32 textures to be active at a time and because I do everything in one draw call we are limited to that 32 textures
	std::vector<GLint> textureSlots; ///< @brief textureSlots contains all of the textureID's of the particles
	int activeTextureArray[32]; ///< @brief activeTextureArray is a array of number that represents the active textures, 32 is the maximum allowed of active textures
	bool hud; ///< @brief hud specifies if the sprites should be rendered to the hud or to the world
	int drawCount; ///< @brief drawCount the amount of times we need to draw

	GLuint VAO; ///< @brief VAO the VAO for this SimpleRenderer
	GLuint VBO_position; ///< @brief VBO_position is a buffer for the sprite positions
	GLuint VBO_texture; ///< @brief VBO_texture is a buffer for the sprite textureID's
	GLuint VBO_color; ///< @brief VBO_color is a buffer for the sprite colors
	GLuint VBO_model; ///< @brief VBO_model is a buffer for the sprite models

	std::vector<glm::vec4> positions; ///< @brief positions is a vector with positions for all of the sprites that have been submitted
	std::vector<GLfloat> textures; ///< @brief textures is a vector with texuterID's for all of the sprites that have been submitted
	std::vector<glm::vec4> colors; ///< @brief colors is a vector with colors for all of the sprites that have been submitted
	std::vector<glm::mat4> matrices; ///< @brief matrices is a vector with model matrices for all of the sprites that have been submitted
};

#endif // !SIMPLERENDERER_H
