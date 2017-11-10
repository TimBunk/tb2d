#ifndef CAMERA_H
#define CAMERA_H

#include <iostream>

#include <GL/glew.h>
#include <glm-0.9.8.4/glm/glm.hpp>
#include <glm-0.9.8.4/glm/gtc/matrix_transform.hpp>
#include <glm-0.9.8.4/glm/gtc/type_ptr.hpp>

#include <GL/glew.h>
#include <SDL2/SDL.h>

class Camera {
public:
	Camera(int screenWidth, int screenHeight, SDL_DisplayMode dm);
	virtual ~Camera();

	// Position in pixels
	void SetPosition(glm::vec2 position);
	void PositionAdd(glm::vec2 position);
	glm::vec2 GetPosition();

	// Angle in degrees
	void SetAngle(float angle);
	void AngleAdd(float angle);
	float GetAngle();

	void SetScale(float scale);

	glm::mat4 GetViewMatrix();
	glm::mat4 GetProjectionMatrix();

	float screenWidth;
	float screenHeight;

private:
	glm::vec2 position;
	float angle;
	float scale;

	glm::mat4 projection;
};

#endif // !CAMERA_H
