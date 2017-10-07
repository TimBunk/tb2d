#ifndef PLAYER_H
#define PLAYER_H

#include "person.h"
#include "camera.h"
#include "input.h"
#include "hand.h"

class Player : public Person {
public:
    Player(Input* input, Camera* camera, Shader* shader, Texture textureHand, b2World* world);
    ~Player();

    void Update(float deltaTime);
private:
    Input* input;
    Hand* hand;
};

#endif // !PLAYER_H
