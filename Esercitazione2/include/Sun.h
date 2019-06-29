#pragma once
#include "Sphere.h"
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <time.h>

class Sun :
	public Sphere
{
	const static int NUMBER_OF_RAYS = 8;
	const static int GAP_SUN_RAYS = 5;

	float x, y;
	float radius;
	float animation = 0;
	GLuint vboID;
	Colorable rayColor;
	float minRay;
	float maxRay;
	clock_t lastDraw;
	bool increasing;

public:
	Sun(float x, float y, float radius);
	void draw();
	void init();
	void setRayColor(float r, float g, float b);
};

