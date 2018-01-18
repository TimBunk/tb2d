/**
* @file entity.h
*
* @brief The Entity header file.
*/

#ifndef ENTITY_H
#define ENTITY_H

#include <iostream>
#include <vector>

#include <glm-0.9.8.4/glm/glm.hpp>
#include <glm-0.9.8.4/glm/gtc/matrix_transform.hpp>
#include <glm-0.9.8.4/glm/gtc/type_ptr.hpp>

/**
* @brief The Entity class
*/
class Entity {
public:
	/// @brief Constructor of the Entity
	Entity();
	/// @brief Destructor of the Entity
	virtual ~Entity();

	glm::vec2 localPosition; ///< @brief localPosition is the local position of this Entity
	float localAngle; ///< @brief localAngle is the local angle in radians of this Entity
	glm::vec2 localScale; ///< @brief localScale is the scale of this Entity

	/// @brief Update is a empty function that will be called automaticly if this Entity is a child of a Scene and that Scene gets runned by the Core
	/// @param deltaTime is the deltaTime received by the parent
	/// @return void
	virtual void Update(double deltaTime) { }
	/// @brief UpdateChilderen updates all of the childerens position, angle and scale of this Entity by a specified parent. UpdateChilderen will call first the Draw method then the Update Method and then it will call the UpdateChilderen function of that Entity
	/// @param parent the parent of the childeren which is in almost every case 'this'
	/// @param deltaTime is the deltaTime
	/// @return void
	virtual void UpdateChilderen(Entity* parent, double deltaTime);
	/// @brief DrawChilderen works the same as UpdateChilderen only difference is that the Update method is not called. This can be usefull for when pausing the game but still wanting to render everything
	/// @param parent the parent of the childeren which is in almsot every case 'this'
	/// @return void
	virtual void DrawChilderen(Entity* parent);
	/// @brief Draw is a empty function that will be called automaticly if this Entity is a child of a Scene and that Scene gets runned by the Core
	/// @return void
	virtual void Draw() { }

	/// @brief AddChild adds a Entity as a child to this Entity but only add it once otherwise it might cause unexpected behaviour
	/// @param child the entity you want to make a child of 'this'
	/// @return void
	void AddChild(Entity* child);
	/// @brief RemoveChild search for the specified child and remvoes it from the vector
	/// @param child the child you want to remove from the vector
	/// @return void
	void RemoveChild(Entity* child);

	/// @brief GetModelMatrix returns the modelMatrix
	/// @return glm::mat4
	glm::mat4 GetModelMatrix() { return model; };
	/// @brief GetGlobalPosition returns the globalPosition of this Entity
	/// @return glm::vec2
	glm::vec2 GetGlobalPosition() { return position; }
	/// @brief GetGlobalAngle return the globalAngle of this Etity in radians
	/// @return float
	float GetGlobalAngle() { return angle; }
	/// @brief GetGlobalScale return the globalscale of this Entity
	glm::vec2 GetGlobalScale() { return scale; }

protected:
	std::vector<Entity*> childeren; ///< @brief childeren is a vector that contains all of the child entities
	
	glm::mat4 model; ///< @brief model is the model matrix of this Entity
	glm::vec2 position; ///< @brief position is the global positon of this Entity that is being calculated by UpdateChilderen or DrawChilderen
	float angle; ///< @brief angle is the global angle of this Entity in radians that is being calculated by UpdateChilderen or DrawChilderen
	glm::vec2 scale; ///< @brief scale is the global scale of this Entity that is being calculated by UpdateChilderen or DrawChilderen

};

#endif // !ENTITY_H
