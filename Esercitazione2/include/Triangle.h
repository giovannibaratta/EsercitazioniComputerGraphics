#pragma once

#include "BaseObject.h"
#include "Colorable.h"

class Triangle : public BaseObject, public Colorable
{

private:
	float size;
	float triangleVertex[9];

public:
	Triangle(vec4 position, float size);
	virtual void draw();
	virtual void init();
};

