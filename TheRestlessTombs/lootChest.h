#ifndef LOOTCHEST_H
#define LOOTCHEST_H

#include "destructable.h"
#include "player.h"
#include "text.h"

#include <string.h>

class LootChest : public Destructable {
public:
	LootChest(int gold, Player* player, Camera* camera, Shader* shader, Shader* text);
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
