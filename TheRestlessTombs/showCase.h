#ifndef SHOWCASE_H
#define SHOWCASE_H

#include "hud.h"
#include "potion.h"
#include "window.h"

class ShowCase : public Hud {
public:
	ShowCase(int x, int y, int w, int h, Camera* camera, Shader* shader, Texture texture);
	~ShowCase();

	void Draw();

	void Give(ShowCasePotion scp);
	bool IsFull();
	void Clear();
private:
	bool item;
	ShowCasePotion scp;
};

#endif // !SHOWCASE_H
