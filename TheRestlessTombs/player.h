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
#include "healthPotion.h"
#include "damagePotion.h"
#include "speedPotion.h"
#include "showCase.h"
#include "text.h"
#include "bomb.h"
#include "gold.h"

#include <math.h>
#include <string.h>
#include <iomanip> // setprecision
#include <sstream>
#include <glm-0.9.8.4/glm/gtx/rotate_vector.hpp>

class Player : public Person {
public:
    Player(Input* input, Camera* camera, ResourceManager* rm, Shader* shader, b2World* world);
    ~Player();

    void Update(float deltaTime);
    void SetRoom(int number);
    int GetRoom();

    void AddGold(int gold);

private:
    Input* input;
    ResourceManager* rm;
    Weapon* sword;
    ShowCase* showCase;
    Text* textGold;
    Text* textStats;
    std::vector<Hud*> hudHealth;
    Potion* potion;
    DamageBoost damageBoost;
    SpeedBoost speedBoost;

    int lastHealth;
    int gold;
    float currentDamage;
    float currentAttackSpeed;
    float currentSpeed;
    int currentRoom;

    void UpdateStats();
};

#endif // !PLAYER_H
