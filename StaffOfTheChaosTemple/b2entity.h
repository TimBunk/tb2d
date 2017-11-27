/**
 * @file b2entity.h
 *
 * @brief The b2entity header file.
 */

#ifndef B2ENTITY_H
#define B2ENTITY_H

#include "entity.h"
#include "texture.h"
#include "camera.h"
#include "shader.h"
#include "window.h"

#include <Box2D/Box2D.h>

/**
 * @brief The B2Entity class is the main entity for all of the box2D objects.
 */
class B2Entity : public Entity {
public:
	/// @brief Constructor of the B2Entity takes a Camera and Shader that is used for rendering and a B2World for the B2Body
	/// @param camera The reason it takes a camera is for drawing the object with the view and projection matrix that can be received from the camera
	/// @param shader The shader is used for the drawing and the shader needs at least to have 3 uniforms matrix4: projection, view and model als the VAO needs to excist of 1. 2Dposition and 2. uv's
	/// @param world The world is need for creating the body and deleting the box2D body
	B2Entity(Camera* camera, Shader* shader, b2World* world);

	/// @brief Destructor of the B2Entity
	virtual ~B2Entity();

	/// @brief Update update function is currently empty it is up to the user to deceide how to use it
	/// @param deltaTime is the time in seconds between 2 frames you can find the deltaTime in the @file window.h class by calling the function GetDeltaTime()
	/// @return void
	virtual void Update(double deltaTime);

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
	virtual void CreateBody(int x, int y, int w, int h, bool dynamic, bool sensor, bool fixedRotation);

	/// @brief Give the B2Entity a texture that will be used while drawing
	/// @param texture Specify the texture that you want to use for drawing
	/// @return void
	virtual void GiveTexture(Texture* texture);

	glm::vec2 ApplyVelocityB2body(glm::vec2 velocity);

	/// @brief Get the position from the box2d body but in pixels instead of meters
	///	@return glm::vec2
	glm::vec2 GetPositionInPixelsB2body();

	/// @brief Get the angle from the b2Body. !Note that the angle is in radians
	/// @return float
	float GetAngleB2body();

	/// @brief A contact will be added whenever this b2Entity fixture collided with an other fixture
	/// @brief The ContactListener class takes care of adding the contacts to this class. You can access the contacts by the a vector named contacts that is protected for this class
	/// @return void
	void AddContact(B2Entity* contact);

	/// @brief The ContacListener removed the added contacts when a collision with a fixture stops
	/// @return void
	void RemoveContact(B2Entity* contact);

	/// @brief This function will set the b2Body active or deactive
	/// @param active If true the body will be active othterwise it will be deactive
	/// @return void
	virtual void SetActive(bool active);

	static float m2p;
	static float p2m;

protected:
	Camera* camera; ///< @brief Camera that is given through the constructor and is needed in order to draw this B2Entity
	Shader* shader; ///< @brief Shader that is given through the constructor and is needed in order to draw this B2Entity. The shader needs at least to have three uniforms matrix4: model, projection, view. The VAO object expects 2 vertex position(x and y) and 2 uv position(x and y)

	b2Body* body; ///< @brief The body needs to be initialized by calling CreateBody()
	b2World* world; ///< @brief The world is needed in order for the body to work
	Texture* texture; ///< @brief texture is needed in order to draw correctly

	GLuint VAO; ///< @brief VAO(Vertex Array Object) is required in order to use the shader this will automatically be created when creating a body
	GLuint VBO; ///< @brief VBO(Vertex Buffer Object) is used in order for the VAO to work. It stores all of the vertices and uv's
	GLuint EBO; ///< @brief EBO(Element Buffer Object) is used in order for the VAO to work. It stores all of the indices.

	b2Fixture* fixture; ///< @brief The body makes use of only one fixture
	b2Vec2 point[4]; ///< @brief the points are the vertices received from creating the body

	std::vector<B2Entity*> contacts; ///< @brief A vector with all of the contacts that this B2Entity(fixture) is colliding with
	int width; ///< @brief The width of the body you entered in CreateBody()
	int height; ///< @brief The height of the body you entered in CreateBody()
private:

};
#endif // !B2ENTITY_H
