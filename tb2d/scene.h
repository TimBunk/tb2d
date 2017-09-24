#ifndef SCENE_H
#define SCENE_H

#include <iostream>
#include <vector>

#include "camera.h"
#include "entity.h"

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
	void Update();
	void CalculateDeltaTime();
protected:
	float deltaTime;

	Camera* camera;
private:
	float lastFrame;
	float totalTime;
	int fpsCount;
};
#endif // !SCENE_H
