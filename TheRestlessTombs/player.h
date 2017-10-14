#ifndef PLAYER_H
#define PLAYER_H

#define _USE_MATH_DEFINES

#include "person.h"
#include "camera.h"
#include "input.h"
#include "hand.h"
#include "renderable.h"
#include "door.h"
#include "weapon.h"

#include <math.h>
#include <glm-0.9.8.4/glm/gtx/rotate_vector.hpp>

class Player : public Person {
public:
    Player(Input* input, Camera* camera, Shader* shader, Texture textureHand, Texture textureSword, b2World* world);
    ~Player();

    void Update(float deltaTime);
    void SetRoom(int number);
    int GetRoom();
private:
    Input* input;
    Weapon* sword;

    int currentRoom;
};

#endif // !PLAYER_H
