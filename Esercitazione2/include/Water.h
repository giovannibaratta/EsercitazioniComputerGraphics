#pragma once
#include "BaseObject.h"
#include "Colorable.h"
#include "Movable.h"
#include "BoundingBox.h"
#include "Triangle.h"
#include "Sphere.h"

/**
	Permette di disegnare una goccia. La goccia è composta da una sfera inferiore ed un
	triangolo superiore. La bouding box include solo la sfera inferiore.
*/
class Water :
	public Colorable, public Movable, public BoundingBox
{
private:
	Sphere *bottom;
	Triangle *top;
	/* dimensione della goccia */
	float size;
	vec4 bottomOffset, topOffset;

public:
	virtual void init();
	virtual void draw();
	virtual void cleanUp();
	virtual void setColor(float r, float g, float b);
	virtual void move(vec4 position);
	Water(vec4 position, float size);
};

