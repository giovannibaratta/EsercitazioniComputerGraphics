#include <GL/glew.h>

#include "Movable.h"
#include "BoundingBox.h"
#include "Colorable.h"
#pragma once

namespace GameObjects {
	/**
		Permette di creare un rettangolo non fisso, colorabile e con bouding box.
	*/
	class Rectangle : public Movable, public Colorable, public BoundingBox
	{

	protected:
		float width;
		float height;
		/** id del VBO del rettangolo */
		GLuint rectangleVboID;
		/** vertici del rettangolo */
		float rectangleVertices[12];
		/** Calcola i vertici del rettangolo */
		void computeVertices(vec4 position, float width, float height);
				
	public:
		/** Position è il vertice iniziale del rettangolo, il vertice opposto si trova a
		position + (width, height, 0.0, 0.0) */
		Rectangle(vec4 position, float width, float height );
		virtual void draw();
		virtual void init();
		virtual void cleanUp();
		virtual void move(vec4 position);
	};
}

