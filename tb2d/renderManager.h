#ifndef RENDERMANAGER_H
#define RENDERMANAGER_H

#include "simplerenderer.h"
#include "particlerenderer.h"

class RenderManager
{
public:
	static void Initalize();
	static void Destroy();

	static void SetRenderer(unsigned int layer, std::string name, Renderer* rendererer);
	static SimpleRenderer* GetSimpleRenderer(std::string name);
	static ParticleRenderer* GetParticleRenderer(std::string name);
	static void Render(Camera* camera);

private:
	static RenderManager* renderManager;
	RenderManager();
	~RenderManager();

	std::vector<std::map<std::string, Renderer*>> renderers;
};

#endif // !RENDERMANAGER_H
