#include "../include/Rectangle.h"

#include <iostream>

using namespace std;
using namespace GameObjects;

Rectangle::Rectangle(vec4 position, float width, float height) 
	: width(width), height(height), color(Colorable(1.0,1.0,1.0)), BaseObject(position)
{
	computeVertices(position, width, height);
}

void Rectangle::computeVertices(vec4 position, float width, float height) {
	// left - bottom
	rectangleVertices[0] = position.x;
	rectangleVertices[1] = position.y;
	rectangleVertices[2] = position.z;
	// right - bottom
	rectangleVertices[3] = position.x + width;
	rectangleVertices[4] = position.y;
	rectangleVertices[5] = position.z;
	// right - top
	rectangleVertices[6] = position.x + width;
	rectangleVertices[7] = position.y + height;
	rectangleVertices[8] = position.z;
	// left - top
	rectangleVertices[9] = position.x;
	rectangleVertices[10] = position.y + height;
	rectangleVertices[11] = position.z;
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
}

void Rectangle::setColor(float r, float g, float b) {
	color.setColor(r, g, b);
}

void Rectangle::draw() {
	glEnableClientState(GL_VERTEX_ARRAY);
	glColor3f(color.getRed(), color.getGreen(), color.getBlue());
	// attivo il vbo
	glBindBuffer(GL_ARRAY_BUFFER, rectangleVboID);
	glVertexPointer(3, GL_FLOAT, 0, (char*)NULL);
	glDrawArrays(GL_QUADS, 0, 4);
	// disattivo il vbo
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Rectangle::cleanUp() {
	glDeleteBuffers(1, &rectangleVboID);
}
