#ifndef BOSS_H
#define BOSS_H

#include "enemy.h"
#include "text.h"

class Boss : public Enemy {
public:
	Boss(std::string nameBoss, ResourceManager* rm, Player* player, float lineOfSight, Camera* camera, Shader* shader, Shader* lineRenderer, b2World* world);
	~Boss();

	void Draw();
protected:
	Text* textBoss;
	ResourceManager* rm;
private:
	GLuint HealthVBO, HealthVAO, HealthEBO;
	Shader* healthbar;
};

#endif //!BOSS_H
