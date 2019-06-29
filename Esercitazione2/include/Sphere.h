#pragma once
#include <GL/glew.h>
#include <GL/freeglut.h>
#include "Colorable.h"
#include "BaseObject.h"

class Sphere :
	public BaseObject
{
	static const int NUMBER_OF_PIECES = 45;
	float radius;
	GLuint vboID;
	Colorable mainColor;

public:
	Sphere(vec4 position, float radius);
	void draw();
	void init();
	void setMainColor(float r, float g, float b);
};

