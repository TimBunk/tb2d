/**
 * @file b2entity.h
 *
 * @brief The B2Entity header file.
 */

#ifndef B2ENTITY_H
#define B2ENTITY_H

#include "sprite.h"
#include "debugRenderer.h"
#include "resourceManager.h"

#include <Box2D/Box2D.h>

/// @brief Shape specifies a shape
enum Shape {
	box,
	circle
};

/**
 * @brief The B2Entity class
 */
class B2Entity : public Sprite {
friend class DebugRenderer;
public:
	/// @brief Constructor of the B2Entity
	/// @param width is the width of the sprite
	/// @param height is the height of the sprite
	/// @param textureID is the texture that will be used. If textureID = 0 then a color will be used instead
	/// @param world is a b2world
	B2Entity(int width, int height, unsigned int textureID, b2World* world);
	/// @brief Destructor of the B2Entity
	virtual ~B2Entity();

	/// @brief UpdateChilderen updates all of the childerens position, angle and scale of this B2Entity by a specified parent. UpdateChilderen will call first the Draw method then the Update Method and then it will call the UpdateChilderen function of that Entity
	/// @param parent the parent of the childeren which is in almost every case 'this'
	/// @param deltaTime is the deltaTime
	/// @return void
	virtual void UpdateChilderen(Entity* parent, double deltaTime);
	/// @brief DrawChilderen works the same as UpdateChilderen only difference is that the Update method is not called. This can be usefull for when pausing the game but still wanting to render everything
	/// @param parent the parent of the childeren which is in almsot every case 'this'
	/// @return void
	virtual void DrawChilderen(Entity* parent);

	/// @brief Draw submits this B2Entity to a simpleRenderer and also to the debugRenderer if this B2Entity has a body
	virtual void Draw();

	/// @brief CreateBoxCollider creates a body and a fixutre and adds it to the b2World
	/// @param w the width of the box2D body
	/// @param h the height of the box2D body
	/// @param pivot the pivot of the box2D body
	/// @param dynamic if true the body will be dynamic that means that it will be affected by physics if false it will be static and not affected by physics
	/// @param sensor if true the body can overlap with the other body's but still detects collision
	/// @return void
	virtual void CreateBoxCollider(int w, int h, glm::vec2 pivot, bool dynamic, bool sensor);

	/// @brief CreateCircleCollider creates a body and a fixutre and adds it to the b2World
	/// @param radius is the radius of the circle
	/// @param dynamic if true the body will be dynamic that means that it will be affected by physics if false it will be static and not affected by physics
	/// @param sensor if true the body can overlap with the other body's but still detects collision
	/// @return void
	virtual void CreateCircleCollider(int radius, bool dynamic, bool sensor);

	/// @brief SetDebugColor sets the debugColor of the collider
	/// @param color is the new color
	/// @return void
	void SetDebugColor(glm::vec3 color);
	/// @brief GetDebugColor return the current debug color
	/// @return glm::vec3
	glm::vec3 GetDebugColor() { return debugColor; };

	/// @brief AppllyVelocityB2body moves the B2Entity but it can not move through other colliders it also return the new position of the B2Entity
	/// @return glm::vec2
	glm::vec2 ApplyVelocityB2body(glm::vec2 velocity);

	/// @brief GetColliderWidth return the collider width
	/// @return int
	int GetColliderWidth();
	/// @brief GetColliderHeight returns the collider height
	/// @return int
	int GetColliderHeight();
	/// @brief GetColliderPivot returns the pivot of the collider
	/// @return glm::vec2
	glm::vec2 GetColliderPivot() { return colliderPivot; };

	/// @brief GetShape returns the shape of the collider
	/// @return Shape
	Shape GetShape() { return shape; };

	/// @brief SetFilter sets a filter for the B2Entity that can be used for detecting what kind of objects you are colliding with
	/// @param filter the filter you want to set
	/// @return void
	virtual void SetFilter(unsigned int filter) { this->filter = filter; };
	/// @brief GetFilter returns the filter
	/// @return unsigned int
	unsigned int GetFilter() { return filter; };

	/// @brief AddContact a B2Entity will be added whenever this b2Entity fixture collided with an other fixture
	/// @brief The ContactListener class takes care of adding the contacts to this class. You can access the contacts by the a vector named contacts that is protected for this class
	/// @return void
	void AddContact(B2Entity* contact);

	/// @brief RemoveContact a B2Entity will be removed whenever a collision between two fixtures stops. The ContacListener will take care of this function
	/// @return void
	void RemoveContact(B2Entity* contact);

	/// @brief Contact check if the contact is colliding with this B2Entity
	/// @return bool
	bool Contact(B2Entity* contact);

	/// @brief GetAllContacts returns all of the current contacts of this B2Entity
	/// @return vector<B2Entity*>
	std::vector<B2Entity*> GetAllContacts();

	/// @brief SetActive will set the b2Body active or not
	/// @param active If true the body will be active othterwise not
	/// @return void
	virtual void SetActive(bool active);

	static float m2p; ///< @brief m2p stands for meter to pixels because box2D works in meters
	static float p2m; ///< @brief p2m stands for pixel to meter because box2D works in meters

protected:
	unsigned int filter; ///< @brief filter the filter of this B2Entity
	Shape shape; ///< @brief shape the shape of the collider of this B2Entity
	int colliderWidth; ///< @brief colliderWidth is the width of the collider
	int colliderHeight; ///< @brief colliderHeight is the height of the collider
	glm::vec2 colliderPivot; ///< @brief colliderPivot is the pivot if the colliders
	glm::vec3 debugColor; ///< @brief debugColor is the color used by the DebugRenderer
	b2Body* body; ///< @brief body is the body of the collider
	b2World* world; ///< @brief world is the box2D world
	b2Fixture* fixture; ///< @brief fixture is the fixture of the body
	std::vector<B2Entity*> contacts; ///< @brief contacts is a vector with all of the contacts that this B2Entity(fixture) is colliding with

};
#endif // !B2ENTITY_H
