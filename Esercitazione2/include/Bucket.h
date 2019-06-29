#pragma once
#include "Rectangle.h"
class Bucket :
	public BaseObject
{
	const int MAX_CAPACITY = 4;

protected:
	float width;
	float height;
	GLuint rectangleVboID;
	float rectangleVertices[24];
	Colorable color;
	int currentLevel = 0;
	void computeVertices(float x, float y, float z, float width, float height);

public:
	Bucket(float x, float y, float z, float width, float height);
	virtual void draw();
	virtual void init();
	void setColor(float r, float g, float b);
};

