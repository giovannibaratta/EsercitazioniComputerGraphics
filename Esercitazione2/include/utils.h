#pragma once
#include <glm/glm.hpp>
#include <string>

#include <random>

using namespace std;
using namespace glm;

constexpr auto PI = 3.14159265358979323846;

double degreeToRadians(double degree);
string vec4ToString(vec4 position);

class RandomGenerator {

public:
	static RandomGenerator* getGenerator();
	int generateValue(int minValue, int maxValue);

private:
	mt19937 generator;
	RandomGenerator();
	static bool init;
	static RandomGenerator* pointer;

};