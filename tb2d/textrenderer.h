/**
* @file textrenderer.h
*
* @brief The TextRenderer header file.
*/

#ifndef TEXTRENDERER_H
#define TEXTRENDERER_H

#include "renderer.h"

class Text;

/**
* @brief The TextRenderer class
*/
class TextRenderer : public Renderer
{
public:
	/// @brief Constructor of the TextRenderer
	/// @param shader is the shader that will be used for rendering
	/// @param hud specifies if the rendering should be done on the hud or in the world
	TextRenderer(Shader* shader, bool hud);
	/// @brief Destructor of the TextRenderer
	~TextRenderer();

	/// @brief Submit saves the text in a vector so that all of the text can be rendered all at once
	/// @param text the text you want to render
	/// @return void
	void Submit(Text* text);
	/// @brief Render renders all of the text onto the screen
	/// @param camera is the camera that will be used to set some uniforms of the shader
	/// @return void
	void Render(Camera* camera);

private:
	/// \todo OpenGL allows 32 textures to be active at a time and because I do everything in one draw call we are limited to that 32 textures
	std::vector<GLint> textureSlots; ///< @brief textureSlots contains all of the textureID's of the particles
	int activeTextureArray[32]; ///< @brief activeTextureArray is a array of number that represents the active textures, 32 is the maximum allowed of active textures
	bool hud; ///< @brief hud specifies if the sprites should be rendered to the hud or to the world

	GLuint VAO; ///< @brief VAO the VAO for this textRenderer
	GLuint VBO_position; ///< @brief VBO_position is a buffer for the text positions
	GLuint VBO_texture; ///< @brief VBO_texture is a buffer for the text textureAtlasID's
	GLuint VBO_color; ///< @brief VBO_color is a buffer for the text colors
	GLuint VBO_model; ///< @brief VBO_model is a buffer for the text models

	std::vector<glm::vec4> positions; ///< @brief positions is a vector with positions for all of the text that have been submitted
	std::vector<GLfloat> textures; ///< @brief textures is a vector with texuterAtlasID's for all of the text that have been submitted
	std::vector<glm::vec3> colors; ///< @brief colors is a vector with colors for all of the text that have been submitted
	std::vector<glm::mat4> matrices; ///< @brief matrices is a vector with model matrices for all of the text that have been submitted
};

#endif // !TEXTRENDERER_H
