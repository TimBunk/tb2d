#ifndef ROOM_H
#define ROOM_H

#include "b2entity.h"
#include "scene.h"

class Room : public Scene {
public:
	Room(Camera* camera);
	~Room();

	void Update(float deltaTime);
	void SetActive(bool active);
private:

};

#endif // !ROOM_H