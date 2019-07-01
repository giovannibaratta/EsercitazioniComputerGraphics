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
