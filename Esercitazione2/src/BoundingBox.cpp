#include <math.h>

#include "../include/BoundingBox.h"

using namespace std;

void BoundingBox::updateBoundingBox(vec4 bb, float width, float height)
{
	boundingBox = bb;
	this->width = width;
	this->height = height;
}

bool BoundingBox::inCollisionWith(BoundingBox otherBb)
{
	if(collisionEnabled == false || otherBb.collisionEnabled == false)
		return false;

	float minX, otherX, minWidth, otherWidth;
	float minY, otherY, minHeight, otherHeight;

	/* Calcolo la bouding box con coordinata x e y minore (separatamente) e verifico
	se l'altra è compresa tra la coordinata + la rispettiva dimension. Se sia in x che in
	y si sovrappongono c'è una collisione */
	if (boundingBox.x < otherBb.boundingBox.x) {
		minX = boundingBox.x;
		minWidth = width;
		otherX = otherBb.boundingBox.x;
		otherWidth = otherBb.width;
	}
	else {
		minX = otherBb.boundingBox.x;
		minWidth = otherBb.width;
		otherX = boundingBox.x;
		otherWidth = width;
	}

	if (boundingBox.y < otherBb.boundingBox.y) {
		minY = boundingBox.y;
		minHeight = height;
		otherY = otherBb.boundingBox.y;
		otherHeight = otherBb.height;
	}
	else {
		minY = otherBb.boundingBox.y;
		minHeight = otherBb.height;
		otherY = boundingBox.y;
		otherHeight = height;
	}

	return minX + minWidth >= otherX && minY + minHeight > otherY;
}

void BoundingBox::enableCollision()
{
	collisionEnabled = true;
}

void BoundingBox::disableCollision()
{
	collisionEnabled = false;
}

BoundingBox::BoundingBox(vec4 boundingBox, float width, float height, bool enableCollision) :
	collisionEnabled(enableCollision), boundingBox(boundingBox), width(width), height(height)
{
}
