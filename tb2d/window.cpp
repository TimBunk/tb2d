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

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


	input = new Input(window, mode->width, mode->height);
	rm = new ResourceManager();
	// Initalize variables for deltaTime
	deltaTime = 0.0f;
	lastFrame = glfwGetTime();
	totalTime = 0.0f;
	fpsCount = 0;
}


Window::~Window() {
	delete rm;
	delete input;
	glfwDestroyWindow(window);
	glfwTerminate();
}

void Window::Update() {
	CalculateFrameRate();
	input->Update();
}

void Window::Clear() {
	// Set background color
	glClearColor(backgroundColor.x, backgroundColor.y, backgroundColor.z, 1.0f);
	// Clear color buffer
	glClear(GL_COLOR_BUFFER_BIT);
}

void Window::SwapBuffers() {
	// check/call events and swap the buffers
	glfwSwapBuffers(window);
	glfwPollEvents();
	
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
	input->SetScreenWidthAndHeight(screenWidth, screenHeight);
	glfwSetWindowSize(window, screenWidth, screenHeight);
}

Input * Window::GetInput()
{
	return input;
}

ResourceManager* Window::GetResourceManager() {
	return rm;
}

double Window::GetDeltaTime() {
	return deltaTime;
}

void Window::SetBackgroundColor(glm::vec3 backgroundColor) {
	this->backgroundColor = backgroundColor;
}

void Window::CalculateFrameRate() {
	double currentFrame = glfwGetTime();
	deltaTime = (currentFrame - lastFrame);
	lastFrame = currentFrame;
	fpsCount++;
	// Print the fps once the totalTime reached 1 second
	totalTime += deltaTime;
	if (totalTime >= 1.0f) {
		totalTime -= 1.0f;
		std::cout << "fps: " << fpsCount << std::endl;
		fpsCount = 0;
	}
}
