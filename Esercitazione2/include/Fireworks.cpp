#include <GL/glew.h>
#include <GL/freeglut.h>
#include <iostream>
#include <math.h>

#include "../include/Fireworks.h"
#include "../include/random/random.hpp"
#include "../include/utils.h"

using Random = effolkronium::random_static;
using namespace std;

Fireworks::Fireworks(vec4 startPosition, vec4 endPosition, float time, int particles, float length, RandomGenerator* randomGen) :
	endPosition(endPosition), stopDraw(false), particles(particles), Movable(startPosition),
	Colorable(1.0,0.0,0.0), randomGen(randomGen), length(length)
{
	// gestione movimento del proprio firework padre
	smoothTransition = new SmoothTransition(this);
	smoothTransition->setTargetPosition(endPosition, time);
	smoothTransition->onTransitionEndCallback(this);
}

void Fireworks::callback() {
	// quando il padre ha raggiunto la destinazione, genero gli altri.
	// ad ogni step riduco il numero di particles e anche la lunghezza.
	stopDraw = true;
	float newLength = std::max(20.0f, length / 2);
	int newParticlesNum = particles / 20;
	int colorIndex = Random::get<float>(0, NUM_COLORS);
	for (int i = 0; i < particles; i++) {
		Fireworks* fireworks = new Fireworks(endPosition, newEndPosition[i], 2000, newParticlesNum, newLength, randomGen);
		fireworks->init();
		fireworks->setColor(colors[colorIndex][0], colors[colorIndex][1], colors[colorIndex][2]);
		children.push_back(fireworks);
	}
}

void Fireworks::worldUpdateEvent()
{
	// se il raggio padre si sta ancora muovendo, continuo ad aggiornare la sua posizione,
	// altrimenti lo propago ai figli la richiesta di aggiornamento
	if (!stopDraw)
		smoothTransition->worldUpdateEvent();
	else
		for (auto fire : children)
			fire->worldUpdateEvent();
}

void Fireworks::draw() {
	// se il padre si sta ancora muovendo lo disegno, altrimenti propago la richiesta
	// ai figli
	if (stopDraw) {
		// draw childern
		for (auto fire : children)
			fire->draw();
		return;
	}

	float currentTime = static_cast<float>(clock()) / (CLOCKS_PER_SEC / 1000);
	
	glPushMatrix();
	glTranslatef(position.x, position.y, position.z);
	glBegin(GL_LINES);
	glColor3f(this->getRedColor(), this->getGreenColor(), this->getBlueColor());
	vec4 dir = glm::normalize(endPosition - position) * length;
	glVertex2f(0.0, 0.0);
	glVertex2f(dir.x, dir.y);
	glEnd();
	glPopMatrix();
}

void Fireworks::init()
{
	// calcolo l'offset delle posizioni dei figli
	for (int i = 0; i < particles; i++)
		newEndPosition.push_back(endPosition
			+ vec4(randomGen->generateIntValue(), randomGen->generateIntValue(), 0.0, 0.0));
}