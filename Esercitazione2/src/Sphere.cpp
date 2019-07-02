#include <math.h>
#include <iostream>

#include "../include/Sphere.h"

using namespace std;

Sphere::Sphere(vec4 position, float radius)
	: radius(radius), Colorable(1.0,1.0,1.0), Movable(position)
{
}


void Sphere::init() {

	int numberOfVertex = NUMBER_OF_PIECES * 9;
	float* vertices = new float[numberOfVertex];
	float angle = 0;
	
	for (int i = 0; i < NUMBER_OF_PIECES; i++) {
		/* Il primo vertice del triangolo è sempre il cerchio */
		vertices[i * 9 + 0] = 0;
		vertices[i * 9 + 1] = 0;
		vertices[i * 9 + 2] = 0;

		vertices[i * 9 + 3] = radius * cos(angle);
		vertices[i * 9 + 4] = radius * sin(angle);
		vertices[i * 9 + 5] = 0;

		angle += ANGLE_STEP;

		vertices[i * 9 + 6] = radius * cos(angle);
		vertices[i * 9 + 7] = radius * sin(angle);
		vertices[i * 9 + 8] = 0;
	}

	// genero il buffer
	glGenBuffers(1, &vboID);
	// attivo il buffer
	glBindBuffer(GL_ARRAY_BUFFER, vboID);
	// carico nel buffer i dati
	glBufferData(GL_ARRAY_BUFFER, numberOfVertex * sizeof(float), vertices, GL_STATIC_DRAW);
	// rimuovo il binding
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Sphere::cleanUp() {
	glDeleteBuffers(1, &vboID);
}

void Sphere::draw() {
	glPushMatrix();
	glMatrixMode(GL_MODELVIEW);
	glEnableClientState(GL_VERTEX_ARRAY);
	glColor3f(color[0], color[1], color[2]);
	glTranslatef(position.x, position.y, position.z);
	// attivo il vbo
	glBindBuffer(GL_ARRAY_BUFFER, vboID);
	glVertexPointer(3, GL_FLOAT, 0, (char *)NULL);
	glDrawArrays(GL_TRIANGLES, 0, 9 * NUMBER_OF_PIECES);
	// disattivo il vbo
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glDisableClientState(GL_VERTEX_ARRAY);
	glPopMatrix();
}
