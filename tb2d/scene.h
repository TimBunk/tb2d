#ifndef SCENE_H
#define SCENE_H

#define _USE_MATH_DEFINES

#include <iostream>
#include <vector>

#include "camera.h"
#include "entity.h"
#include "resourceManager.h"

#include <GL/glew.h>
#include <glm-0.9.8.4/glm/glm.hpp>
#include <glm-0.9.8.4/glm/gtc/matrix_transform.hpp>
#include <glm-0.9.8.4/glm/gtc/type_ptr.hpp>
#include <Box2D/Box2D.h>

class Scene : public Entity {
public:
	Scene(int screenWidthCamera, int screenHeightCamera);
	virtual ~Scene();

	virtual void Update(double deltaTime);
	Camera* GetCamera();
protected:
	Camera* camera;
private:

};
#endif // !SCENE_H
