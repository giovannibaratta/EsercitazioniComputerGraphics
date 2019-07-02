#include <GL/glew.h>

#include "Movable.h"
#include "BoundingBox.h"
#include "Colorable.h"
#pragma once

namespace GameObjects {
	class Rectangle : public Movable, public Colorable, public BoundingBox
	{

	protected:
		float width;
		float height;
		GLuint rectangleVboID;
		float rectangleVertices[12];
		void computeVertices(vec4 position, float width, float height);
				
	public:
		Rectangle(vec4 position, float width, float height );
		virtual void draw();
		virtual void init();
		virtual void cleanUp();
		virtual void move(vec4 position);
	};
}

