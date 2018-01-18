#include "renderManager.h"

RenderManager* RenderManager::renderManager = nullptr;

void RenderManager::Initialize()
{
	if (renderManager == nullptr) {
		// Create a singleotn instance of the RenderManager
		renderManager = new RenderManager();
		// Set some default renderers
		CreateSimpleRenderer(0, "default", ResourceManager::GetShader("default"), false);
		CreateSimpleRenderer(0, "hud", ResourceManager::GetShader("default"), true);
		CreateTextRenderer(0, "freetype", ResourceManager::GetShader("freetype"), true);
	}
}

void RenderManager::Destroy()
{
	// Delete the RenderManager if it has been intialized
	if (renderManager != nullptr) {
		delete renderManager;
		renderManager = nullptr;
	}
}

void RenderManager::CreateSimpleRenderer(unsigned int layer, std::string name, Shader * shader, bool hud)
{
	// If the specfied layer is greater then the simpleRenderers size resize the simpleRenders
	if (layer >= renderManager->simpleRenderers.size()) {
		renderManager->simpleRenderers.resize(layer + 1);
	}
	// Create the new simpleRenderer
	renderManager->simpleRenderers[layer][name] = new SimpleRenderer(shader, hud);
	// If the layer is greater then the renders size resize the renders
	if (layer >= renderManager->renderers.size()) {
		renderManager->renderers.resize(layer + 1);
	}
	renderManager->renderers[layer].push_back(renderManager->simpleRenderers[layer][name]);
}

void RenderManager::CreateParticleRenderer(unsigned int layer, std::string name, Shader * shader)
{
	// If the specfied layer is greater then the particleRenderers size resize the particleRenders
	if (layer >= renderManager->particleRenderers.size()) {
		renderManager->particleRenderers.resize(layer + 1);
	}
	// Create the new particleRenderer
	renderManager->particleRenderers[layer][name] = new ParticleRenderer(shader);
	// If the layer is greater then the renders size resize the renders
	if (layer >= renderManager->renderers.size()) {
		renderManager->renderers.resize(layer + 1);
	}
	renderManager->renderers[layer].push_back(renderManager->particleRenderers[layer][name]);
}

void RenderManager::CreateTextRenderer(unsigned int layer, std::string name, Shader * shader, bool hud)
{
	// If the specfied layer is greater then the textRenderers size resize the particleRenders
	if (layer >= renderManager->textRenderers.size()) {
		renderManager->textRenderers.resize(layer + 1);
	}
	// Create the new textRenderer
	renderManager->textRenderers[layer][name] = new TextRenderer(shader, hud);
	// If the layer is greater then the renders size resize the renders
	if (layer >= renderManager->renderers.size()) {
		renderManager->renderers.resize(layer + 1);
	}
	renderManager->renderers[layer].push_back(renderManager->textRenderers[layer][name]);
}

SimpleRenderer * RenderManager::GetSimpleRenderer(std::string name)
{
	// Look for the simpleRenderer and return it
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
	// Look for the particleRenderer and return it
	for (int i = 0; i < RenderManager::renderManager->particleRenderers.size(); i++) {
		if (RenderManager::renderManager->particleRenderers[i].find(name) != RenderManager::renderManager->particleRenderers[i].end()) {
			return RenderManager::renderManager->particleRenderers[i][name];
		}
	}
	// The renderer was not found so return nullptr
	std::cout << "ERROR particleRenderer: " << name << " is not found" << std::endl;
	return nullptr;
}

TextRenderer * RenderManager::GetTextRenderer(std::string name)
{
	// Look for the textRenderer and return it
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
	// Look through all of the renders and render them
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
	// Delete the renderers
	std::vector<std::vector<Renderer*>> renderers;
	for (int i = 0; i < renderers.size(); i++) {
		std::vector<Renderer*>::iterator it = renderers[i].begin();
		while (it != renderers[i].end()) {
			delete (*it);
			it = renderers[i].erase(it);
		}
	}
}
