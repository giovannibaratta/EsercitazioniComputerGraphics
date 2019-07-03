#include <iostream>

#include "../include/Water.h"
#include "../include/utils.h"

using namespace std;

void Water::init()
{
	bottom->init();
	top->init();
}

void Water::draw()
{
	bottom->draw();
	top->draw();
}

void Water::cleanUp()
{
	bottom->cleanUp();
	top->cleanUp();
	delete bottom;
	delete top;
}

void Water::setColor(float r, float g, float b)
{
	bottom->setColor(r, g, b);
	top->setColor(r, g, b);
}

void Water::move(vec4 position)
{
	Movable::move(position);
	bottom->move(position + bottomOffset);
	top->move(position + topOffset);
	updateBoundingBox(position, size * 2, size * 2);
}


Water::Water(vec4 position, float size) :
	size(size), Colorable(1.0,1.0,1.0),
	Movable(position),  BoundingBox(position, size * 2, size * 2, false)
{
	bottomOffset = vec4(size, size, 0.0, 0.0);
	topOffset = vec4(0, size * 1.15, 0.0, 0.0);
	bottom = new Sphere(position + bottomOffset, size);
	top = new Triangle(position + topOffset, size * 2);
}