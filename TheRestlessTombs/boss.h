/**
 * @file boss.h
 *
 * @brief The boss header file.
 */

#ifndef BOSS_H
#define BOSS_H

#include "enemy.h"
#include "text.h"

/**
 * @brief The Boss class
 */
class Boss : public Enemy {
public:
	/// @brief Constructor of the Boss takes a Camera and Shader that is used for rendering and a B2World for the B2Body
	/// @param nameBoss Is the name that will be displayed when the boss appears
	/// @param player The enemy needs to know of the player so that it always can raycast towards the player
	/// @param lineOfSight is a maximum distance for the raycast
	/// @param rm The ResourceManager is used for getting the right textures and shaders for your person
	/// @param camera The reason it takes a camera is for drawing the object with the view and projection matrix that can be received from the camera
	/// @param shader The shader is used for the drawing and the shader needs at least to have 3 uniforms matrix4: projection, view and model als the VAO needs to excist of 1. 2Dposition and 2. uv's
	/// @param world The world is need for creating the body and deleting the box2D body
	Boss(std::string nameBoss, Player* player, float lineOfSight, ResourceManager* rm, Camera* camera, Shader* shader, b2World* world);

	/// @brief Destructor of the Boss
	~Boss();

	/// @brief Draw draws this Boss according to the shader and position, angle, scaling of the Entity. (Don't forgot to give it a texture)
	/// @brief The Draw function also draws the healthBar of the Boss
	/// @return void
	void Draw();
protected:
	Text* textBoss; ///< @brief textBoss Is that text that displays the name of the boss
private:
	GLuint HealthVAO; ///< @brief VAO(Vertex Array Object) for the healthBar that will display when the boss appears
	GLuint HealthVBO; ///< @brief VBO(Vertex Buffer Object) for the healthBar that will display when the boss appears
	GLuint HealthEBO; ///< @brief EBO(Element Buffer Object) for the healthBar that will display when the boss appears
	Shader* healthbar; ///< @brief healthbar Is the shader for the healthbar that will display when the boss appears
};

#endif //!BOSS_H
