#include "glm/glm.hpp"
#include "BaseObject.h"

using namespace glm;

#pragma once
/**
	Classe che permette di spostare un BaseObject. Lo spostamento avviene tramite la
	funzione move.
*/
class Movable : public BaseObject
{
	public:
		Movable(vec4 position);
		/* Permette di spostare l'oggetto nella posizione position */
		virtual void move(vec4 position);
};
