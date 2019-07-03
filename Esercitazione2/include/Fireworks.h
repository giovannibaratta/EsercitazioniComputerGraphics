#pragma once
#include<vector>

#include "Movable.h"
#include "SmoothTransition.h"
#include "WorldUpdateListener.h"
#include "Colorable.h"
#include "utils.h"

class Fireworks : public Movable, public Colorable, public WorldUpdateListener,
public Callback{

private:
	static const int NUM_COLORS = 6;
	const float colors[NUM_COLORS][3] = {
		{1.0, 0.0, 0.0},
		{0.0, 1.0, 0.0},
		{0.0, 0.0, 1.0},
		{1.0, 1.0, 0.0},
		{1.0, 0.0, 1.0},
		{0.0, 1.0, 1.0},
	};

	SmoothTransition* smoothTransition;
	int particles;
	float lastUpdate;
	const int CHANGE_AFTER = 300;
	float length;
	vec4 endPosition;
	bool stopDraw;
	vector<Fireworks*> children;
	vector<vec4> newStartPosition;
	RandomGenerator *randomGen;
public:
	Fireworks(vec4 startPosition, vec4 endPosition, float time, int particles, float length, RandomGenerator* randomGen);
	virtual void callback();
	virtual void worldUpdateEvent();
	virtual void init();
	virtual void draw();
};