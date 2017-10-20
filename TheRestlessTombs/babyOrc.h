#ifndef BABYORC_H
#define BABYORC_H

#include "enemy.h"

class BabyOrc : public Enemy {
public:
	BabyOrc(Player* player, Camera* camera, Shader* shader, Shader* lineRenderer);
	~BabyOrc();
private:

};

#endif // !BABYORC_H
