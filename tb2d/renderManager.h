#ifndef RENDERMANAGER_H
#define RENDERMANAGER_H

#include "simplerenderer.h"
#include "particlerenderer.h"
#include "textrenderer.h"

class RenderManager
{
public:
	static void Initalize();
	static void Destroy();

	static void CreateSimpleRenderer(unsigned int layer, std::string name, Shader* shader, bool hud);
	static void CreateParticleRenderer(unsigned int layer, std::string name, Shader* shader);
	static void CreateTextRenderer(unsigned int layer, std::string name, Shader* shader, bool hud);

	static SimpleRenderer* GetSimpleRenderer(std::string name);
	static ParticleRenderer* GetParticleRenderer(std::string name);
	static TextRenderer* GetTextRendererer(std::string name);

	static void Render(Camera* camera);

private:
	static RenderManager* renderManager;
	RenderManager();
	~RenderManager();

	std::vector<std::map<std::string, SimpleRenderer*>> simpleRenderers;
	std::vector<std::map<std::string, ParticleRenderer*>> particleRenderers;
	std::vector<std::map<std::string, TextRenderer*>> textRenderers;

	std::vector<std::vector<Renderer*>> renderers;
};

#endif // !RENDERMANAGER_H
