#include <GL/glew.h>
#include "BaseObject.h"
#include "Colorable.h"
#pragma once

namespace GameObjects {
	class Rectangle :
		public BaseObject
	{
	protected:
		float width;
		float height;
		GLuint rectangleVboID;
		float rectangleVertices[12];
		Colorable color;
		void computeVertices(vec4 position, float width, float height);


	public:
		Rectangle(vec4 position, float width, float height);
		virtual void draw();
		virtual void init();
		void setColor(float r, float g, float b);
		void cleanUp();
	};
}

