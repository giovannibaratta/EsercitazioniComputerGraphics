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

