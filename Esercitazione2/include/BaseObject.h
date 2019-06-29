#pragma once
#include <string>

using namespace std;

class BaseObject
{

private:
	float x;
	float y;
	float z;
	string id;
	
protected:
	BaseObject(float x, float y, float z);

public:
	float getX();
	float getY();
	float getZ();
	string getID();
	virtual void draw();
	virtual void passiveMotion();
	virtual void worldUpdate();
	virtual void init();
};