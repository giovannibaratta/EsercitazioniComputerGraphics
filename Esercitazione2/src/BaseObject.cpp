#include <iostream>
#include <string>
#include <time.h>

#include "../include/BaseObject.h"
#include "../include/random/random.hpp"

using namespace std;
using Random = effolkronium::random_static;

BaseObject::BaseObject(float x, float y, float z)
	: x(x), y(y), z(z)
{
	clock_t startTime = clock();
	this->id = to_string(startTime) + "_" + to_string(Random::get(0, INT32_MAX));
}

void BaseObject::worldUpdate() {

}

void BaseObject::passiveMotion() {

}

void BaseObject::init() {

}

void BaseObject::draw() {
}

float BaseObject::getX() {
	return this->x;
}

float BaseObject::getY() {
	return this->y;
}

float BaseObject::getZ() {
	return this->z;
}

string BaseObject::getID()
{
	return this ->id;
}

