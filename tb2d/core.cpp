#include "core.h"

Core::Core(const char * screenName, bool fullscreen)
{
	window = new Window(screenName, fullscreen);
	// Initalize variables for deltaTime
	deltaTime = 0.0f;
	lastFrame = glfwGetTime();
	totalTime = 0.0f;
	fpsCount = 0;
	// Initialize the rendermanager
	ResourceManager::Initialize();
	RenderManager::Initalize();
	DebugRenderer::Initialize();
}

Core::~Core()
{
	delete window;
	ResourceManager::Destroy();
	RenderManager::Destroy();
	DebugRenderer::Destroy();
}

void Core::Run(Scene * scene)
{
	// rendering commands
	window->Clear();
	CalculateFrameRate();

	scene->Update(deltaTime);
	RenderManager::Render(scene->GetCamera());
	scene->UpdateChilderen(NULL, deltaTime);
	DebugRenderer::Render(scene->GetCamera());

	window->SwapBuffers();
	Input::Update(scene->GetCamera());
}

bool Core::IsActive()
{
	if (window->ShouldClose()) {
		return false;
	}
	return true;
}

void Core::Close()
{
	window->CloseWindow();
}

double Core::GetDeltaTime()
{
	return deltaTime;
}

void Core::ResizeWindow(int width, int height)
{
	window->Resize(width, height);
}

void Core::SetWindowBackgroundColor(glm::vec3 color)
{
	window->SetBackgroundColor(color);
}

void Core::CalculateFrameRate()
{
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
