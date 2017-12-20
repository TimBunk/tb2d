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

class Renderer
{
public:
	Renderer(Shader* shader, bool hud);
	~Renderer();

	void Clear();
	void UpdateVBO(Entity* entity);
	void Render(Camera* camera);

	void AddAttributeUV(Texture* texture);
	void AddInstanceAttributeColor();

private:
	Texture* texture;
	Shader* shader;
	bool hud;
	int drawCount;

	GLuint VAO;
	GLuint VBO_position;
	GLuint EBO_position;
	GLuint VBO_model;
	GLuint VBO_uv;
	GLuint EBO_uv;
	GLuint VBO_color;

	std::vector<glm::vec2> positions;
	std::vector<glm::mat4> matrices;
	std::vector<glm::vec2> uvs;
	std::vector<glm::vec4> colors;
};

#endif // !RENDERER_H
