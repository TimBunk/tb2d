#ifndef INPUT_H
#define INPUT_H

#include <iostream>
#include <vector>

#include "camera.h"

#include <glm-0.9.8.4/glm/glm.hpp>
#include <glm-0.9.8.4/glm/gtc/matrix_transform.hpp>
#include <glm-0.9.8.4/glm/gtc/type_ptr.hpp>
#include <SDL2/SDL.h>

class Input {
public:
	Input();
	~Input();
	void Update();

	glm::vec2 GetMousePositionScreenSpace();
	glm::vec2 GetMousePositionWorldSpace(Camera* camera);
	bool MousePress(int key);
	bool MouseDown(int key);
	bool MouseUp(int key);

	bool KeyPress(int key);
	bool KeyDown(int key);
	bool KeyUp(int key);

	bool Quit();
private:
	SDL_Event sdlEvent;

	glm::vec2 mousePosition;
	bool mousePressed[6];
	bool mouseDown[6];
	bool mouseUp[6];

	bool keysPressed[285];
	bool keysDown[285];
	bool keysUp[285];
	bool quit;
};

#endif // !INPUT_H
