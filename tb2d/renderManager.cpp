#include "renderManager.h"

RenderManager* RenderManager::renderManager = nullptr;

void RenderManager::Initalize()
{
	if (RenderManager::renderManager == nullptr) {
		RenderManager::renderManager = new RenderManager();
		// Set some default renderers
		RenderManager::CreateSimpleRenderer(0, "default", ResourceManager::GetShader("default"), false);
		RenderManager::CreateSimpleRenderer(0, "hud", ResourceManager::GetShader("default"), true);
		RenderManager::CreateTextRenderer(0, "freetype", ResourceManager::GetShader("freetype"), true);
	}
}

void RenderManager::Destroy()
{
	if (RenderManager::renderManager != nullptr) {
		delete RenderManager::renderManager;
		RenderManager::renderManager = nullptr;
	}
}

void RenderManager::CreateSimpleRenderer(unsigned int layer, std::string name, Shader * shader, bool hud)
{
	if (layer >= RenderManager::renderManager->simpleRenderers.size()) {
		RenderManager::renderManager->simpleRenderers.resize(layer + 1);
	}
	RenderManager::renderManager->simpleRenderers[layer][name] = new SimpleRenderer(shader, hud);
	if (layer >= RenderManager::renderManager->renderers.size()) {
		RenderManager::renderManager->renderers.resize(layer + 1);
	}
	RenderManager::renderManager->renderers[layer].push_back(RenderManager::renderManager->simpleRenderers[layer][name]);
}

void RenderManager::CreateParticleRenderer(unsigned int layer, std::string name, Shader * shader)
{
	if (layer >= RenderManager::renderManager->particleRenderers.size()) {
		RenderManager::renderManager->particleRenderers.resize(layer + 1);
	}
	RenderManager::renderManager->particleRenderers[layer][name] = new ParticleRenderer(shader);
	if (layer >= RenderManager::renderManager->renderers.size()) {
		RenderManager::renderManager->renderers.resize(layer + 1);
	}
	RenderManager::renderManager->renderers[layer].push_back(RenderManager::renderManager->particleRenderers[layer][name]);
}

void RenderManager::CreateTextRenderer(unsigned int layer, std::string name, Shader * shader, bool hud)
{
	if (layer >= RenderManager::renderManager->textRenderers.size()) {
		RenderManager::renderManager->textRenderers.resize(layer + 1);
	}
	RenderManager::renderManager->textRenderers[layer][name] = new TextRenderer(shader, hud);
	if (layer >= RenderManager::renderManager->renderers.size()) {
		RenderManager::renderManager->renderers.resize(layer + 1);
	}
	RenderManager::renderManager->renderers[layer].push_back(RenderManager::renderManager->textRenderers[layer][name]);
}

SimpleRenderer * RenderManager::GetSimpleRenderer(std::string name)
{
	for (int i = 0; i < RenderManager::renderManager->simpleRenderers.size(); i++) {
		if (RenderManager::renderManager->simpleRenderers[i].find(name) != RenderManager::renderManager->simpleRenderers[i].end()) {
			return RenderManager::renderManager->simpleRenderers[i][name];
		}
	}
	// The renderer was not found so return nullptr
	std::cout << "ERROR simpleRenderer: " << name << " is not found" << std::endl;
	return nullptr;
}

ParticleRenderer * RenderManager::GetParticleRenderer(std::string name)
{
	for (int i = 0; i < RenderManager::renderManager->particleRenderers.size(); i++) {
		if (RenderManager::renderManager->particleRenderers[i].find(name) != RenderManager::renderManager->particleRenderers[i].end()) {
			return RenderManager::renderManager->particleRenderers[i][name];
		}
	}
	// The renderer was not found so return nullptr
	std::cout << "ERROR particleRenderer: " << name << " is not found" << std::endl;
	return nullptr;
}

TextRenderer * RenderManager::GetTextRendererer(std::string name)
{
	for (int i = 0; i < RenderManager::renderManager->textRenderers.size(); i++) {
		if (RenderManager::renderManager->textRenderers[i].find(name) != RenderManager::renderManager->textRenderers[i].end()) {
			return RenderManager::renderManager->textRenderers[i][name];
		}
	}
	// The renderer was not found so return nullptr
	std::cout << "ERROR textRenderer: " << name << " is not found" << std::endl;
	return nullptr;
}

void RenderManager::Render(Camera* camera)
{
	for (int i = 0; i < RenderManager::renderManager->renderers.size(); i++) {
		for (int j = 0; j < RenderManager::renderManager->renderers[i].size(); j++) {
			RenderManager::renderManager->renderers[i][j]->Render(camera);
		}
	}
}

RenderManager::RenderManager()
{

}

RenderManager::~RenderManager()
{
	std::vector<std::vector<Renderer*>> renderers;
	for (int i = 0; i < renderers.size(); i++) {
		std::vector<Renderer*>::iterator it = renderers[i].begin();
		while (it != renderers[i].end()) {
			// Delete renderers
			delete (*it);
			it = renderers[i].erase(it);
		}
	}
}
