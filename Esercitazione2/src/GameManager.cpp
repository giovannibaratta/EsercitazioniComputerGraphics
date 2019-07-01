#include "../include/GameManager.h"
#include "../include/Triangle.h"
#include "../include/Sphere.h"
#include "../include/Rectangle.h"
#include "../include/Sun.h"

#include <glm/glm.hpp>
#include <iostream>

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

	Triangle* test = new Triangle(vec4(300.0, 160.0, NEAR_Z, 1.0), 80);
	test->setColor(1.0, 0.0, 0.0);

	registerObject(sun);
	registerObject(sky);
	registerObject(grass);
	registerObject(bucket);
	registerObject(test);

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
}

bool GameManager::registerObject(BaseObject *obj) {
	if (objects.find(obj->getID()) != objects.end())
		// ID già registrato
		return false;
	objects[obj->getID()] = obj;
	obj->init();
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