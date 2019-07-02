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


bool RandomGenerator::init = false;
RandomGenerator* RandomGenerator::pointer = NULL;


RandomGenerator::RandomGenerator()
	: generator(random_device()())
{	
}

int RandomGenerator::generateValue(int minValue, int maxValue) {
	std::uniform_int_distribution<int> dist(minValue, maxValue);
	return dist(generator);
}

RandomGenerator* RandomGenerator::getGenerator() {
	if (!init)
		RandomGenerator::pointer = new RandomGenerator();
	return RandomGenerator::pointer;
}