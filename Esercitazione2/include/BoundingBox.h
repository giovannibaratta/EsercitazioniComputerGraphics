#pragma once

#include <glm/glm.hpp>

using namespace glm;

/**
	Contiene le funzioni necessarie per realizzare una bouding box di forma rettangolare.
*/
class BoundingBox
{
private:
	/** Vertice della bouding box. Il vertice opposto è
	boudingBox + (width, height, 0.0, 1.0) */
	vec4 boundingBox;
	float width, height;
	/** Se true permette di rilevare la collisione con altri oggetti. */
	bool collisionEnabled;

protected:
	/** aggiorna la posizione e la dimensione della bouding box */
	void updateBoundingBox(vec4 bb, float width, float height);

public:
	/** Restituisce true se la bouding box è in collisione con otherBb */
	bool inCollisionWith(BoundingBox otherBb);
	void enableCollision();
	void disableCollision();
	BoundingBox(vec4 boundingBox, float width, float height, bool enableCollision);
};
