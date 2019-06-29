#include "../include/GameManager.h"
#include "../include/Triangle.h"
#include "../include/Sphere.h"
#include "../include/Rectangle.h"
#include "../include/Sun.h"
#include "../include/Bucket.h"

GameManager::GameManager(int winWidth, int winHeight)
	: winWidth(winWidth), winHeight(winHeight)
{
	buildWorld();
}

void GameManager::buildWorld() {
	MyRectangle* sky = new MyRectangle(0, 0, 0, winWidth, 200);
	sky->setColor(0.274, 0.905, 0.894);

	MyRectangle* grass = new MyRectangle(0, 200, 0, winWidth, winHeight-200);
	grass->setColor(0.082, 0.415, 0.188);

	Sun* sun = new Sun(50, 50, 20);
	sun->setMainColor(1.0, 1.0, 0.0);
	sun->setRayColor(0.949, 0.737, 0.388);

	Bucket* bucket = new Bucket(100, 100, 0, 40, 40);
	bucket->setColor(1.0, 0.0, 0.0);

	registerObject(sky);
	//registerObject(grass);
	//registerObject(sun);
	//registerObject(bucket);
}

GameManager::~GameManager()
{
}

void GameManager::displayUpdate() {
	for (auto keyValuePair : objects)
		keyValuePair.second->draw();
}

void GameManager::worldUpdate() {
	for (auto keyValuePair : objects)
		keyValuePair.second->worldUpdate();
}

bool GameManager::registerObject(BaseObject *obj) {
	if (objects.find(obj->getID()) != objects.end())
		// ID già registrato
		return false;
	objects[obj->getID()] = obj;
	return true;
}

void GameManager::deregisterObject(BaseObject* obj) {
	objects.erase(obj->getID());
}

void GameManager::enqueueCommand(Command * command)
{
	commandsQueue.push_back(command);
}