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
	Triangle(vec4 position);
	virtual void draw();
	virtual void init();
	//~Triangle();
};

