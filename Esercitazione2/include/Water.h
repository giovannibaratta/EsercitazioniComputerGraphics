#pragma once
#include "BaseObject.h"
#include "Colorable.h"
#include "Movable.h"
#include "BoundingBox.h"
#include "Triangle.h"
#include "Sphere.h"

class Water :
	public Colorable, public Movable, public BoundingBox
{
private:
	Sphere *bottom;
	Triangle *top;
	float size;

public:
	virtual void init();
	virtual void draw();
	virtual void cleanUp();
	virtual void setColor(float r, float g, float b);
	virtual void move(vec4 position);
	Water(vec4 position, float size);
};

