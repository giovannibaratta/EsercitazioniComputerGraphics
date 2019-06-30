#include <glm/glm.hpp>
#include <time.h>

#include "Movable.h"

using namespace glm;

#pragma once
class SmoothTransition
{
	private:
		Movable* movable;
		vec4 target;
		// speed = [unit / ms]
		float speed;
		clock_t lastUpdate;

	public:
		SmoothTransition(Movable* movable);
		~SmoothTransition();

		void setTargetPosition(vec4 targetPosition, float time);
		void worldUptadeEvent();
};