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
	
	GameObjects::Rectangle* sky = new GameObjects::Rectangle(vec4(vec3(0.0),1.0), winWidth, 200);
	sky->setColor(0.274, 0.905, 0.894);

	GameObjects::Rectangle* grass = new GameObjects::Rectangle(vec4(0.0, 200.0, 0.0,1.0), winWidth, winHeight-200);
	grass->setColor(0.082, 0.415, 0.188);

	Sun* sun = new Sun(vec2(50, 50), 20);
	sun->setMainColor(1.0, 1.0, 0.0);
	sun->setRayColor(0.949, 0.737, 0.388);

	bucket = new Bucket(vec4(100, 100, 0, 1.0),40, 40);
	bucket->setColor(1.0, 0.0, 0.0);

	registerObject(sky);
	registerObject(grass);
	registerObject(sun);
	registerObject(bucket);
}

GameManager::~GameManager()
{
}

void GameManager::displayUpdate() {
	for (auto keyValuePair : objects)
		keyValuePair.second->draw();
}

void GameManager::worldUpdate() {
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
	std::cout << "key pressed";
	/*
	if (key == LEFT)
		bucket->move(-10);
	else if (key == RIGHT)
		bucket->move(10);
	*/
}