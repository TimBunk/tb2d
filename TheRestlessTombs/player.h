#ifndef PLAYER_H
#define PLAYER_H

#include "person.h"
#include "camera.h"
#include "input.h"

class Player : public Person {
public:
    Player(Input* input, Camera* camera, Shader* shader);
    ~Player();

    void Update(float deltaTime);
private:
    Input* input;
};

#endif // !PLAYER_H
