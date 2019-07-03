#include <glm/glm.hpp>
#include <time.h>

#include "Movable.h"
#include "WorldUpdateListener.h"
#include "Callback.h"

using namespace glm;

#pragma once
/**
	Permette di realizzare un movimento più dolce degli oggetti. Ad ogni smoothTransition
	viene assegnato un oggetto Movable da muovere.
*/
class SmoothTransition : public WorldUpdateListener
{
	private:
		/* oggetto da spostare */
		Movable* movable;
		/* posizione di destinazione */
		vec4 target;
		/* velocità di spostamento  [unit / ms] */
		float speed;
		/* clock dell'ultimo spostamento */
		clock_t lastUpdate;
		/* true se la callback registrata è già stata chiamata */
		bool callbackCalled;
		/* callback da chiamare quando si raggiunge la posizione target */
		Callback* callback;

	public:
		SmoothTransition(Movable* movable);
		/* imposta la destinazione e il tempo per raggiungerlo*/
		void setTargetPosition(vec4 targetPosition, float time);
		/* viene chiamata quando è necessario calcolare un aggiornamento del gioco */
		virtual void worldUpdateEvent();
		/* permette di associare una callback da chiamare quando si raggiunge il target */
		void onTransitionEndCallback(Callback* callback);
};