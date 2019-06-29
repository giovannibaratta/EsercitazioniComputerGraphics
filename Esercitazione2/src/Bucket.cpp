#include "../include/Bucket.h"

Bucket::Bucket(float x, float y, float z, float width, float height) 
	: width(width), height(height), color(Colorable(1.0,1.0,1.0)), BaseObject(x,y,z)
{
	computeVertices(x, y, z, width, height);
}

void Bucket::computeVertices(float x, float y, float z, float width, float height) {
	rectangleVertices[0] = x;
	rectangleVertices[1] = y;
	rectangleVertices[2] = z;
	rectangleVertices[3] = x + width;
	rectangleVertices[4] = y;
	rectangleVertices[5] = z;

	rectangleVertices[6] = x + width;
	rectangleVertices[7] = y;
	rectangleVertices[8] = z;
	rectangleVertices[9] = x + width;
	rectangleVertices[10] = y + height;
	rectangleVertices[11] = z;

	rectangleVertices[12] = x + width;
	rectangleVertices[13] = y + height;
	rectangleVertices[14] = z;
	rectangleVertices[15] = x;
	rectangleVertices[16] = y + height;
	rectangleVertices[17] = z;

	rectangleVertices[18] = x;
	rectangleVertices[19] = y + height;
	rectangleVertices[20] = z;
	rectangleVertices[21] = x;
	rectangleVertices[22] = y;
	rectangleVertices[23] = z;
}


void Bucket::init() {
	// genero il buffer
	glGenBuffers(1, &rectangleVboID);
	// attivo il buffer
	glBindBuffer(GL_ARRAY_BUFFER, rectangleVboID);
	// carico nel buffer i dati
	glBufferData(GL_ARRAY_BUFFER, 24 * sizeof(float), rectangleVertices, GL_STATIC_DRAW);
	// rimuovo il binding
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Bucket::setColor(float r, float g, float b) {
	color.setColor(r, g, b);
}

void Bucket::draw() {
	glEnableClientState(GL_VERTEX_ARRAY);
	//glColor3f(color.getRed(), color.getGreen(), color.getBlue());
	
	glLineWidth(2);
	// attivo il vbo
	glBindBuffer(GL_ARRAY_BUFFER, rectangleVboID);
	glVertexPointer(3, GL_FLOAT, 0, (char *)NULL);
	glColor4f(1.0, 1.0, 1.0, 0.0);
	glDrawArrays(GL_LINES, 0, 2);
	glColor3f(color.getRed(), color.getGreen(), color.getBlue());
	glDrawArrays(GL_LINES, 2, 6);
	// disattivo il vbo
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	if (currentLevel == 0) {
		glColor4f(0.0, 0.0, 1.0, 1.0);
		glBegin(GL_QUADS);
		glVertex2d(rectangleVertices[0] + 2.5 , rectangleVertices[1] + height - 2.5);
		glVertex2d(rectangleVertices[0] + width - 2.5, rectangleVertices[1] + height - 2.5);
		glVertex2d(rectangleVertices[0] + width - 2.5 , rectangleVertices[1] + 2.5);
		glVertex2d(rectangleVertices[0] + 2.5, rectangleVertices[1] + 2.5);
		glEnd();
	}

	glDisableClientState(GL_VERTEX_ARRAY);
}