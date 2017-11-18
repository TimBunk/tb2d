#ifndef CAMERA_H
#define CAMERA_H

#include <iostream>

#include <GL/glew.h>
#include <glm-0.9.8.4/glm/glm.hpp>
#include <glm-0.9.8.4/glm/gtc/matrix_transform.hpp>
#include <glm-0.9.8.4/glm/gtc/type_ptr.hpp>

#include <GL/glew.h>

class Camera {
public:
	Camera(int screenWidth, int screenHeight);
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

	float GetWidth();
	float GetHeight();

private:
	float width;
	float height;

	glm::vec2 position;
	float angle;
	float scale;

	glm::mat4 projection;
};

#endif // !CAMERA_H
