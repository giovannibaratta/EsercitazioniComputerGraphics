#include "Sun.h"
#include "math.h"
#include "utils.h"
#include <iostream>



Sun::Sun(float x, float y, float radius) : 
	x(x), y(y), minRay(radius*0.75),
	maxRay(radius*1.25), radius(radius),
	lastDraw(clock()), rayColor(Colorable(1.0,1.0,1.0)),
	increasing(true), Sphere(x,y,0,radius)
{
}

void Sun::draw() {
	Sphere::draw();
	clock_t currentDraw = clock();
	float elapsedTime = ((double)currentDraw - lastDraw) / CLOCKS_PER_SEC;
	lastDraw = currentDraw;
	float step = elapsedTime * 0.5;

	std::cout << "Called " << step << " total " << animation << "\n";
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

	glColor3f(rayColor.getRed(), rayColor.getGreen(), rayColor.getBlue());
	glLineWidth(2);

	glPushMatrix();
	glTranslatef(x, y, 0);
	glBegin(GL_LINES);
	float angleStep = 2 * PI / NUMBER_OF_RAYS;
	float angle = 0;
	for (int i = 0; i < NUMBER_OF_RAYS; i++) {
		
		glVertex2f((radius + GAP_SUN_RAYS) * cos(angle) , (radius + GAP_SUN_RAYS)* sin(angle));
		float segmentLength = i % 2 == 0 
			? minRay * animation + (1 - animation) * maxRay
			: minRay * (1 - animation) + animation * maxRay;
		glVertex2f((radius + GAP_SUN_RAYS + segmentLength) * cos(angle), (radius + GAP_SUN_RAYS + segmentLength)* sin(angle));
		angle += angleStep;
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
