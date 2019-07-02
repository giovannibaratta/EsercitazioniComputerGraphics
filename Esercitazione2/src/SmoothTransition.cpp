#include <iostream>

#include "../include/SmoothTransition.h"
#include "../include/utils.h"


using namespace std;

SmoothTransition::SmoothTransition(Movable* movable)
	: movable(movable), target(movable->getPosition()),
		speed(0), lastUpdate(0)
{
}

// time in ms
void SmoothTransition::setTargetPosition(vec4 targetPosition, float time) {
	float distance = glm::distance(targetPosition, movable->getPosition());
	speed = distance / time;
	lastUpdate = clock();
	target = targetPosition;
}

void SmoothTransition::worldUptadeEvent() {
	vec4 objectPos = movable->getPosition();
	if (abs(length(objectPos-target)) > 0.5) {
		clock_t newUpdate = clock();
		float differenceLastUpdate = ((float)newUpdate - lastUpdate) / (CLOCKS_PER_SEC / 1000);
		vec4 direction = - normalize(objectPos - target) * speed * differenceLastUpdate;

		// se con lo step supero il target, imposto il target come posizione
		float sign = (-(objectPos + direction - target)).x * direction.x;
		if(sign >= 0)
			movable->move(objectPos + direction);
		else
			movable->move(target);
		lastUpdate = newUpdate;
	}
}

SmoothTransition::~SmoothTransition() {

}

