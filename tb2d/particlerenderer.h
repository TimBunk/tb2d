/**
* @file particlerenderer.h
*
* @brief The ParticleRenderer header file.
*/


#ifndef PARTICLERENDERER_H
#define PARTICLERENDERER_H

#include "renderer.h"

/// @brief Particle contains all of the basic variables that a particle needs
struct Particle {
	GLuint textureID = 0; ///< @brief textureID is the textureID that be received from a texture if textureID = 0 there will be no texture instead there will be a color
	glm::vec4 color; ///< @brief color is the color used for the particle
	glm::vec2 position; ///< @brief position is the position of the particle
	glm::vec2 direction; ///< @brief direction is the direction that this particle will move to
	float angle = 0.0f; ///< @brief angle is the angle of the particle in radians
	int width = 0; ///< @brief width is the width of the particle
	int height = 0; ///< @brief height is the height of the particle
	float lifetime = 0.0f; ///< @brief lifetime the lifetime of the particle
};

/**
* @brief The ParticleRenderer class
*/
class ParticleRenderer : public Renderer
{
public:
	/// @brief Constructor of the ParticleRenderer
	/// @param shader the shader that will be used for this ParticleRenderer
	ParticleRenderer(Shader* shader);
	/// @brief Destructor of the ParticleRenderer
	~ParticleRenderer();

	/// @brief Submit submit a particle that needs to be rendered
	/// @param particle the particle you want to render
	/// @return void
	void Submit(Particle particle);
	/// @brief Render renders all of the submitted particles
	/// @param camera a camera is needed for setting up the shader
	void Render(Camera* camera);

private:
	/// @brief ParticleData contains everything that the shader needs to know about the Particle
	struct ParticleData {
		GLfloat textureID = 0.0f; ///< @brief textureID is the textureID that be received from a texture if textureID = 0 there will be no texture instead there will be a color
		glm::vec4 color; ///< @brief color is the color used for the Particle
		glm::mat4 model; ///< @brief model is the model of the particle
	};
	/// \todo OpenGL allows 32 textures to be active at a time and because I do everything in one draw call we are limited to that 32 textures
	std::vector<GLint> textureSlots; ///< @brief textureSlots contains all of the textureID's of the particles
	int activeTextureArray[32]; ///< @brief activeTextureArray is a array of number that represents the active textures, 32 is the maximum allowed of active textures

	GLuint VAO; ///< @brief VAO is the VAO for this ParticleRenderer
	GLuint VBO_position; ///< @brief VBO_position is a buffer for the position of the particles
	GLuint EBO_position;  ///< @brief EBO_position is a element buffer for the position of the particles
	GLuint VBO_particleData; ///< @brief VBO_particleData is a buffer that contains all of the particleDatas
	
	std::vector<ParticleData> particleData; ///< @brief particleData a vector of all of the particleDatas
};

#endif // !PARTICLERENDERER_H
