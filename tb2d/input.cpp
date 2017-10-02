#include "input.h"

Input::Input() {
	mousePosition = glm::vec2(0);
	quit = false;
	for (int i=0;i<285;i++) {
		keysPressed[i] = false;
		keysDown[i] = false;
		keysUp[i] = true;
		if (i < 6) {
			mousePressed[i] = false;
			mouseDown[i] = false;
			mouseUp[i] = true;
		}
	}
}

Input::~Input() {

}

void Input::Update() {
	// Go through a list of events from sdl2
	while(SDL_PollEvent(&sdlEvent) != 0) {
	// Check if the user wants to exit the window
		if(sdlEvent.type == SDL_QUIT) {
			quit = true;
		}
		// Checks for keysDown input
		else if (sdlEvent.type == SDL_KEYDOWN) {
			if (keysDown[sdlEvent.key.keysym.scancode] == false) {
				keysPressed[sdlEvent.key.keysym.scancode] = true;
			}
			else {
				keysPressed[sdlEvent.key.keysym.scancode] = false;
			}
			keysUp[sdlEvent.key.keysym.scancode] = false;
			keysDown[sdlEvent.key.keysym.scancode] = true;
		}
		// Check for keysUp input
		else if (sdlEvent.type == SDL_KEYUP) {
			keysPressed[sdlEvent.key.keysym.scancode] = false;
			keysUp[sdlEvent.key.keysym.scancode] = true;
			keysDown[sdlEvent.key.keysym.scancode] = false;
		}
		// Get mousePosition in screenCoordinates
		else if (sdlEvent.type == SDL_MOUSEMOTION) {
			mousePosition.x = sdlEvent.button.x;
			mousePosition.y = sdlEvent.button.y;
		}
		// Check for mouse keys that are up
		else if (sdlEvent.type == SDL_MOUSEBUTTONDOWN) {
			if (mouseDown[(int)sdlEvent.button.button] == false) {
				mousePressed[(int)sdlEvent.button.button] = true;
			}
			else {
				mousePressed[(int)sdlEvent.button.button] = false;
			}
			mouseUp[(int)sdlEvent.button.button] = false;
			mouseDown[(int)sdlEvent.button.button] = true;
		}
		// Check for mouse keys that are down
		else if (sdlEvent.type == SDL_MOUSEBUTTONUP) {
			mousePressed[(int)sdlEvent.button.button] = false;
			mouseUp[(int)sdlEvent.button.button] = true;
			mouseDown[(int)sdlEvent.button.button] = false;
		}
	}
}

glm::vec2 Input::GetMousePositionScreenSpace() {
	return mousePosition;
}

glm::vec2 Input::GetMousePositionWorldSpace(Camera* camera) {
	glm::vec2 mousePositionWorldSpace;
	mousePositionWorldSpace = glm::vec2(mousePosition.x + camera->GetPosition().x, mousePosition.y + camera->GetPosition().y);
	return mousePositionWorldSpace;
}

bool Input::MousePress(int key) {
	if (mousePressed[key] == true) {
		mousePressed[key] = false;
		return true;
	}
	return false;
}

bool Input::MouseDown(int key) {
	if (mouseDown[key] == true) {
		return true;
	}
	return false;
}

bool Input::MouseUp(int key) {
	if (mouseUp[key] == true) {
		return true;
	}
	return false;
}

bool Input::KeyPress(int key) {
	if (keysPressed[key] == true) {
		keysPressed[key] = false;
		return true;
	}
	return false;
}

bool Input::KeyDown(int key) {
	if (keysDown[key] == true) {
		return true;
	}
	return false;
}

bool Input::KeyUp(int key) {
	if (keysUp[key] == true) {
		return true;
	}
	return false;
}

bool Input::Quit() {
	return quit;
}
