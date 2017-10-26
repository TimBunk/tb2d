#ifndef LOOTCHEST_H
#define LOOTCHEST_H

#include "destructable.h"
#include "text.h"

#include <string.h>

class Player;

class LootChest : public Destructable {
public:
	LootChest(int gold, Player* player, Shader* text, Camera* camera, Shader* shader, b2World* world);
	~LootChest();

	void Update(float deltaTime);
	void Draw();

	void GiveTexture(Texture chestClosed, Texture chestOpened);
	void Destroy();
	void Reset();

	void SetActive(bool active);
private:
	int gold;
	Texture chestOpened;
	Player* player;

	Text* text;
};

#endif // !LOOTCHEST_H
