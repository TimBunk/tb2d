#ifndef RENDERER_H
#define RENDERER_H

#include <vector>

#include <gl\glew.h>
#include <glfw3.h>
#include <glm-0.9.8.4\glm\glm.hpp>
#include <glm-0.9.8.4\glm\gtc\matrix_transform.hpp>
#include <glm-0.9.8.4\glm\gtc\type_ptr.hpp>

#include "texture.h"
#include "camera.h"
#include "scene.h"

class Sprite;

class Renderer
{
public:
	Renderer(Shader* shader, bool hud);
	~Renderer();

	void Submit(Sprite* sprite);
	void Render(Camera* camera);

private:
	std::vector<GLint> textureSlots;
	int activeTextureArray[32];// 32 is the maximum allowed of active textures
	Shader* shader;
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

#endif // !RENDERER_H
