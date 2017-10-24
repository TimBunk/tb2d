#ifndef BOMB_H
#define BOMB_H

#include "destructable.h"

class Bomb : public Destructable {
public:
	Bomb(float bombSize, float explosionTime, float explosionRadius, float impactTime, Texture bomb, Texture explosionTexture, Camera* camera, Shader* shader);
	~Bomb();

	void Update(float deltaTime);
	void Draw();

	bool Impact();
	void Reset();
	void CreateBody(int x, int y, int w, b2World* world);
private:
	float explosionTime;
	float explosionRadius;
	float w;
	Texture explosionTexture;
	Texture bomb;
	glm::vec4 color;
	float timer;
	bool explode;

	bool impact;
	float currentImpactTime;
	float impactTime;
};

#endif //!BOMB_H
