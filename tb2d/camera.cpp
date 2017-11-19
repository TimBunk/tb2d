#include "camera.h"

Camera::Camera(int width, int height)
{
	projection = glm::ortho(0.0f, ((float)width), 0.0f, ((float)height), -50.0f, 50.0f);
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
	position *= -1;
	this->position = position;
}

void Camera::PositionAdd(glm::vec2 position)
{
	position *= -1;
	this->position += position;
}

glm::vec2 Camera::GetPosition()
{
	glm::vec2 positionCopy = position;
	positionCopy *= -1;
	return positionCopy;
}

void Camera::SetAngle(float angle)
{
	this->angle = angle;
}

void Camera::AngleAdd(float angle)
{
	this->angle += angle;
}

float Camera::GetAngle()
{
	return angle;
}

void Camera::SetScale(float scale)
{
	this->scale = scale;
}

glm::mat4 Camera::GetViewMatrix()
{
	glm::mat4 view;
	view = glm::translate(view, glm::vec3(position.x, position.y, 0.0f));
	view = glm::rotate(view, glm::radians(angle), glm::vec3(0.0f, 0.0f, 1.0f));
	view = glm::scale(view, glm::vec3(scale, scale, 0.0f));
	return view;
}

glm::mat4 Camera::GetProjectionMatrix()
{
	return projection;
}

float Camera::GetWidth()
{
	return width;
}

float Camera::GetHeight()
{
	return height;
}
