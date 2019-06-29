#include<algorithm>
#include<iostream>

#include "../include/Bucket.h"


Bucket::Bucket(vec4 position, float width, float height) 
	: width(width), height(height), Movable(position), Colorable(0.0,0.0,0.0)
{
	computeVertices(position, width, height);
}

void Bucket::computeVertices(vec4 position, float width, float height) {

	rectangleVertices[0] = position.x;
	rectangleVertices[1] = position.y - height;
	rectangleVertices[2] = position.z;
	rectangleVertices[3] = position.x;
	rectangleVertices[4] = position.y;
	rectangleVertices[5] = position.z;
	rectangleVertices[6] = position.x + width;
	rectangleVertices[7] = position.y;
	rectangleVertices[8] = position.z;
	rectangleVertices[9] = position.x + width;
	rectangleVertices[10] = position.y - height;
	rectangleVertices[11] = position.z;

}

void Bucket::increaseLevel() {
	currentLevel = std::min(currentLevel + 1, MAX_CAPACITY);
	updateContentHeight();
}

void Bucket::decreaseLevel() {
	currentLevel = std::max(currentLevel - 1, 0);
	updateContentHeight();
}

void Bucket::updateContentHeight() {
	contentHeight = height * (static_cast<float> (currentLevel) / MAX_CAPACITY);
}

void Bucket::init() {
	// genero il buffer
	glGenBuffers(1, &rectangleVboID);
	// attivo il buffer
	glBindBuffer(GL_ARRAY_BUFFER, rectangleVboID);
	// carico nel buffer i dati
	glBufferData(GL_ARRAY_BUFFER, 3 * 4 * sizeof(float), rectangleVertices, GL_STATIC_DRAW);
	// rimuovo il binding
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}


void Bucket::move(vec4 position) {
	Movable::move(position);
	glInvalidateBufferData(rectangleVboID);
	glBindBuffer(GL_ARRAY_BUFFER, rectangleVboID);
	computeVertices(position, width, height);
	glBufferData(GL_ARRAY_BUFFER, 3 * 4 * sizeof(float), rectangleVertices, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Bucket::draw() {

	// recipiente
	glEnableClientState(GL_VERTEX_ARRAY);
	glColor3f(this->getRed(), this->getGreen(), this->getBlue());
	
	glLineWidth(2);
	// attivo il vbo
	glBindBuffer(GL_ARRAY_BUFFER, rectangleVboID);
	glVertexPointer(3, GL_FLOAT, 0, (char *)NULL);

	glDrawArrays(GL_LINE_STRIP, 0, 4);
	// disattivo il vbo
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glDisableClientState(GL_VERTEX_ARRAY);

	// contenuto interno
	if (currentLevel > 0) {
		glColor4f(0.0, 0.0, 1.0, 1.0);
		glBegin(GL_QUADS);
		glVertex2d(rectangleVertices[3], rectangleVertices[4]);
		glVertex2d(rectangleVertices[3] + width, rectangleVertices[4]);
		glVertex2d(rectangleVertices[3] + width, rectangleVertices[4] - contentHeight);
		glVertex2d(rectangleVertices[3], rectangleVertices[4] - contentHeight);
		
		glEnd();
	}
}