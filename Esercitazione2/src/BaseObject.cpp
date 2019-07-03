#include <iostream>
#include <string>
#include <time.h>

#include "../include/BaseObject.h"
#include "../include/random/random.hpp"

using namespace std;
using Random = effolkronium::random_static;


BaseObject::BaseObject(vec4 position)
	: position(position)
{
	/* generazione dell'id basata sul clock + numero casuale */
	clock_t startTime = clock();
	this->id = to_string(startTime) + "_" + to_string(Random::get(0, INT32_MAX));
}

float BaseObject::getX() {
	return this->position.x;
}

float BaseObject::getY() {
	return this->position.y;
}

float BaseObject::getZ() {
	return this->position.z;
}

vec4 BaseObject::getPosition()
{
	return vec4(position);
}

string BaseObject::getID()
{
	return this ->id;
}

void BaseObject::cleanUp() {

}

