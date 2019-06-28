#pragma once
class BaseObject
{

private:
	float _x;
	float _y;
	float _z;
	
protected:
	BaseObject(float x, float y, float z);

public:
	float getX();
	float getY();
	float getZ();
	virtual void draw();
	virtual void passiveMotion();
	virtual void worldUpdate();
	virtual void init();
	virtual void windowResize(int width, int height);
};