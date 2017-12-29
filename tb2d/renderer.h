#ifndef RENDERER_H
#define RENDERER_H

#include <vector>

#include <gl\glew.h>
#include <glfw3.h>
#include <glm-0.9.8.4\glm\glm.hpp>
#include <glm-0.9.8.4\glm\gtc\matrix_transform.hpp>
#include <glm-0.9.8.4\glm\gtc\type_ptr.hpp>

#include "texture.h"
#include "camera.h"
#include "scene.h"

class Sprite;

class Renderer
{
public:
	Renderer(Shader* shader);
	~Renderer();

	virtual void Render(Camera* camera);

protected:
	Shader* shader;

};

#endif // !RENDERER_H
