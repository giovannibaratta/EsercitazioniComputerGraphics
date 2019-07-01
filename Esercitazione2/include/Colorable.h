#pragma once
class Colorable
{
	protected:
		float color[3];
	public:
		Colorable(float r, float g, float b);
		void setColor(float r, float g, float b);
};

