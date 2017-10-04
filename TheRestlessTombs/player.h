#ifndef PLAYER_H
#define PLAYER_H

#include "person.h"
#include "camera.h"

class Player : public Person {
public:
    Player(Camera* camera, Shader* shader);
    ~Player();

    void Update(float deltaTime);
private:

};

#endif // !PLAYER_H
