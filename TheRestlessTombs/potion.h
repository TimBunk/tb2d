#ifndef POTION_H
#define POTION_H

#include "b2entity.h"
//#include "player.h"

class Player;

struct ShowCasePotion {
	int w;
	int h;
	Texture texture;
};

class Potion : public B2Entity {
public:
	Potion(Camera* camera, Shader* shader);
	~Potion();

	void Draw();
	void CreateBody(int x, int y, int w, int h, bool dynamic, bool sensor, b2World* world);

	virtual void Destroy();
	virtual void Reset();
	void SetActive(bool active);

	virtual void Use(Player* player);
	ShowCasePotion PickUp();
protected:
	bool alive;
	int w, h;
private:

};

#endif // !POTION_H
