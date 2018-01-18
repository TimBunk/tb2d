/**
* @file renderManager.h
*
* @brief The RenderManager header file.
*/

#ifndef RENDERMANAGER_H
#define RENDERMANAGER_H

#include "simplerenderer.h"
#include "particlerenderer.h"
#include "textrenderer.h"

/**
* @brief The RenderManager class
*/
class RenderManager
{
public:
	/// @brief Initialize creates a singleton from the RenderManager
	/// @return void
	static void Initialize();
	/// @brief Destroy delete the singleton of the RenderManager
	/// @return void
	static void Destroy();

	/// @brief CreateSimpleRenderer creates a SimpleRenderer and adds it to a map of simpleRenderers
	/// @param layer is the layer at when you want it to be rendered for example something at layer 1 will be rendered then will layer 2 be rendered
	/// @param name the name of the renderer
	/// @param shader the shader that will be used by the SimpleRenderer
	/// @param hud specifies if the rendering is done on the hud or in the world
	/// @return void
	static void CreateSimpleRenderer(unsigned int layer, std::string name, Shader* shader, bool hud);
	/// @brief CreateParticleRenderer creates a ParticleRenderer and adds it to a map of ParticlesRenderers
	/// @param layer is the layer at when you want it to be rendered for example something at layer 1 will be rendered then will layer 2 be rendered
	/// @param name the name of the renderer
	/// @param shader the shader that will be used by the ParticleRenderer
	/// @return void
	static void CreateParticleRenderer(unsigned int layer, std::string name, Shader* shader);
	/// @brief CreateTextRenderer creates a TextRenderer and adds it to a map of TextRenderers
	/// @param layer is the layer at when you want it to be rendered for example something at layer 1 will be rendered then will layer 2 be rendered
	/// @param name the name of the renderer
	/// @param shader the shader that will be used by the TextRenderer
	/// @param hud specifies if the rendering is done on the hud or in the world
	/// @return void
	static void CreateTextRenderer(unsigned int layer, std::string name, Shader* shader, bool hud);

	/// @brief GetSimpleRenderer return the SimpleRenderer with the specified name if it exists otherwise it will return a nullptr
	/// @param name the name of the SimpleRenderer
	/// @return SimpleRenderer*
	static SimpleRenderer* GetSimpleRenderer(std::string name);
	/// @brief GetParticleRenderer return the ParticleRenderer with the specified name if it exists otherwise it will return a nullptr
	/// @param name the name of the ParticleRenderer
	/// @return ParticleRenderer*
	static ParticleRenderer* GetParticleRenderer(std::string name);
	/// @brief GetTextRenderer return the TextRenderer with the specified name if it exists otherwise it will return a nullptr
	/// @param name the name of the TextRenderer
	/// @return TextRenderer*
	static TextRenderer* GetTextRenderer(std::string name);

	/// @brief Render calls all of the rendering calls of all the different renderers
	static void Render(Camera* camera);

private:
	/// @brief Constructor of the RenderManager
	RenderManager();
	/// @brief Destructor of the RenderManager
	~RenderManager();

	static RenderManager* renderManager; ///< @brief renderManager is singleton of the RenderManager

	std::vector<std::map<std::string, SimpleRenderer*>> simpleRenderers; ///< @brief simpleRenderers is a map filled with SimpleRenderer
	std::vector<std::map<std::string, ParticleRenderer*>> particleRenderers; ///< @brief particleRenderers is a map filled with ParticleRenderer
	std::vector<std::map<std::string, TextRenderer*>> textRenderers; ///< @brief textRenderers is a map filled with TextRenderer

	std::vector<std::vector<Renderer*>> renderers; ///< @brief renderers is a map filled with all the renderers
};

#endif // !RENDERMANAGER_H
