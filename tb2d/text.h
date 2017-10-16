#ifndef TEXT_H
#define TEXT_H

#include <iostream>
#include <string>

#include "entity.h"
#include "shader.h"
#include "camera.h"

#include <GL/glew.h>
#include <glm-0.9.8.4/glm/glm.hpp>
#include <glm-0.9.8.4/glm/gtc/matrix_transform.hpp>
#include <glm-0.9.8.4/glm/gtc/type_ptr.hpp>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

class Text : public Entity {
public:
	Text(const char* filePath, std::string text, int fontSize, glm::vec4 color, bool HUD, Camera* camera, Shader* shader);
	~Text();

	void SetText(std::string text);
	void SetFontSize(int fontSize);
	// Set RGBA color
	void SetColor(glm::vec4 color);
	void SetVisibility(float value);
	void Draw();

	std::string GetText();
	unsigned int GetFontSize();
	glm::vec4 GetColor();
	float GetVisibility();
	int GetWidth();
	int GetHeight();

private:
	const char* filePath;
	TTF_Font* font;
	SDL_Color fontColor;
	std::string currentText;
	unsigned int fontSize;
	bool HUD;
	int width, height;
	Camera* camera;
	glm::vec4 color;
	float visibility;

	Shader* shader;
	GLuint VAO, VBO, EBO;
	GLuint textureId;

	void CreateText();
};

#endif // TEXT_H
