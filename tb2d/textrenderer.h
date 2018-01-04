#ifndef TEXTRENDERER_H
#define TEXTRENDERER_H

#include "renderer.h"

class Text;

class TextRenderer : public Renderer
{
public:
	TextRenderer(Shader* shader, bool hud);
	~TextRenderer();

	void Submit(Text* text);
	void Render(Camera* camera);

private:
	std::vector<GLint> textureSlots;
	int activeTextureArray[32];// 32 is the maximum allowed of active textures
	bool hud;

	GLuint VAO;
	GLuint VBO_position;
	GLuint VBO_texture;
	GLuint VBO_color;
	GLuint VBO_model;

	std::vector<glm::vec4> positions;
	std::vector<GLfloat> textures;
	std::vector<glm::vec3> colors;
	std::vector<glm::mat4> matrices;
};

#endif // !TEXTRENDERER_H
