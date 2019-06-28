#include "Rectangle.h"

MyRectangle::MyRectangle(float x, float y, float z, float width, float height) 
	: width(width), height(height), color(Colorable(1.0,1.0,1.0)), BaseObject(x, y, z)
{
	computeVbo(x, y, z, width, height);
}

void MyRectangle::computeVbo(float x, float y, float z, float width, float height) {
	rectangleVertex[0] = x;
	rectangleVertex[1] = y;
	rectangleVertex[2] = z;
	rectangleVertex[3] = x + width;
	rectangleVertex[4] = y;
	rectangleVertex[5] = z;
	rectangleVertex[6] = x + width;
	rectangleVertex[7] = y + height;
	rectangleVertex[8] = z;
	rectangleVertex[9] = x;
	rectangleVertex[10] = y + height;
	rectangleVertex[11] = z;
}


void MyRectangle::init() {
	// genero il buffer
	glGenBuffers(1, &rectangleVboID);
	// attivo il buffer
	glBindBuffer(GL_ARRAY_BUFFER, rectangleVboID);
	// carico nel buffer i dati
	glBufferData(GL_ARRAY_BUFFER, 12 * sizeof(float), rectangleVertex, GL_STATIC_DRAW);
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
	glDrawArrays(GL_QUADS, 0, 12);
	// disattivo il vbo
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glDisableClientState(GL_VERTEX_ARRAY);
}
