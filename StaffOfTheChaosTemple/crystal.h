#ifndef CRYSTAL_H
#define CRYSTAL_H

#include "b2entity.h"

class Crystal : public B2Entity {
public:
	Crystal(int uniqueID, int width, int height, unsigned int textureID, b2World* world);
	~Crystal();

	void Update(double deltaTime);
	int GetUniqueID() { return uniqueID; }

	void Hit() { hit = true; }
	bool IsEnabled() { return enabled; }

	void SetColor(glm::vec4 color);
private:
	// Every crystal has its own uniqueID
	glm::vec4 activeColor;
	int uniqueID;
	bool hit;
	bool enabled;
};

#endif // !CRYSTAL_H
