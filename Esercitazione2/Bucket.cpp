#include "Bucket.h"

Bucket::Bucket(float x, float y, float z, float width, float height) 
	: width(width), height(height), color(Colorable(1.0,1.0,1.0)), BaseObject(x,y,z)
{
	computeVbo(x, y, z, width, height);
}

void Bucket::computeVbo(float x, float y, float z, float width, float height) {
	rectangleVertex[0] = x;
	rectangleVertex[1] = y;
	rectangleVertex[2] = z;
	rectangleVertex[3] = x + width;
	rectangleVertex[4] = y;
	rectangleVertex[5] = z;

	rectangleVertex[6] = x + width;
	rectangleVertex[7] = y;
	rectangleVertex[8] = z;
	rectangleVertex[9] = x + width;
	rectangleVertex[10] = y + height;
	rectangleVertex[11] = z;

	rectangleVertex[12] = x + width;
	rectangleVertex[13] = y + height;
	rectangleVertex[14] = z;
	rectangleVertex[15] = x;
	rectangleVertex[16] = y + height;
	rectangleVertex[17] = z;

	rectangleVertex[18] = x;
	rectangleVertex[19] = y + height;
	rectangleVertex[20] = z;
	rectangleVertex[21] = x;
	rectangleVertex[22] = y;
	rectangleVertex[23] = z;
}


void Bucket::init() {
	// genero il buffer
	glGenBuffers(1, &rectangleVboID);
	// attivo il buffer
	glBindBuffer(GL_ARRAY_BUFFER, rectangleVboID);
	// carico nel buffer i dati
	glBufferData(GL_ARRAY_BUFFER, 24 * sizeof(float), rectangleVertex, GL_STATIC_DRAW);
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
		glVertex2d(rectangleVertex[0] + 2.5 , rectangleVertex[1] + height - 2.5);
		glVertex2d(rectangleVertex[0] + width - 2.5, rectangleVertex[1] + height - 2.5);
		glVertex2d(rectangleVertex[0] + width - 2.5 , rectangleVertex[1] + 2.5);
		glVertex2d(rectangleVertex[0] + 2.5, rectangleVertex[1] + 2.5);
		glEnd();
	}

	glDisableClientState(GL_VERTEX_ARRAY);
}