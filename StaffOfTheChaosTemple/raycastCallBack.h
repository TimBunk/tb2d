/**
 * @file rayCastCallBack.h
 *
 * @brief The rayCastCallBack header file.
 */


#ifndef RAYCASTCALLBACK_H
#define RAYCASTCALLBACK_H

#include "b2entity.h"

#include "shader.h"
#include "window.h"
#include "crystal.h"

#include <GL/glew.h>
#include <glm-0.9.8.4/glm/glm.hpp>
#include <glm-0.9.8.4/glm/gtc/matrix_transform.hpp>
#include <glm-0.9.8.4/glm/gtc/type_ptr.hpp>
#include <Box2D/Box2D.h>

/// @brief RaycastOutput is a struct you will receive whenever you call GetOutput(). It will give you all of the information of the hitted B2Entity by this raycast
struct RaycastOutput {
	b2Fixture* fixture = nullptr;
	b2Vec2 point = b2Vec2(0.0f, 0.0f);
	b2Vec2 normal = b2Vec2(0.0f, 0.0f);
	float32 fraction = 0.0f;
};

/**
 * @brief The RayCastCallBack is an inherited class by b2RayCastCallBack of box2D
 */

class RaycastCallBack : public b2RayCastCallback {
public:
	///< @brief Constructor of the RayCastCallBack
	///< @param user You have to give the user of the raycast so that it won't collide with itself
	RaycastCallBack();

	///< @brief Destructor of the RayCastCallBack
	virtual ~RaycastCallBack();

	/// @brief CreateLine is an optional function it is used for rendering a line that can help you visualize the raycast better
	/// @param length The length of the line
	/// @param width The Width of the line
	/// @param camera The camera used by the window
	/// @param shader Its best to give the debugRenderer shader or make your own one similar to that one
	/// @param color The color of the line
	/// @return void
	void CreateLine(float length, float width, Camera* camera, Shader* shader, glm::vec3 color);

	void ChangeColor(glm::vec3 color);

	/// @brief Draws the line created by the function CreateLine
	/// @param position The position of where the ray starts
	/// @param angle The angle of where the raycast is poiting
	/// @return void
	void Draw(glm::vec2 position, float angle);

	/// @brief ReportFixture looks if the raycast is hitting something note that this raycast ignores sensors and enenmy's.
	/// @param fixture The fixture is the fixture hit by the raycast that will be received from the b2World
	/// @param point A 2D point of where the raycast hitted the other B2Entity
	/// @param normal The normal provided by box2D
	/// @param fraction The fraction provided by box2D
	/// @return float32
	float32 ReportFixture(b2Fixture* fixture, const b2Vec2& point, const b2Vec2& normal, float32 fraction);

	/// @brief This function returns all of the output received by the raycast
	/// @return RaycastOutput
	RaycastOutput GetOutput();
private:
	std::vector<Linkable*> linkables;
	RaycastOutput ro; ///< @brief The raycastOutput received by GetOutput()
	float lineWidth; ///< @brief the lineWidth that is used for drawing
	Camera* camera; ///< @brief The camera is needed for drawing
	Shader* shader; ///< @brief It's best to use the debugRenderer shader
	glm::vec3 color; ///< @brief The color of the line
	GLuint VAO; ///< @brief VAO(Vertex Array Object) is needed for drawing and stores all of the VBO
	GLuint VBO; ///< @brief VBO(Vertex Buffer Object) is needed for creating the VAO. The VBO stores all of the vertices and uv's
};

#endif // !RAYCASTCALLBACK_H
