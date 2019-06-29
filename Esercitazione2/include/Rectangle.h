#include <GL/glew.h>
#include "BaseObject.h"
#include "Colorable.h"
#pragma once
class MyRectangle :
	public BaseObject
{
protected: 
	float width;
	float height;
	GLuint rectangleVboID;
	float rectangleVertices[12];
	Colorable color;
	void computeVertices(float x, float y, float z, float width, float height);
public:
	MyRectangle(float x, float y, float z, float width, float height);
	virtual void draw();
	virtual void init();
	void setColor(float r, float g, float b);
};

