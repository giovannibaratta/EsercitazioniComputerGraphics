#include <glm/glm.hpp>
#include <time.h>

#include "Movable.h"
#include "WorldUpdateListener.h"
#include "Callback.h"

using namespace glm;

#pragma once
class SmoothTransition : public WorldUpdateListener
{
	private:
		Movable* movable;
		vec4 target;
		// speed = [unit / ms]
		float speed;
		clock_t lastUpdate;
		bool callbackCalled;
		Callback* callback;

	public:
		SmoothTransition(Movable* movable);

		void setTargetPosition(vec4 targetPosition, float time);
		virtual void worldUpdateEvent();
		void onTransitionEndCallback(Callback* callback);
};