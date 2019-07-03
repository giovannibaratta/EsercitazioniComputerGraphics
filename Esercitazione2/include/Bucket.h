#pragma once
#include <GL/glew.h>
#include <GL/freeglut.h>

#include "Movable.h"
#include "Colorable.h"
#include "BoundingBox.h"

/**
	Contenitore quadrato in cui è possibile incrementare il contenuto.
	Sono presenti maxCapacity livelli.
*/
class Bucket : public Movable, public Colorable, public BoundingBox
{

private:
	/** Capacità massima del contenitore */
	int maxCapacity;
	/** capacità corrente del contenitore */
	int currentLevel;
	float contentHeight;
	/** Calcola i vertici da inserire nel VBO */
	void computeVertices(vec4 position, float width, float height);
	/** Aggiorna l'altezza del contenuto, utilizzata per il drawing */
	void updateContentHeight();

protected:
	float width;
	float height;
	/* ID del VBO del contenitore */
	GLuint outerVboID;
	/* vertici del contenitore (x,y,z) * 4 */
	float outerVertices[12];

public:
	Bucket(vec4 position, float width, float height, int maxCapacity);
	virtual void draw();
	virtual void init();
	virtual void move(vec4 position);
	virtual void cleanUp();
	/** Permette di aumentare il livello del contenuto */
	void increaseLevel();
	/** Permette di diminuire il livello del contenuto */
	void decreaseLevel();
};

