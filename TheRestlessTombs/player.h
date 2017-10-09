#ifndef PLAYER_H
#define PLAYER_H

#include "person.h"
#include "camera.h"
#include "input.h"
#include "hand.h"
#include "floor.h"
#include "door.h"

class Player : public Person {
public:
    Player(Input* input, Camera* camera, Shader* shader, Texture textureHand, b2World* world);
    ~Player();

    void Update(float deltaTime);
    void SetRoom(int number);
    int GetRoom();
private:
    Input* input;
    Floor* hand;
    int currentRoom;
};

#endif // !PLAYER_H
