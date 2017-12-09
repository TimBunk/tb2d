#ifndef BUTTON_H
#define BUTTON_H

#include "input.h"
#include "text.h"
#include "resourceManager.h"

class Button : public Entity {
public:
	Button(int width, int height, bool HUD, glm::vec3 color, Input* input, Camera* camera);
	virtual ~Button();

	void Update(double deltaTime);
	void Draw();

	void SetColor(glm::vec3 color);

	void CreateText(std::string text, int textSize, glm::vec3 color);
	void SetText(std::string text);

	bool Hover();
	bool Down();

private:
	int width, height;
	Input* input;
	Camera* camera;
	Text* text;
	glm::vec3 color;
	Shader* shader;
	GLuint VBO, VAO, EBO;

	bool HUD;
	bool hover;
	bool down;
};

#endif //!BUTTON_H