#ifndef RAYCASTCALLBACK_H
#define RAYCASTCALLBACK_H

#include "b2entity.h"

#include "shader.h"
#include "window.h"

#include <GL/glew.h>
#include <glm-0.9.8.4/glm/glm.hpp>
#include <glm-0.9.8.4/glm/gtc/matrix_transform.hpp>
#include <glm-0.9.8.4/glm/gtc/type_ptr.hpp>
#include <Box2D/Box2D.h>

struct RaycastOutput {
	b2Fixture* fixture = nullptr;
	b2Vec2 point = b2Vec2(0.0f, 0.0f);
	b2Vec2 normal = b2Vec2(0.0f, 0.0f);
	float32 fraction = 0.0f;
};

class RayCastCallBack : public b2RayCastCallback {
public:
	RayCastCallBack(B2Entity* user);
	~RayCastCallBack();

	// the points have to be in meters
	void CreateLine(float length, float width, Camera* camera, Shader* shader, glm::vec4 color);
	void Draw(glm::vec2 position, float angle);

	float32 ReportFixture(b2Fixture* fixture, const b2Vec2& point, const b2Vec2& normal, float32 fraction);
	RaycastOutput GetOutput();
private:
	B2Entity* user;
	RaycastOutput ro;
	float lineWidth;
	Camera* camera;
	Shader* shader;
	glm::vec4 color;
	GLuint VBO, VAO;
};

#endif // !RAYCASTCALLBACK_H
