/*#include "shape.h"

Shape::Shape() {

}

Shape::~Shape() {

}

void Shape::Draw() {
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}

void Shape::CreateBox(int w, int h, bool dyn, b2World* world) {
	b2BodyDef bodydef;
	bodydef.position.Set(0, 0);
	if (dyn) {
		bodydef.type = b2_dynamicBody;
	}
	else {
		bodydef.type = b2_staticBody;
	}

	// Step 2 create a body
	body = world->CreateBody(&bodydef);

	// Step 3 create shape
	b2PolygonShape shape;
	// the reason for dividing by 2 is because box2D draws from the center
	shape.SetAsBox(w / 2 * Configure::P2M, h / 2 * Configure::P2M);

	// step 4 create fixture
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &shape;
	fixtureDef.density = 1.0;
	fixtureDef.friction = 0.3f;
	fixtureDef.restitution = 0.5f;
	fixture = body->CreateFixture(&fixtureDef);

	dr = new DebugRenderer(Configure::projection, glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
		for (int i = 0; i < 4; i++) {
			point[i] = ((b2PolygonShape*)body->GetFixtureList()->GetShape())->m_vertices[i];
			//std::cout << "point " << i << ": (" << point[i].x << ") (" << point[i].y << ")" << std::endl;
		}
		dr->DrawBox(point);
		dr->Init();

		float vertices[] = {
			// position
			point[0].x, point[0].y, 0.0f, 0.0f,  // lower-left corner
			point[1].x, point[1].y, 1.0f, 0.0f,  // lower-right corner
			point[2].x, point[2].y, 1.0f, 1.0f,  // upper-right corner
			point[3].x, point[3].y, 0.0f, 1.0f  // uper left corner
		};

		unsigned int indices[] = {
			0, 1, 3,
			1, 2, 3
		};

		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);
		glGenBuffers(1, &EBO);

		glBindVertexArray(VAO);

		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

		// set the vertices
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid*)0);
		glEnableVertexAttribArray(0);

		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid*)(2 * sizeof(GLfloat)));
		glEnableVertexAttribArray(1);

		glBindVertexArray(0);
}
*/
