#ifndef SIMPLERENDERER_H
#define SIMPLERENDERER_H

#include "renderer.h"

class SimpleRenderer : public Renderer
{
public:
	SimpleRenderer(Shader* shader, bool hud);
	~SimpleRenderer();

	void Submit(Sprite* sprite);
	void Render(Camera* camera);

private:
	std::vector<GLint> textureSlots;
	int activeTextureArray[32];// 32 is the maximum allowed of active textures
	bool hud;
	int drawCount;

	GLuint VAO;
	GLuint VBO_position;
	GLuint VBO_texture;
	GLuint VBO_color;
	GLuint VBO_model;

	std::vector<glm::vec4> positions;
	std::vector<GLfloat> textures;
	std::vector<glm::vec4> colors;
	std::vector<glm::mat4> matrices;
};

#endif // !SIMPLERENDERER_H
