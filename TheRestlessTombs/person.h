/**
 * @file person.h
 *
 * @brief The person header file.
 */

#ifndef PERSON_H
#define PERSON_H

#include "destructable.h"
#include "camera.h"
#include "texture.h"
#include "shader.h"
#include <Box2D/Box2D.h>

/**
 * @brief The Person class is the main class for all of the Enemy and Player classes
 */
class Person : public Destructable {
public:
	/// @brief Constructor of the Person takes a Camera and Shader that is used for rendering and a B2World for the B2Body
	/// @param rm The ResourceManager is used for getting the right textures and shaders for your person
	/// @param camera The reason it takes a camera is for drawing the object with the view and projection matrix that can be received from the camera
	/// @param shader The shader is used for the drawing and the shader needs at least to have 3 uniforms matrix4: projection, view and model als the VAO needs to excist of 1. 2Dposition and 2. uv's
	/// @param world The world is need for creating the body and deleting the box2D body
    Person(ResourceManager* rm, Camera* camera, Shader* shader, b2World* world);

    /// @brief Destructor of the Person
    virtual ~Person();

    void Draw();

    /// @brief Checks if the person is alive according to their health, meaning if the health is lower or equal to 0 the player is not alive
    /// @return bool
    bool IsAlive();

    /// @brief Apply damage to a person the damage goes minus the health
    /// @param damage The amount of damage the person will take the damage goes minus the health
    /// @return void
    virtual void TakeDamage(int damage);

    /// @brief Applies a healing to the peron's health
    /// @param healing is the amount of healing the person receives
    /// @return void
    void ApplyHealing(int healing);

    /// @brief FlipTexture will recreate the VAO and mirror the uv's so that it looks flipped you can call flip as many times as you want
    /// @return void
    void FlipTexture();

    /// @brief Checks if the texture is flipped or not, returns true if it is flipped
    /// @return bool
    bool IsTextureFlipped();

protected:
    ResourceManager* rm; ///< @brief Keep a pointer to the ResourceManager so that you can always get new textures or shaders from it

	int health; ///< @brief health The maximum health of the Person
	int currentHealth; ///< @brief currentHealth The currentHealth of the Person
	int damage; ///< @brief damage The amount of damage the person can deal
	float attackSpeed; ///< @brief attackSpeed The amount of attackSpeed of the person
	float speed; ///< @brief speed The amount of speed the person has

	bool flippedTexture; ///< @brief flippedTexture is a boolean that keeps track if the texture is flipped
	float currentX; ///< @brief save the currentX of the Person so that we can later check it with the new X and that way we can determine which direction the Person is moving

	bool damaged;
	float cooldownDamaged;
	float timerDamaged;

private:

};

#endif // !PERSON_H
