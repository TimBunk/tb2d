#ifndef GOLD_H
#define GOLD_H

#include "destructable.h"

class Gold : public Destructable {
public:
	Gold(int value, Camera* camera, Shader* shader, b2World* world);
	~Gold();

	int GetGold();
private:
	int value;
};

#endif //!GOLD_H
