#include "renderManager.h"

RenderManager* RenderManager::renderManager = nullptr;

void RenderManager::Initalize()
{
	if (RenderManager::renderManager == nullptr) {
		RenderManager::renderManager = new RenderManager();
		// Set a default renderer for the sprites
		RenderManager::SetRenderer(0, "default", new SimpleRenderer(ResourceManager::GetShader("default"), false));
	}
}

void RenderManager::Destroy()
{
	if (RenderManager::renderManager != nullptr) {
		delete RenderManager::renderManager;
		RenderManager::renderManager = nullptr;
	}
}

void RenderManager::SetRenderer(unsigned int layer, std::string name, Renderer * renderer)
{
	if (layer >= RenderManager::renderManager->renderers.size()) {
		RenderManager::renderManager->renderers.resize(layer + 1);
	}
	RenderManager::renderManager->renderers[layer][name] = renderer;
}

SimpleRenderer * RenderManager::GetSimpleRenderer(std::string name)
{
	for (int i = 0; i < RenderManager::renderManager->renderers.size(); i++) {
		if (RenderManager::renderManager->renderers[i].find(name) != RenderManager::renderManager->renderers[i].end()) {
			if (dynamic_cast<SimpleRenderer*>(RenderManager::renderManager->renderers[i][name]) != NULL) {
				return dynamic_cast<SimpleRenderer*>(RenderManager::renderManager->renderers[i][name]);
			}
			else {
				std::cout << "ERROR renderManager: " << name << " is not a simpleRenderer" << std::endl;
				return nullptr;
			}
		}
	}
	// The renderer was not found so return nullptr
	std::cout << "ERROR renderManager: " << name << " is not found" << std::endl;
	return nullptr;
}

ParticleRenderer * RenderManager::GetParticleRenderer(std::string name)
{
	for (int i = 0; i < RenderManager::renderManager->renderers.size(); i++) {
		if (RenderManager::renderManager->renderers[i].find(name) != RenderManager::renderManager->renderers[i].end()) {
			if (dynamic_cast<ParticleRenderer*>(RenderManager::renderManager->renderers[i][name]) != NULL) {
				return dynamic_cast<ParticleRenderer*>(RenderManager::renderManager->renderers[i][name]);
			}
			else {
				std::cout << "ERROR renderManager: " << name << " is not a particleRenderer" << std::endl;
				return nullptr;
			}
		}
	}
	// The renderer was not found so return nullptr
	std::cout << "ERROR renderManager: " << name << " is not found" << std::endl;
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
