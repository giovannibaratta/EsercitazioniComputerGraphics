#include "../include/Colorable.h"

Colorable::Colorable(float r, float g, float b)
{
	color[0] = r;
	color[1] = g;
	color[2] = b;
}

void Colorable::setColor(float r, float g, float b){
	color[0] = r;
	color[1] = g;
	color[2] = b;
}

float Colorable::getRedColor()
{
	return color[0];
}

float Colorable::getGreenColor()
{
	return color[1];
}

float Colorable::getBlueColor()
{
	return color[2];
}
