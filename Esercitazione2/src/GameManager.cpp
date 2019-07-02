#include <glm/glm.hpp>
#include <iostream>

#include "../include/GameManager.h"
#include "../include/Triangle.h"
#include "../include/Sphere.h"
#include "../include/Sun.h"
#include "../include/Water.h"

using namespace std;

GameManager::GameManager(int winWidth, int winHeight)
	: winWidth(winWidth), winHeight(winHeight)
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

	Sun* sun = new Sun(vec4(100.0, winHeight-50, NEAR_Z, 1.0), 20);
	sun->setColor(1.0, 1.0, 0.0);
	sun->setRayColor(0.949, 0.737, 0.388);

	bucket = new Bucket(vec4(winWidth/2-bucketWidth/2, 50, NEAR_Z, 1.0), bucketWidth, 40, bucketMaxCapacity);
	bucket->setColor(1.0, 0.0, 0.0);
	bucket->enableCollision();

	Water* test = new Water(vec4(50.0,75.0, NEAR_Z, 1.0), 10);
	test->setColor(1.0, 0.0, 0.0);
	test->enableCollision();

	screenEnd
		= new GameObjects::Rectangle(vec4(0.0, 0.0, 0.0, 1.0), winWidth, 1.0);
	screenEnd->enableCollision();
	screenEnd ->setColor(0.082, 0.415, 0.188);

	registerObject(sun);
	registerObject(sky);
	registerObject(grass);
	registerObject(bucket);
	registerObject(test);
	registerObject(screenEnd);

	bucket->inCollisionWith(*test);
	cout << "BUCKET ID " << bucket->getID() << endl;
	cout << "WATER ID " << test->getID() << endl;
	bucketHandler = new SmoothTransition(bucket);
	movementHandler.push_back(bucketHandler);
}

GameManager::~GameManager()
{
}

void GameManager::displayUpdate() {
	for (auto keyValuePair : objects)
		keyValuePair.second->draw();
}

void GameManager::worldUpdate() {
	for (auto transition : movementHandler)
		transition->worldUptadeEvent();
	// fai cadere le gocce

	vector<BaseObject*> objectsToDelete;
	vector<int> indexToDelete;

	// controlla le collisioni
	for (int i = 0; i < objectWithBB.size() - 1; i++)
		for (int j = i + 1; j < objectWithBB.size(); j++) {

			BoundingBox* objI = dynamic_cast<BoundingBox*>(objectWithBB[i]);
			BoundingBox* objJ = dynamic_cast<BoundingBox*>(objectWithBB[j]);
			if (objI->inCollisionWith(*objJ)) {
				cout << objectWithBB[i]->getID() <<  "Collision" << objectWithBB[j]->getID() << endl;
				if (objectWithBB[i] == bucket) {
					// coliisione tra cestino e goccia
					objectsToDelete.push_back(objectWithBB[j]);
					indexToDelete.push_back(j);
					bucket->increaseLevel();
				}
					
				if (objectWithBB[i] == screenEnd) {
					objectsToDelete.push_back(objectWithBB[j]);
					indexToDelete.push_back(j);
				}
			}
		}

	// elimino le gocce
	for (auto obj : objectsToDelete) {
		string id = obj->getID();
		obj->cleanUp();
		delete obj;
		objects.erase(id);
		cout << "ID" << id;
	}

	int count = 0;
	for (auto index : indexToDelete) {
		objectWithBB.erase(objectWithBB.begin() + index-count);
		count += 1;
	}

	/*
	for (int i = 0; i < indexToDelete.size(); i++) {
		int index = indexToDelete[i];
		
		BaseObject* obj = objects[objectWithBBID[index - 1]];
		objects.erase(objectWithBBID[index - 1]);
		obj->cleanUp();
		delete obj;
		objectWithBB.erase(objectWithBB.begin()+(index-i));
		objectWithBBID.erase(objectWithBBID.begin() + (index - i));
	}	*/
}

bool GameManager::registerObject(BaseObject *obj) {
	if (objects.find(obj->getID()) != objects.end())
		// ID già registrato
		return false;
	objects[obj->getID()] = obj;
	obj->init();
	if (BoundingBox * bb = dynamic_cast<BoundingBox*>(obj))
		objectWithBB.push_back(obj);

	return true;
}

void GameManager::deregisterObject(BaseObject* obj) {
	objects.erase(obj->getID());
	obj->cleanUp();
}

void GameManager::keyPressed(KEY key) {
	std::cout << "Key pressed " << key << "\n";
	
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