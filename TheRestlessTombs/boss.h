#ifndef BOSS_H
#define BOSS_H

#include "enemy.h"
#include "text.h"

class Boss : public Enemy {
public:
	Boss(std::string nameBoss, Player* player, float lineOfSight, ResourceManager* rm, Camera* camera, Shader* shader, b2World* world);
	~Boss();

	void Draw();
protected:
	Text* textBoss;
private:
	GLuint HealthVBO, HealthVAO, HealthEBO;
	Shader* healthbar;
};

#endif //!BOSS_H
