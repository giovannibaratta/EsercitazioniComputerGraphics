#include<algorithm>
#include<iostream>

#include "../include/Bucket.h"


Bucket::Bucket(vec4 position, float width, float height, int maxCapacity)
	: width(width), height(height), maxCapacity(maxCapacity),
		Movable(position), Colorable(0.0,0.0,0.0)
{
	computeVertices(position, width, height);
}

void Bucket::cleanUp() {
	glDeleteBuffers(1, &outerVboID);
}

void Bucket::computeVertices(vec4 position, float width, float height) {

	outerVertices[0] = 0;
	outerVertices[1] = height;
	outerVertices[2] = 0;
	outerVertices[3] = 0;
	outerVertices[4] = 0;
	outerVertices[5] = 0;
	outerVertices[6] = width;
	outerVertices[7] = 0;
	outerVertices[8] = 0;
	outerVertices[9] = width;
	outerVertices[10] = height;
	outerVertices[11] = 0;

}

void Bucket::increaseLevel() {
	currentLevel = std::min(currentLevel + 1, maxCapacity);
	updateContentHeight();
}

void Bucket::decreaseLevel() {
	currentLevel = std::max(currentLevel - 1, 0);
	updateContentHeight();
}

void Bucket::updateContentHeight() {
	contentHeight = height * (static_cast<float> (currentLevel) / maxCapacity);
}

void Bucket::init() {
	// genero il buffer
	glGenBuffers(1, &outerVboID);
	// attivo il buffer
	glBindBuffer(GL_ARRAY_BUFFER, outerVboID);
	// carico nel buffer i dati
	glBufferData(GL_ARRAY_BUFFER, 3 * 4 * sizeof(float), outerVertices, GL_STATIC_DRAW);
	// rimuovo il binding
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Bucket::draw() {
	// recipiente
	glPushMatrix();
	glMatrixMode(GL_MODELVIEW);
	glEnableClientState(GL_VERTEX_ARRAY);
	glColor3f(color[0], color[1], color[2]);
	glLineWidth(2);
	glTranslatef(position.x, position.y, position.z);
	// attivo il vbo
	glBindBuffer(GL_ARRAY_BUFFER, outerVboID);
	glVertexPointer(3, GL_FLOAT, 0, (char *)NULL);
	glDrawArrays(GL_LINE_STRIP, 0, 4);
	// disattivo il vbo
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glDisableClientState(GL_VERTEX_ARRAY);

	// contenuto interno
	if (currentLevel > 0) {
		glColor4f(0.0, 0.0, 1.0, 1.0);
		glBegin(GL_QUADS);
		glVertex2d(0,0);
		glVertex2d(width, 0);
		glVertex2d(width, contentHeight);
		glVertex2d(0, contentHeight);
		
		glEnd();
	}
	glPopMatrix();
}