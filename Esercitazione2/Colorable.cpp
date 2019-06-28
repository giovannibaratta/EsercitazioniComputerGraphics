#include "Colorable.h"

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

float Colorable::getRed() {
	return color[0];
}

float Colorable::getBlue() {
	return color[2];
}

float Colorable::getGreen() {
	return color[1];
}

