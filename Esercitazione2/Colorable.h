#pragma once
class Colorable
{
	float color[3];
public:
	Colorable(float r, float g, float b);
	void setColor(float r, float g, float b);
	float getGreen();
	float getRed();
	float getBlue();
};

