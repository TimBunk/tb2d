#ifndef CONFIGURE_H
#define CONFIGURE_H

#include <GL/glew.h>
#include <glm-0.9.8.4/glm/glm.hpp>
#include <glm-0.9.8.4/glm/gtc/matrix_transform.hpp>
#include <glm-0.9.8.4/glm/gtc/type_ptr.hpp>

class Configure {
public:
	static float M2P;
	static float P2M;
	static float screenWidth;
	static float screenHeight;
};

#endif // !CONFIGURE_H
