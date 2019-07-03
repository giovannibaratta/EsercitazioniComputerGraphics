#pragma once
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <time.h>

#include "Sphere.h"
#include "utils.h"

/**
	Permette di creare un sole con dei raggi animati.
*/
class Sun :	public Sphere
{

private:
	/* Numero di raggi da disegnare */
	const static int NUMBER_OF_RAYS = 8;
	/* angolo tra un raggio e il successivo */
	const float ANGLE_STEP = 2 * PI / NUMBER_OF_RAYS;
	/* distanza tra il raggio di lunghezza massima e la sfera centrale */
	const static int GAP_SUN_RAYS = 1;
	/* durata animazione in ms dei raggi */
	const static int ANIMATION_DURATION = 2000;

	/* raggio della sfera centrale */
	float radius;
	/* colore del raggio del sole */
	Colorable rayColor;
	/* lunghezza minima raggio del sole */
	float minRay;
	/* lunghezza massima raggio del sole */
	float maxRay;

	/* Disegna i raggi del sole, alterna un raggio lungo ad un corto. La dimensione
	effettiva dei raggi dipende da size (deve essere tra 0 e 1). Size viene usata per
	animare i raggi, con size = 0 i raggi pari sono di lunghezza minima e i raggi dispari
	di lunghezza massima, con size = 1, i raggi pari sono di lunghezza massima e i raggi
	dispari di lugnhezza minima */ 
	void drawRays(float size);

public:
	Sun(vec4 position, float radius);
	void draw();
	void init();
	/* Imposta il colore dei raggi (solo dei raggi non della sfera) */
	void setRayColor(float r, float g, float b);
};

