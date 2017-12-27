/**
 * @file rayCastCallBack.h
 *
 * @brief The rayCastCallBack header file.
 */


#ifndef RAYCAST_H
#define RAYCAST_H

#include <algorithm>

#include "b2entity.h"

#include "shader.h"
#include "window.h"
#include "debugRenderer.h"

#include <GL/glew.h>
#include <glm-0.9.8.4/glm/glm.hpp>
#include <glm-0.9.8.4/glm/gtc/matrix_transform.hpp>
#include <glm-0.9.8.4/glm/gtc/type_ptr.hpp>
#include <Box2D/Box2D.h>

/// @brief RaycastOutput is a struct you will receive whenever you call GetOutput(). It will give you all of the information of the hitted B2Entity by this raycast
struct RaycastHit {
	b2Fixture* fixture = nullptr;
	glm::vec2 point;
	glm::vec2 normal;
	float32 fraction = 0.0f;
};

/**
 * @brief The RayCastCallBack is an inherited class by b2RayCastCallBack of box2D
 */

class Raycast : public b2RayCastCallback {
public:
	///< @brief Constructor of the RayCastCallBack
	///< @param user You have to give the user of the raycast so that it won't collide with itself
	Raycast(b2World* world);

	///< @brief Destructor of the RayCastCallBack
	virtual ~Raycast();

	void Update(glm::vec2 startingPoint, glm::vec2 endPoint);

	std::vector<RaycastHit> GetHits() { return hits; };

	/// @brief Draws the line created by the function CreateLine
	/// @param position The position of where the ray starts
	/// @param angle The angle of where the raycast is poiting
	/// @return void
	void Draw(glm::vec3 color);

	/// @brief ReportFixture looks if the raycast is hitting something note that this raycast ignores sensors and enenmy's.
	/// @param fixture The fixture is the fixture hit by the raycast that will be received from the b2World
	/// @param point A 2D point of where the raycast hitted the other B2Entity
	/// @param normal The normal provided by box2D
	/// @param fraction The fraction provided by box2D
	/// @return float32
	float32 ReportFixture(b2Fixture* fixture, const b2Vec2& point, const b2Vec2& normal, float32 fraction);

private:
	glm::vec2 startingPoint, endPoint;
	b2World* world;
	std::vector<RaycastHit> hits;
	glm::vec3 color; ///< @brief The color of the line
};

#endif // !RAYCASTCALLBACK_H
