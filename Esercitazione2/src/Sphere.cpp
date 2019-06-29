#include "../include/Sphere.h"
#include <math.h>
#include "../include/utils.h"

Sphere::Sphere(vec4 position, float radius)
	: radius(radius), mainColor(Colorable(1.0, 1.0, 1.0)), BaseObject(position)
{
}

void Sphere::setMainColor(float r, float g, float b) {
	mainColor.setColor(r, g, b);
}

void Sphere::init() {

	float angleStep = (2 * PI) / NUMBER_OF_PIECES;
	int numberOfVertex = NUMBER_OF_PIECES * 9;
	float* vertices = new float[numberOfVertex];
	float angle = 0;
	
	for (int i = 0; i < NUMBER_OF_PIECES; i++) {
		/* Il primo vertice del triangolo è sempre il cerchio */
		vertices[i * 9 + 0] = this->getX();
		vertices[i * 9 + 1] = this->getY();
		vertices[i * 9 + 2] = this->getZ();

		vertices[i * 9 + 3] = this->getX() + radius * cos(angle);
		vertices[i * 9 + 4] = this->getY() + radius * sin(angle);
		vertices[i * 9 + 5] = this->getZ();

		angle += angleStep;

		vertices[i * 9 + 6] = this->getX() + radius * cos(angle);
		vertices[i * 9 + 7] = this->getY() + radius * sin(angle);
		vertices[i * 9 + 8] = this->getZ();
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

void Sphere::draw() {
	glEnableClientState(GL_VERTEX_ARRAY);
	glColor3f(mainColor.getRed(), mainColor.getGreen(), mainColor.getBlue());
	// attivo il vbo
	glBindBuffer(GL_ARRAY_BUFFER, vboID);
	glVertexPointer(3, GL_FLOAT, 0, (char *)NULL);
	glDrawArrays(GL_TRIANGLES, 0, 9 * NUMBER_OF_PIECES);
	// disattivo il vbo
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glDisableClientState(GL_VERTEX_ARRAY);
}
