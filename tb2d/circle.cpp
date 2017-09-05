#include "circle.h"

Circle::Circle(int x, int y, int radius, bool dynamic, float p2m, b2World* world) {
	// Step 1 defina a body
	b2BodyDef bodydef;
	bodydef.position.Set(x*p2m, y*p2m);
	if (dynamic) {
		bodydef.type = b2_dynamicBody;
	}
	else {
		bodydef.type = b2_staticBody;
	}

	// Step 2 create a body
	body = world->CreateBody(&bodydef);

	// Step 3 create shape
	b2CircleShape shape;
	shape.m_p.Set(0.0f, 0.0f);
	shape.m_radius = radius * p2m;


	// step 4 create fixture
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &shape;
	fixtureDef.density = 1.0;
	fixtureDef.friction = 0.3f;
	fixtureDef.restitution = 0.5f;
	body->CreateFixture(&fixtureDef);

	MeshData meshData;
	meshData = OBJloader::LoadObject("assets//circle.obj", true);

	std::cout << "Is textCoord true? " << meshData.hasTextCoord << std::endl;
	for (int i = 0; i < meshData.amountVertices; i++) {
		std::cout << "vertices[" << i << "] = " << meshData.vertices[i] << std::endl;
	}
	std::cout << "meshData.amountVertices = " << meshData.amountVertices / 5 << std::endl;

	mesh = new Mesh(meshData);
	/*glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// set the vertices
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);*/
}

Circle::~Circle()
{

}

void Circle::Draw()
{
	mesh->Draw();
}

glm::vec3 Circle::GetPositionInPixels(float m2p)
{
	glm::vec3 pos;
	pos = glm::vec3(body->GetPosition().x * m2p, body->GetPosition().y * m2p, 0.0f);
	return pos;
}

float Circle::GetAngle()
{
	float angle;
	angle = body->GetAngle();
	return angle;
}
