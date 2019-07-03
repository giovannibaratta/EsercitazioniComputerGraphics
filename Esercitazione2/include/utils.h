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
	float generateFloatValue();
	int generateIntValue();
	RandomGenerator(float minValue, float maxValue);

	void updateFloatCache();
	void updateIntCache();

private:
	static const int CACHE_SIZE = 10000;
	int floatCount;
	int intCount;
	float floatCache[CACHE_SIZE];
	int intCache[CACHE_SIZE];
	mt19937 generator;
	uniform_int_distribution<int> intDist;
	uniform_real_distribution<float> floatDist;	
};