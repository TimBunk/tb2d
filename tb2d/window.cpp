#include "window.h"

Window::Window(int screenWidth, int screenHeight, const char* screenName, bool fullScreen) {
	// Initialize all variables with a value
	backgroundColor = glm::vec3(0.0f, 0.0f, 0.0f);
	deltaTime = 0.0f;
	lastFrame = 0.0f;
	totalTime = 0.0f;
	fpsCount = 0;
	window = nullptr;
	// Initialize SDL2
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
		std::cout << "Video initialization error: " << SDL_GetError() << std::endl;
	}
	else {
		SDL_DisplayMode dm;
		SDL_GetCurrentDisplayMode(0, &dm);
		if (fullScreen) {
			window = SDL_CreateWindow(screenName, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, dm.w, dm.h, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL | SDL_WINDOW_FULLSCREEN_DESKTOP);
		}
		else {
			window = SDL_CreateWindow(screenName, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, dm.w, dm.h, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);
		}
		if (window == NULL) {
			std::cout << "sdl2 window creation failed! " << SDL_GetError() << std::endl;
		}
		else {
			glContext = SDL_GL_CreateContext(window);
			if (glContext == NULL) {
				std::cout << "failed to set glContext: " << SDL_GetError() << std::endl;
			}
			// set this to true so glew knows to use a modern approache to retrieving function pointers and extensions
			glewExperimental = GL_TRUE;

			// initialize glew
			if (GLEW_OK != glewInit()) {
				std::cout << "Error in initializing glew" << std::endl;
			}

			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

			camera = new Camera(screenWidth, screenHeight, dm);
			input = new Input(dm);
			rm = new ResourceManager();

		}
	}
}


Window::~Window() {
	SDL_GL_DeleteContext(glContext);
	SDL_DestroyWindow(window);
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
	delete camera;
	delete input;
	delete rm;
}

void Window::Update() {
	input->Update();
	CalculateFrameRate();
}

void Window::ClearWindow() {
	// Set background color
	glClearColor(backgroundColor.x, backgroundColor.y, backgroundColor.z, 1.0f);
	// Clear color buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Window::SwapBuffers() {
	SDL_GL_SwapWindow(window);
}

Camera* Window::GetCamera() {
	return camera;
}

Input* Window::GetInput() {
	return input;
}

ResourceManager* Window::GetResourceManager() {
	return rm;
}

float Window::GetDeltaTime() {
	return deltaTime;
}

void Window::SetBackgroundColor(glm::vec3 backgroundColor) {
	this->backgroundColor = backgroundColor;
}

void Window::CalculateFrameRate() {
	float currentFrame = SDL_GetTicks();
	deltaTime = ((currentFrame - lastFrame) / 1000.0f);
	lastFrame = currentFrame;
	fpsCount++;
	totalTime += deltaTime;
	if (totalTime >= 1.0f) {
		totalTime -= 1.0f;
		std::cout << "fps: " << fpsCount << std::endl;
		fpsCount = 0;
	}
}
