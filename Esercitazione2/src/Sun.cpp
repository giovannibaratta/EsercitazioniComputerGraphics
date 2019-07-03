#include <math.h>
#include <iostream>

#include "../include/Sun.h"

Sun::Sun(vec4 position, float radius) :
	minRay(radius * 0.8),
	maxRay(radius * 1.2), radius(radius),
	rayColor(Colorable(1.0, 1.0, 1.0)), Sphere(position, radius)
{
}

void Sun::draw() {
	clock_t currentDraw = clock();

	// disegno la sfera interna
	Sphere::draw();

	// current time in ms (int value)
	int currentMs
		= static_cast<int>(round(static_cast<double>(currentDraw) / (CLOCKS_PER_SEC / 1000)));
	// in base al tempo passato dall'inizio calcolo % di animazione e stato. Lo stato è
	// allungo i raggi pari/accorcio quelli dispari o accorcio i raggi pari e allungo
	// quelli dispari
	float animationPercentage =
		(currentMs % ANIMATION_DURATION) / static_cast<float>(ANIMATION_DURATION);
	bool animationPhase = (currentMs / ANIMATION_DURATION) % 2 == 0;
	// disegno tutti i raggi
	drawRays(
		animationPhase == 0 ? animationPercentage : 1 - animationPercentage
	);
}

void Sun::drawRays(float size) {
	glPushMatrix();
	glMatrixMode(GL_MODELVIEW);
	glColor3f(rayColor.getRedColor(), rayColor.getGreenColor(), rayColor.getBlueColor());
	glTranslatef(position.x, position.y, position.z + 0.05);
	glBegin(GL_LINES);

	float evenHalfSegment = (minRay * size + (1 - size) * maxRay) / 2;
	float oddHalfSegment = (minRay * (1 - size) + size * maxRay) / 2;

	float angle = 0;
	float offset = radius + GAP_SUN_RAYS + maxRay/2;
	for( int i = 0; i < NUMBER_OF_RAYS; i += 2){
		
		glVertex2f((offset - evenHalfSegment) * cos(angle), (offset - evenHalfSegment) * sin(angle));
		glVertex2f((offset + evenHalfSegment) * cos(angle), (offset + evenHalfSegment) * sin(angle));
		angle += ANGLE_STEP * 2;
	}

	angle = ANGLE_STEP;
	for (int i = 1; i < NUMBER_OF_RAYS; i += 2) {
		glVertex2f((offset - oddHalfSegment) * cos(angle), (offset - oddHalfSegment) * sin(angle));
		glVertex2f((offset + oddHalfSegment) * cos(angle), (offset + oddHalfSegment) * sin(angle));
		angle += ANGLE_STEP * 2;
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
