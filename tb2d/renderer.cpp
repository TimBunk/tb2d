#include "renderer.h"
#include "sprite.h"

Renderer::Renderer(Shader* shader)
{
	// Set the shader
	this->shader = shader;
}

Renderer::~Renderer()
{
	
}