/**
* @file input.h
*
* @brief The Input header file.
*/

#ifndef INPUT_H
#define INPUT_H

#include <vector>

#include <gl\glew.h>
#include <glfw3.h>

#include "camera.h"

/**
* @brief The Input class
*/
class Input {
public:
	/// @brief Initialize initialize the Input as a singleton. This is also done autmaticlly by the Window class
	/// @param window the Input class makes use of the events of glfw and glfw events require a GLFWwindow*
	/// @param screenWidth is the width of the window in pixels
	/// @param screenHeight is the height of the window in pixels
	/// @return void
	static void Initialize(GLFWwindow* window, float screenWidth, float screenHeight);
	/// @brief Destroy deletes the singleton of the Input class
	/// @return void
	static void Destroy();

	/// @brief GetMousePositionScreenSpace returns the mouse position in screenspace this can be usefull for hud elements
	/// @return glm::vec2
	static glm::vec2 GetMousePositionScreenSpace();
	/// @brief GetMousePositionWorldSpace returns the mouse position in world space
	/// @return glm::vec2
	static glm::vec2 GetMousePositionWorldSpace();
	/// @brief MousePress checks if the specified mouse button was pressed 
	/// @param mouse the mouse key for example: GLFW_MOUSE_BUTTON_1
	/// @return bool
	static bool MousePress(int mouse);
	/// @brief MouseDown checks if the specified mouse button is being held down
	/// @param mouse the mouse key for example: GLFW_MOUSE_BUTTON_1
	/// @return bool
	static bool MouseDown(int mouse);
	/// @brief MouseUp checks if the specified mouse button is not being held down
	/// @param mouse the mouse key for example: GLFW_MOUSE_BUTTON_1
	/// @return bool
	static bool MouseUp(int mouse);

	/// @brief KeyPress checks if the specified key is being pressed
	/// @param key the key button for example: GLFW_KEY_ESCAPE
	/// @return bool
	static bool KeyPress(int key);
	/// @brief KeyDown checks if the specified key is being held down
	/// @param key the key button for example: GLFW_KEY_ESCAPE
	/// @return bool
	static bool KeyDown(int key);
	/// @brief KeyUp checks if the specified key is not being held down
	/// @param key the key button for example: GLFW_KEY_ESCAPE
	/// @return bool
	static bool KeyUp(int key);

	/// @brief NewChar if a key is pressed recognize it as a new char so that the user known when to call GetKeyPressChar
	/// @return bool
	static bool NewChar();
	/// @brief GetKeyPressChar get the character behind the pressed key
	/// @return void
	static char GetKeyPressChar();

	/// @brief Update restores all of the pressed keys and mouse buttons that were pressed and aslo sets the camera for getting the mousePosition
	/// @param camera the new camera for getting the mousePosition
	/// @return void
	static void Update(Camera* camera);
private:
	/// @brief Constructor of the Input
	/// @param window is a GLFWwindow that is needed in order to get the events of glfw to work
	/// @param screenWidth is the width of the window in pixels
	/// @param screenHeight is the height of the window in pixels
	Input(GLFWwindow* window, float screenWidth, float screenHeight);
	/// @brief Destructor of the Input
	~Input();

	/// @brief SetMouseState sets the state of the specified mouse button according to the information of glfw
	/// @param mouse the mouse key for example: GLFW_MOUSE_BUTTON_1
	/// @return void
	void SetMouseState(int mouse);
	/// @brief SetKeyState sets the state of the specified key button according to the information of glfw
	/// @param key the key button for example: GLFW_KEY_ESCAPE
	/// @return void
	void SetKeyState(int key);

	static Input* input; ///< @brief input is a singleton of the Input class
	GLFWwindow* window; ///< @brief window is a glfwWindow that is required for using the key events of glfw
	Camera* camera; ///< @brief camera that is being used for calculating the mousePosition
	float screenWidth; ///< @brief screenWidth is the width of the window
	float screenHeight; ///< @brief screenHeight is the height of the window

	glm::vec2 mousePosition; ///< @brief mousePosition is the position of the mouse
	bool mousePressed[8]; ///< @brief mousePressed is a array that contains all 8 glfw_keys for the mouse buttons
	bool mousePressedSecond[8]; ///< @brief mousePressedSecond is a array that contains all 8 glfw_keys for the mouse buttons
	bool mouseDown[8]; ///< @brief mouseDown is a array that contains all 8 glfw_keys for the mouse buttons
	bool mouseUp[8]; ///< @brief mouseUp is a array that contains all 8 glfw_keys for the mouse buttons

	bool keysPressed[348]; ///< @brief keysPressed is a array that contains all 348 glfw_keys for the keys buttons
	bool keysPressedSecond[348]; ///< @brief keysPressed is a array that contains all 348 glfw_keys for the keys buttons
	bool keysDown[348]; ///< @brief keysPressed is a array that contains all 348 glfw_keys for the keys buttons
	bool keysUp[348]; ///< @brief keysPressed is a array that contains all 348 glfw_keys for the keys buttons

	bool newChar; ///< @brief newChar keeps track of whenever a new char has been entered by the user
	char c; ///< @brief c is the latest pressed char
};

#endif // !INPUT_H
