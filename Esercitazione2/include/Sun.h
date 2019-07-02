#pragma once
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <time.h>

#include "Sphere.h"
#include "utils.h"

class Sun :	public Sphere
{

private:
	const static int NUMBER_OF_RAYS = 8;
	const float ANGLE_STEP = 2 * PI / NUMBER_OF_RAYS;
	const static int GAP_SUN_RAYS = 1;
	// durata animazione in ms
	const static int ANIMATION_DURATION = 2000;
	float animation = 0;
	// stato animazione, true espando il raggio, falso lo riduco
	bool increasing;

	float radius;
	// colore del raggio del sole
	Colorable rayColor;
	// lunghezza minima raggio del sole
	float minRay;
	// lunghezza massima raggio del sole
	float maxRay;

	// size tra 0 e 1
	void drawRays(float size);

public:
	Sun(vec4 position, float radius);
	void draw();
	void init();
	void setRayColor(float r, float g, float b);
};

