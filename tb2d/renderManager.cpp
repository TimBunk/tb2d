#include "renderManager.h"

RenderManager* RenderManager::renderManager = nullptr;

void RenderManager::Initalize()
{
	if (RenderManager::renderManager == nullptr) {
		RenderManager::renderManager = new RenderManager();
		RenderManager::CreateRenderer(0, "default", ResourceManager::GetShader("default"), false);
	}
}

void RenderManager::Destroy()
{
	if (RenderManager::renderManager != nullptr) {
		delete RenderManager::renderManager;
		RenderManager::renderManager = nullptr;
	}
}

void RenderManager::CreateRenderer(unsigned int layer, std::string name, Shader* shader, bool hud)
{
	if (layer >= RenderManager::renderManager->renderers.size()) {
		RenderManager::renderManager->renderers.resize(layer + 1);
	}
	RenderManager::renderManager->renderers[layer][name] = new Renderer(shader, hud);

	/*std::cout << "print out rendering order!" << std::endl;
	for (int i = 0; i < RenderManager::renderManager->renderers.size(); i++) {
		std::map<std::string, Renderer*>::iterator it = RenderManager::renderManager->renderers[i].begin();
		while (it != RenderManager::renderManager->renderers[i].end()) {
			std::cout << (*it).first << std::endl;
			++it;
		}
	}*/
}

Renderer * RenderManager::GetRenderer(std::string name)
{
	for (int i = 0; i < RenderManager::renderManager->renderers.size(); i++) {
		if (RenderManager::renderManager->renderers[i].find(name) != RenderManager::renderManager->renderers[i].end()) {
			return RenderManager::renderManager->renderers[i][name];
		}
	}
	// The renderer was not found so return nullptr
	return nullptr;
}

void RenderManager::Render(Camera* camera)
{
	for (int i = 0; i < RenderManager::renderManager->renderers.size(); i++) {
		std::map<std::string, Renderer*>::iterator it = RenderManager::renderManager->renderers[i].begin();
		while (it != RenderManager::renderManager->renderers[i].end()) {
			(*it).second->Render(camera);
			++it;
		}
	}
}

RenderManager::RenderManager()
{

}

RenderManager::~RenderManager()
{
	for (int i = 0; i < renderers.size(); i++) {
		std::map<std::string, Renderer*>::iterator it = renderers[i].begin();
		while (it != renderers[i].end()) {
			// Delete renderers
			delete (*it).second;
			it = renderers[i].erase(it);
		}
	}
}
