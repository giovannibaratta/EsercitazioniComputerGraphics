#include <iostream>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include "../include/Triangle.h"
#include "../include/utils.h"


Triangle::Triangle(vec4 position, float size) :
	size(size), Colorable(1.0,1.0,1.0), BaseObject(position)
{
}


void Triangle::init() {
	triangleVertex[0] = 0;
	triangleVertex[1] = 0;
	triangleVertex[2] = 0;
	triangleVertex[3] = size;
	triangleVertex[4] = 0;
	triangleVertex[5] = 0;

	triangleVertex[6] = size / 2;
	triangleVertex[7] = sqrt(3) * size / 2;
	triangleVertex[8] = 0;
}


void Triangle::draw() {

	glPushMatrix();
	glColor3f(color[0], color[1], color[2]);
	glMatrixMode(GL_MODELVIEW);
	glTranslatef(position.x, position.y, position.z);
	glBegin(GL_POLYGON);
	for (int i = 0; i < 9; i = i + 3 )
		glVertex3f(triangleVertex[i], triangleVertex[i + 1], triangleVertex[i + 2]);
	glEnd();
	glPopMatrix();
}