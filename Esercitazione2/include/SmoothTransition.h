#include <glm/glm.hpp>
#include "Movable.h"

using namespace glm;

#pragma once
class SmoothTransition
{
	private:
		Movable* movable;
		vec4 target;
		float speed;

	public:
		SmoothTransition(Movable* movable);
		~SmoothTransition();

		void setTargetPosition(vec4 targetPosition, float time);
};