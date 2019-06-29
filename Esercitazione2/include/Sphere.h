#pragma once
#include "BaseObject.h"
#include <GL/glew.h>
#include <GL/freeglut.h>
#include "Colorable.h"

class Sphere :
	public BaseObject
{
	static const int NUMBER_OF_PIECES = 45;
	float radius;
	GLuint vboID;
	Colorable mainColor;

public:
	Sphere(float x, float y, float z, float radius);
	void draw();
	void init();
	void setMainColor(float r, float g, float b);
};

