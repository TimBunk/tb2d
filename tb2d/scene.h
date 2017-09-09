#ifndef SCENE_H
#define SCENE_H

#include "camera.h"
#include "entity.h"

class Scene : public Entity {
public:
	Scene();
	~Scene();
	void CalculateDeltaTime();
protected:
	float deltaTime;

	Camera* camera;
	//void CalculateDeltaTime();
private:
	float lastFrame;
	float totalTime;
	bool printFPS;
	int fpsCount;
};
#endif // !SCENE_H