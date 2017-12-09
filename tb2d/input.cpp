#include "input.h"

Input* Input::_input = nullptr;

void Input::Init(GLFWwindow * window, float screenWidth, float screenHeight)
{
	if (Input::_input == nullptr) {
		Input::_input = new Input(window, screenWidth, screenHeight);
		return;
	}
	std::cout << "Input is already initialized!" << std::endl;
}

Input* Input::GetInstance()
{
	if (Input::_input != nullptr) {
		return Input::_input;
	}
	std::cout << "Input has not yet been intialized" << std::endl;
	return nullptr;
}

void Input::Destroy()
{
	if (Input::_input != nullptr) {
		delete Input::_input;
		Input::_input = nullptr;
		return;
	}
	std::cout << "You need to initialize the input before destroying it!" << std::endl;
}

void Input::MouseCallback(GLFWwindow * window, double xpos, double ypos)
{
	// Get the position according to the window's size
	mousePosition.x = xpos;
	mousePosition.y = ypos;
}

glm::vec2 Input::GetMousePositionScreenSpace(Camera* camera) {
	Input* input = Input::GetInstance();
	glm::vec2 mousePositionScreenSpace;
	mousePositionScreenSpace = glm::vec2(camera->GetWidth()/input->screenWidth*input->mousePosition.x, ((camera->GetHeight()/input->screenHeight*input->mousePosition.y) - camera->GetHeight()) * -1);
	return mousePositionScreenSpace;
}

glm::vec2 Input::GetMousePositionWorldSpace(Camera* camera) {
	Input* input = Input::GetInstance();
	glm::vec2 mousePositionWorldSpace;
	mousePositionWorldSpace = glm::vec2(camera->GetWidth() / input->screenWidth*input->mousePosition.x + camera->GetPosition().x, ((camera->GetHeight() / input->screenHeight*input->mousePosition.y) - camera->GetHeight()) * -1 + camera->GetPosition().y);
	return mousePositionWorldSpace;
}

bool Input::MousePress(int mouse) {
	Input* input = Input::GetInstance();
	// Check if the mousepressed is already true and if so it first has to become false again by releasing the mouse
	if (input->mousePressed[mouse]) {
		input->SetMouseState(mouse);
		if (input->mousePressed[mouse]) {
			return false;
		}
	}
	else {
		input->SetMouseState(mouse);
	}
	return input->mousePressed[mouse];
}

bool Input::MouseDown(int mouse) {
	Input* input = Input::GetInstance();
	input->SetMouseState(mouse);
	return input->mouseDown[mouse];
}

bool Input::MouseUp(int mouse) {
	Input* input = Input::GetInstance();
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
		if (!mousePressed[mouse]) {
			mousePressed[mouse] = true;
		}
		return;
	}
	// The mouse is not being held down so set mouseup to true and mousedown and pressed to false
	mousePressed[mouse] = false;
	mouseDown[mouse] = false;
	mouseUp[mouse] = true;
}

bool Input::KeyPress(int key) {
	Input* input = Input::GetInstance();
	// Check if the keypressed is already true and if so it first has to become false again by releasing the key
	if (input->keysPressed[key]) {
		input->SetKeyState(key);
		if (input->keysPressed[key]) {
			return false;
		}
	}
	else {
		input->SetKeyState(key);
	}
	return input->keysPressed[key];
}

bool Input::KeyDown(int key) {
	Input* input = Input::GetInstance();
	input->SetKeyState(key);
	return input->keysDown[key];
}

bool Input::KeyUp(int key) {
	Input* input = Input::GetInstance();
	input->SetKeyState(key);
	return input->keysUp[key];
}

void Input::SetKeyState(int key)
{
	// Check if the key is held down
	if (glfwGetKey(window, key) == GLFW_PRESS) {
		// Set the keysdown to true because it is being held down and the keysup to false
		keysDown[key] = true;
		keysUp[key] = false;
		// Check if the keypressed has not yet been pressed otherwise you have to release the key first
		if (!keysPressed[key]) {
			keysPressed[key] = true;
		}
		return;
	}
	// The key is not being held down so set keyup to true and keydown and pressed to false
	keysPressed[key] = false;
	keysDown[key] = false;
	keysUp[key] = true;
}

Input::Input(GLFWwindow* window, float screenWidth, float screenHeight) {
	this->window = window;
	this->screenWidth = screenWidth;
	this->screenHeight = screenHeight;
	mousePosition = glm::vec2(0.0f, 0.0f);
	for (int i = 0; i<348; i++) {
		keysPressed[i] = false;
		keysDown[i] = false;
		keysUp[i] = true;
		if (i < 8) {
			mousePressed[i] = false;
			mouseDown[i] = false;
			mouseUp[i] = true;
		}
	}

	// A hacky kinda way to get events working for member functions
	// https://stackoverflow.com/questions/7676971/pointing-to-a-function-that-is-a-class-member-glfw-setkeycallback
	glfwSetWindowUserPointer(window, this);
	glfwSetCursorPosCallback(window, [](GLFWwindow* window, double xpos, double ypos) {
		static_cast<Input*>(glfwGetWindowUserPointer(window))->MouseCallback(window, xpos, ypos);
	});
}

Input::~Input() {

}