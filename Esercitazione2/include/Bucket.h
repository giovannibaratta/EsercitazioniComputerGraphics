#pragma once
#include <GL/glew.h>
#include <GL/freeglut.h>

#include "Movable.h"
#include "Colorable.h"

class Bucket :
	public Movable, public Colorable
{

private:
	const int MAX_CAPACITY = 4;
	int currentLevel = 0;
	float contentHeight = 0;
	void computeVertices(vec4 position, float width, float height);
	void updateContentHeight();

protected:
	float width;
	float height;
	GLuint rectangleVboID;
	float rectangleVertices[12];

public:
	Bucket(vec4 position, float width, float height);
	virtual void move(vec4 position);
	virtual void draw();
	virtual void init();
	void increaseLevel();
	void decreaseLevel();
};

