#include "../include/Rectangle.h"

#include <iostream>

using namespace std;
using namespace GameObjects;

Rectangle::Rectangle(vec4 position, float width, float height) 
	: width(width), height(height), Colorable(1.0,1.0,1.0), BaseObject(position)
{
	computeVertices(position, width, height);
}

void Rectangle::computeVertices(vec4 position, float width, float height) {
	// left - bottom
	rectangleVertices[0] = 0;
	rectangleVertices[1] = 0;
	rectangleVertices[2] = 0;
	// right - bottom
	rectangleVertices[3] = width;
	rectangleVertices[4] = 0;
	rectangleVertices[5] = 0;
	// right - top
	rectangleVertices[6] = width;
	rectangleVertices[7] = height;
	rectangleVertices[8] = 0;
	// left - top
	rectangleVertices[9] = 0;
	rectangleVertices[10] = height;
	rectangleVertices[11] = 0;
}


void Rectangle::init() {
	// genero il buffer
	glGenBuffers(1, &rectangleVboID);
	// attivo il buffer
	glBindBuffer(GL_ARRAY_BUFFER, rectangleVboID);
	// carico nel buffer i dati
	glBufferData(GL_ARRAY_BUFFER, 3 * 4 * sizeof(float), rectangleVertices, GL_STATIC_DRAW);
	// rimuovo il binding
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	cout << "Rec ID" << rectangleVboID << "\n";
}

void Rectangle::draw() {
	glPushMatrix();
	glMatrixMode(GL_MODELVIEW);
	glEnableClientState(GL_VERTEX_ARRAY);
	glColor3f(color[0], color[1], color[2]);
	glTranslatef(position.x, position.y, position.z);
	// attivo il vbo
	glBindBuffer(GL_ARRAY_BUFFER, rectangleVboID);
	glVertexPointer(3, GL_FLOAT, 0, (char*)NULL);
	glDrawArrays(GL_QUADS, 0, 4);
	// disattivo il vbo
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glPopMatrix();
}

void Rectangle::cleanUp() {
	glDeleteBuffers(1, &rectangleVboID);
}
