#pragma once

#include "Colorable.h"
#include "Movable.h"

/**
	Permette di disegnare un triangolo equilatero
*/
class Triangle : public Colorable, public Movable
{

private:
	/* lunghezza del lato */
	float size;
	/* Vertici del triangolo */
	float triangleVertex[9];

public:
	/** position è il vertice iniziale, size è la lunghezza dei lati */
	Triangle(vec4 position, float size);
	virtual void draw();
	virtual void init();
};

