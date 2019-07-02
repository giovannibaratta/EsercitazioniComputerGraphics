#pragma once
#include <GL/glew.h>
#include <GL/freeglut.h>

#include "Movable.h"
#include "Colorable.h"
#include "BoundingBox.h"

class Bucket : public Movable, public Colorable, public BoundingBox
{

private:
	int maxCapacity;
	int currentLevel = 0;
	float contentHeight = 0;
	void computeVertices(vec4 position, float width, float height);
	void updateContentHeight();

protected:
	float width;
	float height;
	GLuint outerVboID;
	float outerVertices[12];

public:
	Bucket(vec4 position, float width, float height, int maxCapacity);
	virtual void draw();
	virtual void init();
	virtual void move(vec4 position);
	virtual void cleanUp();
	void increaseLevel();
	void decreaseLevel();
};

