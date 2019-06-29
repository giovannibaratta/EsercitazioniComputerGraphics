#include "../include/SmoothTransition.h"

SmoothTransition::SmoothTransition(Movable* movable)
	: movable(movable) {
	//target = movable.
	speed = 0;
}

SmoothTransition::~SmoothTransition() {

}

