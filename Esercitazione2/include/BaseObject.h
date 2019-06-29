#pragma once
#include <string>
#include <glm/glm.hpp>

using namespace std;
using namespace glm;

class BaseObject
{

private:
	string id;
	
protected:
	BaseObject(vec4 position);
	vec4 position;

public:
	float getX();
	float getY();
	float getZ();
	string getID();
	virtual void draw() = 0;
	virtual void init() = 0;
	virtual void cleanUp();
};