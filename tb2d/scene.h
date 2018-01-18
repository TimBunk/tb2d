/**
* @file scene.h
*
* @brief The Scene header file.
*/


#ifndef SCENE_H
#define SCENE_H

#include "camera.h"
#include "entity.h"

/**
* @brief The Scene class
*/
class Scene : public Entity {
public:
	/// @brief Constructor of the Scene
	/// @param screenWidthCamera will be used for setting the width of the projection matrix of the camera
	/// @param screenHeightCamera will be used for setting the height of the projection matrix of the camera
	Scene(int screenWidthCamera, int screenHeightCamera);
	/// @brief Destructor of the Scene
	virtual ~Scene();

	/// @brief GetCamera returns the camera of this Scene
	/// @return Camera*
	Camera* GetCamera() { return camera; }
protected:
	Camera* camera; ///< @brief camera the camera of this Scene

private:

};
#endif // !SCENE_H
