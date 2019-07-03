#pragma once
#include<vector>

#include "Movable.h"
#include "SmoothTransition.h"
#include "WorldUpdateListener.h"
#include "Colorable.h"
#include "utils.h"


/**
	Simulazione di un sistema particellare che simula dei fuochi d'artificio. Viene
	disegnata una linea che una volta raggiunta la destinazione endPosition, genera
	altri Fireworks pari al valore particles. I nuovi fireworks hanno una endPosition
	casuale.
*/
class Fireworks : public Movable, public Colorable, public WorldUpdateListener,
public Callback{

private:
	/* Colori per i fuochi d'artificio*/
	static const int NUM_COLORS = 6;
	const float colors[NUM_COLORS][3] = {
		{1.0, 0.0, 0.0},
		{0.0, 1.0, 0.0},
		{0.0, 0.0, 1.0},
		{1.0, 1.0, 0.0},
		{1.0, 0.0, 1.0},
		{0.0, 1.0, 1.0},
	};

	/* Permette di gestire internamente il movimento del fuoco d'artificio */
	SmoothTransition* smoothTransition;
	/* Numero di particelle da generare*/
	int particles;
	/* Lunghezza del fuoco d'artificio */
	float length;
	/* Posizione target da raggiungere */
	vec4 endPosition;
	/* Se true non effettua più il rendering del fuoco padre ma effettua quello
		dei fuochi d'artifico generati */
	bool stopDraw;
	/* Contiene i fuochi d'artificio generati */
	vector<Fireworks*> children;
	/* Contiene la nuova posizione finale per i fuochi d'artificio generati */
	vector<vec4> newEndPosition;
	/* Generatore di numeri casuali */
	RandomGenerator *randomGen;
public:
	/* startPosition è la posizione iniziale dalla quale iniziare a fare il rendering
	del fuoco d'artificio principale, endPosition è la posizione target e corrisponde
	alla posizione di partenza dei fuochi d'artificio generati successivamente.
	Time tempo necessario per raggiungere endPosition, length lunghezza del
	fuoco d'artificio principale*/
	Fireworks(vec4 startPosition, vec4 endPosition, float time,
					int particles, float length, RandomGenerator* randomGen);

	/* Viene chiamata quando il fucoo d'artificio principale raggiunge la posizione
	endPosition */
	virtual void callback();
	/* Viene chiamata quando si verifica un update all'interno del gioco */
	virtual void worldUpdateEvent();
	virtual void init();
	virtual void draw();
};