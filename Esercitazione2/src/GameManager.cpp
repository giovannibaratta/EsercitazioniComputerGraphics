#include <glm/glm.hpp>
#include <iostream>

#include "../include/GameManager.h"
#include "../include/Triangle.h"
#include "../include/Sphere.h"
#include "../include/Sun.h"
#include "../include/Water.h"
#include "../include/random/random.hpp"
#include "../include/Fireworks.h"

using namespace std;
using Random = effolkronium::random_static;

GameManager::GameManager(int winWidth, int winHeight)
	: winWidth(winWidth), winHeight(winHeight), score(0), lastSpawn(0),
	deletedWater(0), spawnedWater(0), gameEnd(false), fire(NULL)
{
	buildWorld();
}

void GameManager::buildWorld() {
	
	GameObjects::Rectangle* sky =
		new GameObjects::Rectangle(vec4(0.0, winHeight - 200,FAR_Z,1.0), winWidth, 200);
	sky->setColor(0.274, 0.905, 0.894);

	GameObjects::Rectangle* grass =
		new GameObjects::Rectangle(vec4(0.0, 0.0, FAR_Z,1.0), winWidth, winHeight-200);
	grass->setColor(0.082, 0.415, 0.188);

	Sun* sun = new Sun(vec4(100.0, winHeight-50, MID_Z, 1.0), 20);
	sun->setColor(1.0, 1.0, 0.0);
	sun->setRayColor(0.949, 0.737, 0.388);

	bucket = new Bucket(vec4(winWidth/2-bucketWidth/2, 50, MID_Z, 1.0), bucketWidth, 40, bucketMaxCapacity);
	bucket->setColor(1.0, 0.0, 0.0);
	bucket->enableCollision();

	screenEnd
		= new GameObjects::Rectangle(vec4(0.0, 0.0, FAR_Z, 1.0), winWidth, 1.0);
	screenEnd->enableCollision();
	screenEnd ->setColor(0.082, 0.415, 0.188);

	registerObject(sun);
	registerObject(sky);
	registerObject(grass);
	registerObject(bucket);
	registerObject(screenEnd);

	bucketHandler = new SmoothTransition(bucket);
	movementHandler[bucket->getID()] = bucketHandler;
}

void GameManager::spawnWater() {
	// genero le gocce in posizioni casuali
	if (spawnedWater >= WATER_TO_SPAWN)
		return;

	float currentTime = static_cast<float>(clock()) / (CLOCKS_PER_SEC / 1000);
	
	if (currentTime - lastSpawn < SPAWN_EVERY_MS)
		return;

	float randomXPos = Random::get(20, winWidth - 20);
	Water* drop = new Water(vec4(randomXPos, winHeight + 50, NEAR_Z, 1.0), 10);
	drop->setColor(0.0, 0.0, 1.0);
	drop->enableCollision();

	SmoothTransition* waterHandler = new SmoothTransition(drop);
	waterHandler->setTargetPosition(vec4(randomXPos, 0.0, NEAR_Z, 1.0), TIME_TO_REACH_FLOOR);

	registerObject(drop);
	movementHandler[drop->getID()] = waterHandler;

	spawnedWater += 1;
	lastSpawn = currentTime;
}

void GameManager::displayUpdate() {
	// chiedo agli oggetti di disegnarsi
	for (auto keyValuePair : objects)
		keyValuePair.second->draw();
}

/**
verifico le collissioni tra gli oggetti. se c'è una collisione tra goccia e contenitore,
aggiorno il livello del contenitore, aumento lo score e la elimino.
Se la goccia cade, la elimino.
*/
void GameManager::worldUpdate() {
	cleanObjects();
	spawnWater();

	/* propago l'aggiornamento del movimento agli handler */
	for (auto keyValuePair : movementHandler)
		keyValuePair.second->worldUpdateEvent();

	// controlla le collisioni
	for (int i = 0; i < objectWithBB.size() - 1; i++)
		for (int j = i + 1; j < objectWithBB.size(); j++) {

			BoundingBox* objI = dynamic_cast<BoundingBox*>(objectWithBB[i]);
			BoundingBox* objJ = dynamic_cast<BoundingBox*>(objectWithBB[j]);
			if (objI->inCollisionWith(*objJ)) {
				if (objectWithBB[i] == bucket) {
					// coliisione tra cestino e goccia
					objectsToDelete.push_back(objectWithBB[j]);
					indexToDelete.push_back(j);
					bucket->increaseLevel();
					score += 1;
				}
				else if (objectWithBB[j] == bucket) {
					objectsToDelete.push_back(objectWithBB[i]);
					indexToDelete.push_back(i);
					bucket->increaseLevel();
					score += 1;
				}
				else if (objectWithBB[i] == screenEnd) {
					objectsToDelete.push_back(objectWithBB[j]);
					indexToDelete.push_back(j);
				}else if (objectWithBB[j] == screenEnd) {
					objectsToDelete.push_back(objectWithBB[i]);
					indexToDelete.push_back(i);
				}
			}
		}
	checkWinCondition();
	if(fire != NULL)
		fire->worldUpdateEvent();
}

void GameManager::checkWinCondition() {
	if (gameEnd)
		return;
	if (deletedWater < WATER_TO_SPAWN)
		return;
	// controllo vittoria o sconfitta
	gameEnd = true;
	if (score == WATER_TO_SPAWN) {
		cout << "HAI VINTO" << endl;
		spawnFireworks();
	}
	else
		cout << "HAI PERSO" << endl;
}

void GameManager::spawnFireworks() {
	fire = new Fireworks(vec4(300.0, 0.0, NEAR_Z, 1.0),
		vec4(300.0, winHeight * 0.6, NEAR_Z, 1.0), 1000, 200, 30, new RandomGenerator(-100, 100));
	registerObject(fire);
}

bool GameManager::registerObject(BaseObject *obj) {
	if (objects.find(obj->getID()) != objects.end())
		// ID già registrato
		return false;
	objects[obj->getID()] = obj;
	obj->init();
	// se l'oggetto ha una bouding box lo aggiungo alla lista
	if (BoundingBox * bb = dynamic_cast<BoundingBox*>(obj))
		objectWithBB.push_back(obj);

	return true;
}

void GameManager::deregisterObject(BaseObject* obj) {
	objects.erase(obj->getID());
	obj->cleanUp();
}

void GameManager::cleanObjects()
{
	// elimino le gocce
	for (auto obj : objectsToDelete) {
		string id = obj->getID();
		obj->cleanUp();
		delete obj;
		objects.erase(id);
		movementHandler.erase(id);
		deletedWater += 1;
	}

	int count = 0;
	for (auto index : indexToDelete) {
		objectWithBB.erase(objectWithBB.begin() + index - count);
		count += 1;
	}
	objectsToDelete.clear();
	indexToDelete.clear();
}

/** gestione dell'input */
void GameManager::keyPressed(KEY key) {
	
	if (key == LEFT) {
		vec4 newPosition = bucket->getPosition() + vec4(-stepSize, 0.0, 0.0, 0.0);
		if (newPosition.x < 0)
			newPosition.x = 0;
		bucketHandler->setTargetPosition(newPosition, stepTime);
	}
	else if (key == RIGHT) {
		vec4 newPosition = bucket->getPosition() + vec4(+stepSize, 0.0, 0.0, 0.0);
		if (newPosition.x > winWidth - bucketWidth)
			newPosition.x = winWidth - bucketWidth;
		bucketHandler->setTargetPosition(newPosition, stepTime);
	}

}