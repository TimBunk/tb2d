#ifndef ITEM_H
#define ITEM_H

#include "destructable.h"

struct ShowCaseItem {
	std::string name;
	Texture texture;
};

class Item : public Destructable {
public:
	Item(Camera* camera, Shader* shader, b2World* world);
	~Item();

	ShowCaseItem PickUp();
	std::string GetName();
protected:
	std::string name;
private:

};

#endif //!ITEM_H
