#pragma once
#include <GL/glew.h>
#include <GL/freeglut.h>

#include "Colorable.h"
#include "utils.h"
#include "Movable.h"

/**
	Permette di creare una sfera. La sfera si può spostare e colorare.
*/
class Sphere : public Colorable, public Movable
	{
	private:
		/* Numero di triangoli da utilizzare per disegnare la sfera */
		static const int NUMBER_OF_PIECES = 45;
		/* Angolo tra un lato di un triangolo e l'altro */
		const float ANGLE_STEP = (2 * PI) / NUMBER_OF_PIECES;
		/* raggio della sfera */
		float radius;
		/* id del vbo*/
		GLuint vboID;

	public:
		/** position il centro della sfera */
		Sphere(vec4 position, float radius);
		virtual void draw();
		virtual void init();
		virtual void cleanUp();
};

