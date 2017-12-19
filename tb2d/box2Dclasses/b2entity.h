/**
 * @file b2entity.h
 *
 * @brief The b2entity header file.
 */

#ifndef B2ENTITY_H
#define B2ENTITY_H

#include "sprite.h"
#include "window.h"
#include "debugRenderer.h"
#include "resourceManager.h"

#include <Box2D/Box2D.h>

enum Shape {
	box,
	circle
};

/**
 * @brief The B2Entity class is the main entity for all of the box2D objects.
 */
class B2Entity : public Sprite {
public:
	/// @brief Constructor of the B2Entity takes a Camera and Shader that is used for rendering and a B2World for the B2Body
	/// @param camera The reason it takes a camera is for drawing the object with the view and projection matrix that can be received from the camera
	/// @param shader The shader is used for the drawing and the shader needs at least to have 3 uniforms matrix4: projection, view and model als the VAO needs to excist of 1. 2Dposition and 2. uv's
	/// @param world The world is need for creating the body and deleting the box2D body
	B2Entity(int width, int height, glm::vec2 pivot, Texture* texture, Camera* camera, b2World* world);

	/// @brief Destructor of the B2Entity
	virtual ~B2Entity();

	/// @brief UpdateChilderen updates and draws all of the children and their children.
	/// @brief It updates according to the position, angle and scaling of the parent for example:
	/// @brief the parents localPosition.x is 4 and the childs localPosition.x is 1 then the final position of the child will be 5
	/// @param parent for example you have a class that inherits from Entity then you can use 'this' as input and all of the childeren from 'this' will be updated accordingly to the parent
	/// @param deltaTime you have to give the deltaTime because the Update function of an Entity takes a deltaTime
	/// @return void
	virtual void UpdateChilderen(Entity* parent, double deltaTime);

	/// @brief Draw draws this B2Entity according to the shader and position, angle, scaling of the Entity. (Don't forgot to give it a texture)
	/// @return void
	virtual void Draw();

	/// @brief Create a body and add it to the b2World
	/// @param x The x position
	/// @param y The y position
	/// @param w The width of the box2D body
	/// @param h The height of the box2D body
	/// @param dynamic If true the body will be dynamic that means that it will be affected by physics if false it will be static and not affected by physics
	/// @param sensor If true the body can overlap with the other body's but still detects collision
	/// @return void
	virtual void CreateBoxCollider(int w, int h, glm::vec2 pivot, bool dynamic, bool sensor);

	virtual void CreateCircleCollider(int radius, bool dynamic, bool sensor);

	void EnableDebugRendering(glm::vec3 color);

	glm::vec2 ApplyVelocityB2body(glm::vec2 velocity);

	int GetColliderWidth();
	int GetColliderHeight();

	/// @brief A contact will be added whenever this b2Entity fixture collided with an other fixture
	/// @brief The ContactListener class takes care of adding the contacts to this class. You can access the contacts by the a vector named contacts that is protected for this class
	/// @return void
	void AddContact(B2Entity* contact);

	/// @brief The ContacListener removed the added contacts when a collision with a fixture stops
	/// @return void
	void RemoveContact(B2Entity* contact);

	bool Contact(B2Entity* contact);

	std::vector<B2Entity*> GetAllContacts();

	/// @brief This function will set the b2Body active or deactive
	/// @param active If true the body will be active othterwise it will be deactive
	/// @return void
	virtual void SetActive(bool active);

	static float m2p;
	static float p2m;

protected:
	DebugRenderer* dr;
	Shape shape;
	int colliderWidth, colliderHeight;
	b2Body* body; ///< @brief The body needs to be initialized by calling CreateBody()
	b2World* world; ///< @brief The world is needed in order for the body to work
	b2Fixture* fixture; ///< @brief The body makes use of only one fixture
	std::vector<B2Entity*> contacts; ///< @brief A vector with all of the contacts that this B2Entity(fixture) is colliding with

private:

};
#endif // !B2ENTITY_H