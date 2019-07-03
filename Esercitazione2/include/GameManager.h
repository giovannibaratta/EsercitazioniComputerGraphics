#include <unordered_map>
#include <list>
#include <vector>

#include "BaseObject.h"
#include "Bucket.h"
#include "SmoothTransition.h"
#include "Rectangle.h"
#include "Fireworks.h"

using namespace std;
#pragma once
/**
	Componente principale. Si occupa di istanziare gli oggetti che compongono la scena
	(sfondo superiore e inferiore, sole, contenitore, gocce che cadono e fuochi d'artificio
	finali in caso di vittoria). è possibile spostare il contenitore utilizzando le frecce
	direzionali di sinistra e destra. Gestice le collisioni all'interno tra gli oggetti.
	Si vince se ci raccolgono le 4 gocce prima che cadano a terra.
*/
class GameManager
{
public:
	/** winWidth = larghezza della finestra in px,
		winHeight = altezza della finestra in px */
	GameManager(int winWidth, int winHeight);
	/** Viene chiamataa quando è necessario disegnare gli oggetti.*/
	void displayUpdate();
	/** Viene chiamata quando è necessario calcolare un aggiornamento del mondo di gioco */
	void worldUpdate();

	enum KEY
	{
		LEFT,
		RIGHT
	};

	/** Viene chiamato quando si preme una delle due freccette */
	void keyPressed(KEY key);

private:
	/* oggetti sullo sfondo */
	const float FAR_Z = 0.1;
	const float MID_Z = 0.5;
	/* oggetti in primo piano */
	const float NEAR_Z = 0.9;
	int winWidth;
	int winHeight;

	/* oggetti gestiti dal gameManager, ad ogni ID corrisponde un puntatore ad un oggetto*/
	unordered_map<string, BaseObject*> objects;
	/* movimenti gestiti dal gameManager,
	ad ogni ID corrisponde un gestore di movimento */
	unordered_map<string, SmoothTransition*> movementHandler;
	/* oggetti che hanno una bounding box */
	vector<BaseObject*> objectWithBB;
	/* oggetti da eliminare (le gocce) a seguito di collisione o altro */
	vector<BaseObject*> objectsToDelete;
	/* indice degli oggetti da eliminare da objectWithBB */
	vector<int> indexToDelete;
	/* registra un oggetto presso il game manager */
	bool registerObject(BaseObject* obj);
	/* deregistra un oggetto */
	void deregisterObject(BaseObject* obj);
	/* elimina gli oggetti presennti in objectsToDelete */
	void cleanObjects();
	/* costruisce gli oggetti presenti nella scena iniziale */
	void buildWorld();
	/* punteggio raggiungeto (1 goccia 1 punto) */
	int score;
	/* gocce da generare */
	int WATER_TO_SPAWN = 4;
	/* numero di gocce eliminare (raccolte o cadute) */
	int deletedWater;
	/* numero di gocce generate */
	int spawnedWater;
	/* controlla se il game è finito */
	void checkWinCondition();
	/* true se il game è terminato */
	bool gameEnd;
	/* frequenza in ms di spawn delle gocce */
	float SPAWN_EVERY_MS = 1000 * 4;
	/* tempo necessario alle gocce per raggiunge il terreno */
	float TIME_TO_REACH_FLOOR = 1000 * 3;
	/* tempo dell'ultima goccia spawnata */
	float lastSpawn;
	/* genera una goccia in una poszione casuale */
	void spawnWater();
	/* genera il fuochi d'artificio */
	void spawnFireworks();
	/** Gestione contenitore */
	Bucket* bucket;
	int bucketWidth = 40;
	int bucketMaxCapacity = 4;
	/* gestisce il movimento del contenitore */
	SmoothTransition* bucketHandler;
	/* offset di movimento ad ogni pressione delle frecce */
	float stepSize = 40.0;
	/* tempo in ms per raggiungere la nuova posizione */
	int stepTime = 80;

	/* puntatore ai fuochi */
	Fireworks *fire;
	/* puntatore al rettangolo inferiore per rilevare la caduta delle gocce */
	GameObjects::Rectangle* screenEnd;
};