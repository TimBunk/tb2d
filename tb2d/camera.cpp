#include "camera.h"

Camera::Camera(int width, int height)
{

	// Set the projection to point at the center of the screen.
	projection = glm::ortho(((float)width) / 2 * -1, ((float)width)/2, ((float)height)/2 * -1, ((float)height)/2, -50.0f, 50.0f);
	position = glm::vec2(0.0f, 0.0f);
	angle = 0.0f;
	scale = 1.0f;
	this->width = width;
	this->height = height;
}

Camera::~Camera()
{
}

void Camera::SetPosition(glm::vec2 position)
{
	// Position times -1 to give the user the illusion that camera is moving to that position
	position *= -1;
	this->position = position;
}

void Camera::PositionAdd(glm::vec2 position)
{
	// Position times -1 to give the user the illusion that camera is moving to that position
	position *= -1;
	this->position += position;
}

glm::vec2 Camera::GetPosition()
{
	glm::vec2 positionCopy = position;
	positionCopy *= -1;
	return positionCopy;
}

glm::mat4 Camera::GetViewMatrix()
{
	glm::mat4 view;
	view = glm::translate(view, glm::vec3(position.x, position.y, 0.0f));
	view = glm::rotate(view, angle, glm::vec3(0.0f, 0.0f, 1.0f));
	view = glm::scale(view, glm::vec3(scale, scale, 0.0f));
	return view;
}