#include "window.h"

// This function will be used as an argument for the glfwSetFramebufferSizeCallback event. And it can only be used when the function does
// not belong to any class
void FramebufferSize(GLFWwindow* window, int width, int height);

Window::Window(const char* screenName, bool fullScreen) {
	// Initialize all variables with a value
	backgroundColor = glm::vec3(0.0f, 0.0f, 0.0f);
	// initialize and configure glfw
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	// glfw window creation
	const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
	if (fullScreen) {
		window = glfwCreateWindow(mode->width, mode->height, screenName, glfwGetPrimaryMonitor(), NULL);
	}
	else {
		window = glfwCreateWindow(mode->width, mode->height, screenName, NULL, NULL);
	}
	// Set the framebuffersizecallback event for whenever the user changes the window's size
	glfwSetFramebufferSizeCallback(window, FramebufferSize);
	if (window == NULL) {
		std::cout << "glfw window creation failed!" << std::endl;
		glfwTerminate();
	}
	glfwMakeContextCurrent(window);

	// set this to true so glew knows to use a modern approache to retrieving function pointers and extensions
	glewExperimental = GL_TRUE;

	// initialize glew
	if (GLEW_OK != glewInit()) {
		std::cout << "Error in initializing glew" << std::endl;
		glfwTerminate();
	}

	// Set bleding on for alpha values
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// Initialize input by the GLFWwindow
	Input::Initialize(window, mode->width, mode->height);
}


Window::~Window() {
	// Delete the allocated memory
	Input::Destroy();
	glfwDestroyWindow(window);
	glfwTerminate();
}

void Window::Clear() {
	// Set background color
	glClearColor(backgroundColor.x, backgroundColor.y, backgroundColor.z, 1.0f);
	// Clear color buffer
	glClear(GL_COLOR_BUFFER_BIT);
	// Call the events of glfw
	glfwPollEvents();
}

void Window::SwapBuffers() {
	// swap the buffers
	glfwSwapBuffers(window);
}

int Window::ShouldClose()
{
	return glfwWindowShouldClose(window);
}

void Window::CloseWindow()
{
	glfwSetWindowShouldClose(window, true);
}

// This function is used as an argument for the glfwSetFramebufferSizeCallback event. And it can only be used when the function does
// not belong to any class
void FramebufferSize(GLFWwindow * window, int width, int height)
{
	// Set the viewport in case the user changes the window size
	glViewport(0, 0, width, height);
}

void Window::Resize(int screenWidth, int screenHeight)
{
	// Destroy and initalize the input again because otherwise the mouse position calculations will be wrong
	Input::Destroy();
	Input::Initialize(window, screenWidth, screenHeight);
	glfwSetWindowSize(window, screenWidth, screenHeight);
}

void Window::SetBackgroundColor(glm::vec3 backgroundColor) {
	this->backgroundColor = backgroundColor;
}