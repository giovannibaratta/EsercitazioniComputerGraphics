#include "../include/Triangle.h"
#include <sstream>
#include <iostream>


Triangle::Triangle(vec4 position) : BaseObject(position)
{
	triangleVertex[0] = position.x;
	triangleVertex[1] = position.y;
	triangleVertex[2] = position.z;
	triangleVertex[3] = position.x +0.2;
	triangleVertex[4] = position.y;
	triangleVertex[5] = position.z;
	triangleVertex[6] = position.x +0.1;
	triangleVertex[7] = position.y +0.1;
	triangleVertex[8] = position.z;
}


void Triangle::init() {
	// genero il buffer
	glGenBuffers(1, &triangleVboID);
	// attivo il buffer
	glBindBuffer(GL_ARRAY_BUFFER, triangleVboID);
	// carico nel buffer i dati
	glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(float), triangleVertex, GL_STATIC_DRAW);
	// rimuovo il binding
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}


void Triangle::draw() {
	glEnableClientState(GL_VERTEX_ARRAY);
	glColor3f(1.0, 0.0, 0.0);
	// attivo il vbo
	glBindBuffer(GL_ARRAY_BUFFER, triangleVboID);
	glVertexPointer(3, GL_FLOAT, 0, (char *)NULL);
	glDrawArrays(GL_TRIANGLES, 0, 9);
	// disattivo il vbo
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glDisableClientState(GL_VERTEX_ARRAY);
}