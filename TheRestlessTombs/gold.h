#ifndef GOLD_H
#define GOLD_H

#include "item.h"

class Gold : public Item {
public:
	Gold(int value, Camera* camera, Shader* shader, b2World* world);
	~Gold();

	int GetGold();
private:
	int value;
};

#endif //!GOLD_H
