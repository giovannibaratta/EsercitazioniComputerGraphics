#pragma once
#include <string>
#include <glm/glm.hpp>

using namespace std;
using namespace glm;

/**
	Oggetto base della gerarchia. Ogni oggetto dispone di una posizione (non modificabile)
	ed un ID generato automaticamente. Ogni oggetto che lo vuole estendere deve
	implementare le funzioni di inizializzazione e di disegno (draw). Nella draw dovranno
	essere eseguite tutte le chiamatate alle API di openGL.
*/
class BaseObject
{

private:
	/** ID univoco dell'oggetto */
	string id;
	
protected:
	BaseObject(vec4 position);
	vec4 position;

public:
	float getX();
	float getY();
	float getZ();
	vec4 getPosition();
	string getID();

	/** Funzione di disegno dell'oggetto */
	virtual void draw() = 0;
	virtual void init() = 0;
	/** Da utilizzare per eliminare eventuali risorse allocate durante l'esecuzione */
	virtual void cleanUp();
};