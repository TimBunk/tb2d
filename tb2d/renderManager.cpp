#include "renderManager.h"

RenderManager* RenderManager::renderManager = nullptr;

void RenderManager::Initalize()
{
	if (RenderManager::renderManager == nullptr) {
		RenderManager::renderManager = new RenderManager();
	}
}

void RenderManager::Destroy()
{
	if (RenderManager::renderManager != nullptr) {
		delete RenderManager::renderManager;
		RenderManager::renderManager = nullptr;
	}
}

void RenderManager::CreateRenderer(std::string name, Shader* shader, bool hud)
{
	RenderManager::renderManager->renderers[name] = new Renderer(shader, hud);
}

Renderer * RenderManager::GetRenderer(std::string name)
{
	if (RenderManager::renderManager->renderers.find(name) != RenderManager::renderManager->renderers.end()) {
		return RenderManager::renderManager->renderers[name];
	}
	return nullptr;
}

void RenderManager::ClearRenderers()
{
	std::map<std::string, Renderer*>::iterator it = RenderManager::renderManager->renderers.begin();
	while (it != RenderManager::renderManager->renderers.end()) {
		(*it).second->Clear();
		++it;
	}
}

void RenderManager::Render(Camera* camera)
{
	std::map<std::string, Renderer*>::iterator it = RenderManager::renderManager->renderers.begin();
	while (it != RenderManager::renderManager->renderers.end()) {
		(*it).second->Render(camera);
		++it;
	}
}

RenderManager::RenderManager()
{

}

RenderManager::~RenderManager()
{
	// Delete renderers
	std::map<std::string, Renderer*>::iterator it = renderers.begin();
	while (it != renderers.end()) {
		delete (*it).second;
		it = renderers.erase(it);
	}
}
