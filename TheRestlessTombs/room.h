/**
 * @file room.h
 *
 * @brief The room header file.
 */

#ifndef ROOM_H
#define ROOM_H

#include "b2entity.h"
#include "destructable.h"
#include "scene.h"

/**
 * @brief The Room class
 */
class Room : public Scene {
public:
	/// @brief Constructor of the Room
	/// @param camera Is needed by the scene
	Room(Camera* camera);

	/// @brief Destructor of the Room
	virtual ~Room();

	/// @brief Update updates the childeren
	/// @param deltaTime is the time in seconds between 2 frames you can find the deltaTime in the @file window.h class by calling the function GetDeltaTime()
	/// @return void
	void Update(double deltaTime);

	/// @brief calls the Reset() functions for all of the B2Entity's
	/// @return void
	void Reset();

	/// @brief calls The SetActive for all of the B2Entity's
	/// @param active If true all of the B2Entity's will be active otherwise not
	/// @return void
	void SetActive(bool active);
private:

};

#endif // !ROOM_H
