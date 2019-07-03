#include <math.h>
#include <sstream>

#include "../include/utils.h"

double degreeToRadians(double degree) {
	return (degree * 2 * PI) / 360.0;
}

string vec4ToString(vec4 position) {
	stringstream ss;
	ss << "(" << position.x << "," << position.y
			<< "," << position.z << "," << position.w << ")";
	return ss.str();
}


float RandomGenerator::generateFloatValue()
{
	if (floatCount >= CACHE_SIZE)
		updateFloatCache();
	return floatCache[floatCount++];
}

int RandomGenerator::generateIntValue()
{
	if (intCount >= CACHE_SIZE)
		updateIntCache();
	return intCache[intCount++];
}

void RandomGenerator::updateIntCache() {
	for (int i = 0; i < CACHE_SIZE; i++)
		intCache[i] = intDist(generator);
	intCount = 0;
}


void RandomGenerator::updateFloatCache() {
	for (int i = 0; i < CACHE_SIZE; i++)
		floatCache[i] = floatDist(generator);
	floatCount = 0;
}

RandomGenerator::RandomGenerator(float minValue, float maxValue)
	: generator(random_device()()),
	intDist(static_cast<int>(minValue), static_cast<int>(maxValue)),
	floatDist(minValue, maxValue), floatCount(0), intCount(0)
{
	updateIntCache();
	updateFloatCache();
}