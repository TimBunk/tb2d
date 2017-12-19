#ifndef RENDERMANAGER_H
#define RENDERMANAGER_H

#include "renderer.h"

class RenderManager
{
public:
	static void Initalize();
	static void Destroy();

	static void CreateRenderer(std::string name, Shader* shader, bool hud);
	static Renderer* GetRenderer(std::string name);
	static void ClearRenderers();
	static void Render(Camera* camera);

private:
	static RenderManager* renderManager;
	RenderManager();
	~RenderManager();

	std::map<std::string, Renderer*> renderers;
};

#endif // !RENDERMANAGER_H