#include "BaseObject.h"
#include <iostream>

BaseObject::BaseObject(float x, float y, float z)
{
	_x = x;
	_y = y;
	_z = z;
}


/*
BaseObject::~BaseObject()
{
}*/

void BaseObject::worldUpdate() {

}

void BaseObject::passiveMotion() {

}

void BaseObject::init() {

}

void BaseObject::windowResize(int width, int height) {

}

void BaseObject::draw() {
	std::cout << "Base called";
}

float BaseObject::getX() {
	return _x;
}

float BaseObject::getY() {
	return _y;
}

float BaseObject::getZ() {
	return _z;
}

