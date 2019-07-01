#include <math.h>
#include <iostream>

#include "../include/Sun.h"

Sun::Sun(vec4 position, float radius) : 
	minRay(radius*0.75),
	maxRay(radius*1.25), radius(radius),
	lastDraw(clock()), rayColor(Colorable(1.0,1.0,1.0)),
	increasing(true), Sphere(position,radius)
{
}

void Sun::draw() {
	clock_t currentDraw = clock();

	// disegno la sfera interna
	Sphere::draw();

	// tempo trascorso in ms
	float elapsedTime = ((double)currentDraw - lastDraw) / (CLOCKS_PER_SEC / 1000);
	lastDraw = currentDraw;

	float step = elapsedTime * 0.5;

	if (increasing) {
		// sto aumentando
		animation += step;
		if (animation > 1.0) {
			animation = 1.0;
			increasing = false;
		}
	}
	else {
		// sto tornando indietro
		animation -= step;
		if (animation < 0.0) {
			animation = 0.0;
			increasing = true;
		}
	}

	glPushMatrix();
	glLineWidth(2);
	glMatrixMode(GL_MODELVIEW);
	glTranslatef(position.x, position.y, position.z);
	glBegin(GL_LINES);
	
	float angle = 0;
	for (int i = 0; i < NUMBER_OF_RAYS; i++) {
		
		glVertex2f((radius + GAP_SUN_RAYS) * cos(angle) , (radius + GAP_SUN_RAYS)* sin(angle));
		float segmentLength = i % 2 == 0 
			? minRay * animation + (1 - animation) * maxRay
			: minRay * (1 - animation) + animation * maxRay;
		glVertex2f((radius + GAP_SUN_RAYS + segmentLength) * cos(angle), (radius + GAP_SUN_RAYS + segmentLength)* sin(angle));
		angle += ANGLE_STEP;
	}
	glEnd();
	glPopMatrix();
}

void Sun::init() {
	Sphere::init();
}

void Sun::setRayColor(float r, float g, float b) {
	rayColor.setColor(r, g, b);
}
