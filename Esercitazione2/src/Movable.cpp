#include "../include/Movable.h"

Movable::Movable(vec4 position) : BaseObject(position)
{
}

void Movable::move(vec4 position) {
	this->position = position;
}