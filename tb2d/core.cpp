#include "core.h"

Core::Core(const char * screenName, bool fullscreen)
{
	// Create the window
	window = new Window(screenName, fullscreen);
	// Initalize variables for deltaTime
	deltaTime = 0.0f;
	lastFrame = glfwGetTime();
	totalTime = 0.0f;
	fpsCount = 0;
	// Initialize all of the singletons
	ResourceManager::Initialize();
	RenderManager::Initalize();
	DebugRenderer::Initialize();
}

Core::~Core()
{
	// Delete the allocated memory
	delete window;
	ResourceManager::Destroy();
	RenderManager::Destroy();
	DebugRenderer::Destroy();
}

void Core::Run(Scene * scene)
{
	// Clear the window
	window->Clear();
	// Calculate fps and deltaTime
	CalculateFrameRate();
	
	// Update the scene
	scene->Update(deltaTime);
	// Render scene by the camera of the scene
	RenderManager::Render(scene->GetCamera());
	// Update the childeren
	scene->UpdateChilderen(NULL, deltaTime);
	// Render all of the debug information
	DebugRenderer::Render(scene->GetCamera());

	// SwapBuffers
	window->SwapBuffers();
	// Update the input by the camera of the scene
	Input::Update(scene->GetCamera());
}

bool Core::IsWindowActive()
{
	// Checks if the window has not yet been exited
	if (window->ShouldClose()) {
		return false;
	}
	return true;
}

void Core::CloseWindow()
{
	// Closes the window
	window->CloseWindow();
}

double Core::GetDeltaTime()
{
	return deltaTime;
}

void Core::ResizeWindow(int width, int height)
{
	// Resizes the window
	window->Resize(width, height);
}

void Core::SetWindowBackgroundColor(glm::vec3 color)
{
	// Sets the background color of the window
	window->SetBackgroundColor(color);
}

void Core::CalculateFrameRate()
{
	// Calculate deltaTime and fps
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
