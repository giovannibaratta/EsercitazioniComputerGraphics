#pragma once

#include <glm/glm.hpp>

using namespace glm;

class BoundingBox
{
private:
	vec4 boundingBox;
	float width, height;
	bool collisionEnabled;

protected:
	void updateBoundingBox(vec4 bb, float width, float height);

public:
	bool inCollisionWith(BoundingBox otherBb);
	void enableCollision();
	void disableCollision();
	BoundingBox(vec4 boundingBox, float width, float height, bool enableCollision);
};
