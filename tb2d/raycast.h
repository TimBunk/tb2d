/**
 * @file raycast.h
 *
 * @brief The Raycast header file.
 */

#ifndef RAYCAST_H
#define RAYCAST_H

#include <algorithm>

#include "b2entity.h"

/// @brief Raycasthit contains all of the data for whenever the raycast hits something
struct RaycastHit {
	b2Fixture* fixture = nullptr; ///< @brief fixture the hitted fixture
	glm::vec2 point; ///< @brief point is the point of hit
	glm::vec2 normal; ///< @brief normal is the normal of the hitted B2Entity
	float32 fraction = 0.0f; ///< @brief fraction of the hit. Fraction is always between 0-1
};

/**
 * @brief The Raycast class
 */

class Raycast : public b2RayCastCallback {
public:
	/// @brief Constructor of the Raycast
	/// @param world the b2world
	Raycast(b2World* world);
	/// @brief Destructor of the Raycast
	virtual ~Raycast();

	/// @brief Update updates the raycast by a startingPoint and a endPoint of the Raycast
	/// @param startingPoint is the start position of the Raycast
	/// @param endPoint is the end point of the Raycast
	/// @return void
	void Update(glm::vec2 startingPoint, glm::vec2 endPoint);

	/// @brief GetHits returns all of the hits from the raycast in order of hit
	/// @return vector<RaycastHit>
	std::vector<RaycastHit> GetHits() { return hits; };

	/// @brief Draws send information of the Raycast to the DebugRenderer to visualize it
	/// @param color is the color of the Raycast
	/// @return void
	void Draw(glm::vec3 color);

	/// @brief ReportFixture looks if the raycast is hitting something
	/// @param fixture the fixture is the fixture hit by the raycast that will be received from the b2World
	/// @param point a 2D point of where the raycast hitted the other B2Entity
	/// @param normal the normal provided by box2D
	/// @param fraction the fraction provided by box2D
	/// @return float32
	float32 ReportFixture(b2Fixture* fixture, const b2Vec2& point, const b2Vec2& normal, float32 fraction);

private:
	glm::vec2 startingPoint; ///< @brief startingPoint is the startingPoint of the Raycast
	glm::vec2 endPoint; ///< @brief endPoint is the endPoint of the of the Raycast
	b2World* world; ///< @brief world is the b2world
	std::vector<RaycastHit> hits; ///< @brief hits is a vector with all of the hits in it
};

#endif // !RAYCAST_H
