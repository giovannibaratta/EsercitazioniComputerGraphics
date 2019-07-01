#include <GL/glew.h>
#include "BaseObject.h"
#include "Colorable.h"
#pragma once

namespace GameObjects {
	class Rectangle : public BaseObject, public Colorable
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
	};
}

