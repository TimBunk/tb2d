#ifndef PARTICLERENDERER_H
#define PARTICLERENDERER_H

#include "renderer.h"

struct Particle {
	GLuint textureID = 0;// If textureID = 0; There will be no texture instead there will be a color
	glm::vec4 color;
	glm::vec2 position;
	glm::vec2 direction;
	float angle = 0.0f; // In radians
	int width = 0;
	int height = 0;
	float lifetime = 0.0f;
};

class ParticleRenderer : public Renderer
{
public:
	ParticleRenderer(Shader* shader);
	~ParticleRenderer();

	void Submit(Particle particle);
	void Render(Camera* camera);

private:
	struct ParticleData {
		GLfloat textureID = 0.0f;
		glm::vec4 color;
		glm::mat4 model;
	};
	std::vector<GLint> textureSlots;
	int activeTextureArray[32];// 32 is the maximum allowed of active textures

	GLuint VAO;
	GLuint VBO_position;
	GLuint EBO_position;
	GLuint VBO_particleData;
	
	std::vector<ParticleData> particleData;
};

#endif // !PARTICLERENDERER_H
