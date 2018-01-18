/**
* @file camera.h
*
* @brief The Camera header file.
*/

#ifndef CAMERA_H
#define CAMERA_H

#include <glm-0.9.8.4/glm/glm.hpp>
#include <glm-0.9.8.4/glm/gtc/matrix_transform.hpp>
#include <glm-0.9.8.4/glm/gtc/type_ptr.hpp>

/**
* @brief The Camera class
*/
class Camera {
public:
	/// @brief Constructor of the Camera
	/// @param screenWidth is the width that will be used by the projectionMatrix
	/// @param screenHeight is the height that will be used by the projectionMatrix
	Camera(int screenWidth, int screenHeight);
	/// @brief Destructor of the Camera
	virtual ~Camera();

	/// @brief SetPosition sets the position of the camera
	/// @param position is the new position of the camera
	/// @return void
	void SetPosition(glm::vec2 position);
	/// @brief PositionAdd adds a value to the currentposition
	/// @param position is the value that will be added to thee currentPosition
	/// @return void
	void PositionAdd(glm::vec2 position);
	/// @brieff GetPosition return the currentposition of the camera
	/// @return glm::vec2
	glm::vec2 GetPosition();

	/// @brief SetAngle sets the angle in radians
	/// @param angle is the new angle
	/// @return void
	void SetAngle(float angle) { this->angle = angle; }
	/// @brief AngleAdd adds a value to the currentangle in radians
	/// @param angle is the angle that will be added to the currentangle
	/// @return void
	void AngleAdd(float angle) { this->angle += angle; }
	/// @brief return the currentangle in radians
	/// @return float
	float GetAngle() { return angle; }

	/// @brief SetScale sets the scale of the Camera
	/// @param scale is the new scale of the Camera
	/// @return void
	void SetScale(float scale) { this->scale = scale; }

	/// @brief GetViewMatrix return the viewmatrix of the Camera
	/// @return glm::mat4
	glm::mat4 GetViewMatrix();
	/// @brief GetProjectionMatrix return the projectionmatrix of the Camera
	/// @return glm::mat4
	glm::mat4 GetProjectionMatrix() { return projection; }

	/// @brief GetWidth return width of the Camera. Also note that the Camera pivot is in the center of the screen
	/// @return float
	float GetWidth() { return width; }
	/// @brief GetHeight return the height of the Camera. Also note that the Camera pivot is in the center of the screen
	/// @return float
	float GetHeight() { return height; }

private:
	float width; ///< @brief width is the width that will be used by the projectionmatrix
	float height; ///< @brief height is the height that will be used by the projectionmatrix

	glm::vec2 position; ///< @brief position is the position of the Camera
	float angle; ///< @brief angle is the angle in radians of the Camera
	float scale; ///< @brief scale is the scale of the camera

	glm::mat4 projection; ///< @brief projection is the projectionmatrix of the camera
};

#endif // !CAMERA_H
