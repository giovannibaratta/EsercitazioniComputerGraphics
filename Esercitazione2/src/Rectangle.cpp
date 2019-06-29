#include "../include/Rectangle.h"

MyRectangle::MyRectangle(float x, float y, float z, float width, float height) 
	: width(width), height(height), color(Colorable(1.0,1.0,1.0)), BaseObject(x, y, z)
{
	computeVertices(x, y, z, width, height);
}

void MyRectangle::computeVertices(float x, float y, float z, float width, float height) {
	// left - bottom
	rectangleVertices[0] = x;
	rectangleVertices[1] = y;
	rectangleVertices[2] = z;
	// right - bottom
	rectangleVertices[3] = x + width;
	rectangleVertices[4] = y;
	rectangleVertices[5] = z;
	// right - top
	rectangleVertices[6] = x + width;
	rectangleVertices[7] = y + height;
	rectangleVertices[8] = z;
	// left - top
	rectangleVertices[9] = x;
	rectangleVertices[10] = y + height;
	rectangleVertices[11] = z;
}


void MyRectangle::init() {
	// genero il buffer
	glGenBuffers(1, &rectangleVboID);
	// attivo il buffer
	glBindBuffer(GL_ARRAY_BUFFER, rectangleVboID);
	// carico nel buffer i dati
	glBufferData(GL_ARRAY_BUFFER, 3 * 4 * sizeof(float), rectangleVertices, GL_STATIC_DRAW);
	// rimuovo il binding
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void MyRectangle::setColor(float r, float g, float b) {
	color.setColor(r, g, b);
}

void MyRectangle::draw() {
	glEnableClientState(GL_VERTEX_ARRAY);
	glColor3f(color.getRed(), color.getGreen(), color.getBlue());
	glLineWidth(5);
	// attivo il vbo
	glBindBuffer(GL_ARRAY_BUFFER, rectangleVboID);
	glVertexPointer(3, GL_FLOAT, 0, (char *)NULL);
	glDrawArrays(GL_LINE_STRIP, 0, 2);
	// disattivo il vbo
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glDisableClientState(GL_VERTEX_ARRAY);
}
