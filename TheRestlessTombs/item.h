#ifndef ITEM_H
#define ITEM_H

#include "destructable.h"

struct ShowCaseItem {
	int w;
	int h;
	Texture texture;
};

class Item : public Destructable {
public:
	Item(Camera* camera, Shader* shader, b2World* world);
	~Item();

	ShowCaseItem PickUp();
protected:

private:

};

#endif //!ITEM_H
