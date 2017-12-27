#include "raycast.h"

Raycast::Raycast(b2World* world) : b2RayCastCallback::b2RayCastCallback() {
	// Initialize all variables with a value to avoid conflicts
	this->world = world;
}

Raycast::~Raycast() {
	
}

void Raycast::Update(glm::vec2 startingPoint, glm::vec2 endPoint)
{
	this->startingPoint = startingPoint;
	this->endPoint = endPoint;
	hits.clear();
	world->RayCast(this, b2Vec2(startingPoint.x * B2Entity::p2m, startingPoint.y * B2Entity::p2m), b2Vec2(endPoint.x * B2Entity::p2m, endPoint.y * B2Entity::p2m));
	if (hits.size() > 0) {
		// Sort the hits by fraction from low to high
		// The square brackets specify which variables are "captured" by the lambda, and how (by value or reference).
		// More info on lambda's https://stackoverflow.com/questions/7627098/what-is-a-lambda-expression-in-c11
		std::sort(hits.begin(), hits.end(), [](RaycastHit a, RaycastHit b) { return a.fraction < b.fraction; });
	}
}

void Raycast::Draw(glm::vec3 color) {
	DebugRenderer::Line(startingPoint, endPoint, color);
}

float32 Raycast::ReportFixture(b2Fixture* fixture, const b2Vec2& point, const b2Vec2& normal, float32 fraction) {
	RaycastHit rh;
	rh.fixture = fixture;
	rh.point = glm::vec2(point.x * B2Entity::m2p, point.y * B2Entity::m2p);
	rh.normal = glm::vec2(normal.x, normal.y);
	rh.fraction = fraction;
	hits.push_back(rh);
	// We return 1 to trick box2D in continueing shooting the raycast
	return 1;
}