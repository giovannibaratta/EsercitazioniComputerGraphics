#include "BaseObject.h"
#include <GL/glew.h>
#include <GL/freeglut.h>
#include "Colorable.h"
#pragma once
class MyRectangle :
	public BaseObject
{
protected: 
	float width;
	float height;
	GLuint rectangleVboID;
	float rectangleVertex[12];
	Colorable color;
	void computeVbo(float x, float y, float z, float width, float height);
public:
	MyRectangle(float x, float y, float z, float width, float height);
	virtual void draw();
	virtual void init();
	void setColor(float r, float g, float b);
	void resize(int width, int height);
};

