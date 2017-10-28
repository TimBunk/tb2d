#ifndef SHOWCASE_H
#define SHOWCASE_H

#include "hud.h"
#include "item.h"
#include "window.h"

class ShowCase : public Hud {
public:
	ShowCase(int x, int y, int w, int h, Camera* camera, Shader* shader, Texture texture);
	~ShowCase();

	void Draw();

	void Give(ShowCaseItem sci);
	bool IsFull();
	void Clear();
private:
	bool item;
	ShowCaseItem sci;
};

#endif // !SHOWCASE_H
