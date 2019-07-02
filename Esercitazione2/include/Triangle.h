#pragma once

#include "Colorable.h"
#include "Movable.h"

class Triangle : public Colorable, public Movable
{

private:
	float size;
	float triangleVertex[9];

public:
	Triangle(vec4 position, float size);
	virtual void draw();
	virtual void init();
};

