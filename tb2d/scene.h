#ifndef SCENE_H
#define SCENE_H

#define GLEW_STATIC
#define _USE_MATH_DEFINES

#include <iostream>
#include <vector>

#include "camera.h"
#include "entity.h"
#include "resourceManager.h"
#include "input.h"

#include <GL/glew.h>
#include <glm-0.9.8.4/glm/glm.hpp>
#include <glm-0.9.8.4/glm/gtc/matrix_transform.hpp>
#include <glm-0.9.8.4/glm/gtc/type_ptr.hpp>
#include <Box2D/Box2D.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

class Scene : public Entity {
public:
	Scene(Camera* camera);
	~Scene();

	virtual void Update(double deltaTime);
protected:
	Camera* camera;
private:

};
#endif // !SCENE_H
