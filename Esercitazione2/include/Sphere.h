#pragma once
#include <GL/glew.h>
#include <GL/freeglut.h>

#include "Colorable.h"
#include "utils.h"
#include "Movable.h"

class Sphere : public Colorable, public Movable
	{
	private:
		static const int NUMBER_OF_PIECES = 45;
		const float ANGLE_STEP = (2 * PI) / NUMBER_OF_PIECES;
		float radius;
		GLuint vboID;

	public:
		Sphere(vec4 position, float radius);
		virtual void draw();
		virtual void init();
		virtual void cleanUp();
};

