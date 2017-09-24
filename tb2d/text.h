#ifndef TEXT_H
#define TEXT_H

#include <iostream>
#include <string>

#include "shader.h"

#include <GL/glew.h>
#include <glm-0.9.8.4/glm/glm.hpp>
#include <glm-0.9.8.4/glm/gtc/matrix_transform.hpp>
#include <glm-0.9.8.4/glm/gtc/type_ptr.hpp>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

class Text {
public:
	Text(const char* filePath, const char* text, int fontSize, glm::vec4 color, bool HUD, float width, float height, glm::mat4 projection);
	~Text();

	void SetText(const char* text);
	void SetFontSize(int fontSize);
	// Set RGBA color
	void SetColor(glm::vec4 color);
	void SetPosition(glm::vec3);
	void Draw(glm::mat4 view);
	void DrawHUD();
private:
	const char* filePath;
	TTF_Font* font;
	SDL_Color fontColor;
	const char* currentText;
	unsigned int fontSize;
	bool HUD;
	glm::vec4 color;
	glm::mat4 model;

	Shader* shader;
	GLuint VBO, VAO, EBO;
	GLuint textureId;

	void CreateText();
};

#endif // TEXT_H
