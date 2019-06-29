#pragma once
#include "BaseObject.h"
#include <GL/glew.h>
#include <GL/freeglut.h>

class Triangle :
	public BaseObject
{

GLuint triangleVboID;
float triangleVertex[9];

public:
	Triangle(float x, float y, float z);
	virtual void draw();
	virtual void init();
	//~Triangle();
};

