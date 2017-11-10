#ifndef BUTTON_H
#define BUTTON_H

#include "input.h"
#include "text.h"
#include "resourceManager.h"

class Button : public Entity {
public:
	Button(int x, int y, int width, int height, bool HUD, std::string text, glm::vec4 color, Input* input, Camera* camera, ResourceManager* rm);
	virtual ~Button();

	void Update(double deltaTime);
	void Draw();

	void SetColor(glm::vec4 color);

	void SetText(std::string text);
	void SetTextFontSize(int fontSize);
	void SetTextColor(glm::vec4 color);

	bool Hover();
	bool Down();

private:
	int width, height;
	Input* input;
	Camera* camera;
	Text* text;
	glm::vec4 color;
	Shader* shader;
	GLuint VBO, VAO, EBO;

	bool HUD;
	bool hover;
	bool down;
};

#endif //!BUTTON_H
