#pragma once
#include <GL/glew.h>
#include <GL/freeglut.h>

#include "Colorable.h"
#include "BaseObject.h"
#include "utils.h"

class Sphere : public BaseObject, public Colorable
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

