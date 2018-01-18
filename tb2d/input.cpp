#include "input.h"

Input* Input::input = nullptr;

void Input::Initialize(GLFWwindow * window, float screenWidth, float screenHeight)
{
	if (input == nullptr) {
		// Create a instance of the input
		input = new Input(window, screenWidth, screenHeight);

		// Set charCallback function for the input
		glfwSetCharCallback(window, [](GLFWwindow* window, unsigned int keyCode) {
			input->c = keyCode;
			input->newChar = true;
		});
		// Set mousecursorcallback function for the input
		glfwSetCursorPosCallback(window, [](GLFWwindow* window, double xpos, double ypos) {
			input->mousePosition.x = xpos;
			input->mousePosition.y = ypos;
		});
	}
}

void Input::Destroy()
{
	// Delete the instance of the input if it was intialized
	if (input != nullptr) {
		delete input;
		input = nullptr;
	}
}

glm::vec2 Input::GetMousePositionScreenSpace() {
	glm::vec2 mousePositionScreenSpace;
	// Calculate the mousePosition in screenSpace if a camera exists
	if (input->camera != nullptr) {
		mousePositionScreenSpace = glm::vec2(input->camera->GetWidth() / input->screenWidth*input->mousePosition.x - input->camera->GetWidth() / 2, ((input->camera->GetHeight() / input->screenHeight*input->mousePosition.y) - input->camera->GetHeight()) * -1 - input->camera->GetHeight() / 2);
	}
	return mousePositionScreenSpace;
}

glm::vec2 Input::GetMousePositionWorldSpace() {
	glm::vec2 mousePositionWorldSpace;
	// Calculate the mousePosition in worldSpace if a camera exists
	if (input->camera != nullptr) {
		mousePositionWorldSpace = glm::vec2(input->camera->GetWidth() / input->screenWidth*input->mousePosition.x + input->camera->GetPosition().x - input->camera->GetWidth() / 2, ((input->camera->GetHeight() / input->screenHeight*input->mousePosition.y) - input->camera->GetHeight()) * -1 + input->camera->GetPosition().y - input->camera->GetHeight() / 2);
	}
	return mousePositionWorldSpace;
}

bool Input::MousePress(int mouse) {
	// Checks if the mouse is being pressed
	input->SetMouseState(mouse);
	if (input->mousePressedSecond[mouse]) {
		// Return false if the mouse is still being held down at the second frame and wait for it to be released again
		return false;
	}
	return input->mousePressed[mouse];
}

bool Input::MouseDown(int mouse) {
	// Check if the mouse is being held down
	input->SetMouseState(mouse);
	return input->mouseDown[mouse];
}

bool Input::MouseUp(int mouse) {
	// Check if the mouse is not being held down
	input->SetMouseState(mouse);
	return input->mouseUp[mouse];
}

void Input::SetMouseState(int mouse)
{
	// Check if the mouse is held down
	if (glfwGetMouseButton(window, mouse) == GLFW_PRESS) {
		// Set the mousedown to true because it is being held down and the mouseup to false
		mouseDown[mouse] = true;
		mouseUp[mouse] = false;
		// Check if the mousepressed has not yet been pressed otherwise you have to release the mouse first
		mousePressed[mouse] = true;
		return;
	}
	// The mouse is not being held down so set mouseup to true and mousedown and pressed to false
	mousePressed[mouse] = false;
	mousePressedSecond[mouse] = false;
	mouseDown[mouse] = false;
	mouseUp[mouse] = true;
}

bool Input::KeyPress(int key) {
	// Check if the key is being pressed
	input->SetKeyState(key);
	if (input->keysPressedSecond[key]) {
		// Return false if the key is still being held down at the second frame and wait for it to be released again
		return false;
	}
	return input->keysPressed[key];
}

bool Input::KeyDown(int key) {
	// Check if the key is being held down
	input->SetKeyState(key);
	return input->keysDown[key];
}

bool Input::KeyUp(int key) {
	// Check if the key is not being held down
	input->SetKeyState(key);
	return input->keysUp[key];
}

bool Input::NewChar()
{
	// Return true whenever the user entered a new char
	return input->newChar;
}

char Input::GetKeyPressChar()
{
	// Return the pressed char
	return input->c;
}

void Input::Update(Camera* camera)
{
	// Set the camera
	input->camera = camera;
	// Loop through characters and update them
	for (int i = 0; i < 348; i++) {
		if (i < 8) {
			if (input->mousePressed[i]) {
				input->mousePressedSecond[i] = true;
			}
		}
		if (input->keysPressed[i]) {
			input->keysPressedSecond[i] = true;
		}
	}
	// Set new char always to false
	input->newChar = false;
}

void Input::SetKeyState(int key)
{
	// Check if the key is held down
	if (glfwGetKey(window, key) == GLFW_PRESS) {
		// Set the keysdown to true because it is being held down and the keysup to false
		keysDown[key] = true;
		keysUp[key] = false;
		// Check if the keypressed has not yet been pressed otherwise you have to release the key first
		keysPressed[key] = true;
		return;
	}
	// The key is not being held down so set keyup to true and keydown and pressed to false
	keysPressed[key] = false;
	keysPressedSecond[key] = false;
	keysDown[key] = false;
	keysUp[key] = true;
}

Input::Input(GLFWwindow* window, float screenWidth, float screenHeight) {
	// Intialize all of the variables
	this->window = window;
	this->camera = nullptr;
	this->screenWidth = screenWidth;
	this->screenHeight = screenHeight;
	mousePosition = glm::vec2(0.0f, 0.0f);
	for (int i = 0; i<348; i++) {
		keysPressed[i] = false;
		keysPressedSecond[i] = false;
		keysDown[i] = false;
		keysUp[i] = true;
		if (i < 8) {
			mousePressed[i] = false;
			mousePressedSecond[i] = false;
			mouseDown[i] = false;
			mouseUp[i] = true;
		}
	}
	newChar = false;
	c = ' ';
}

Input::~Input() {

}