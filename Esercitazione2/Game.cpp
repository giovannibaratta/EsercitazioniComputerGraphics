#include "Game.h"
#include <iostream>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include "Triangle.h"
#include <sstream>

GameManager::GameManager(GameLogic* gameLogic) : gameLogic(gameLogic)
{
	std::vector<BaseObject*> objs = gameLogic->objectToSpawn();
	for (auto objPtr : objs)
		registerObject(objPtr);
}

GameManager::~GameManager()
{
	for (auto obj : objects)
		delete obj;
}

void GameManager::displayUpdate() {
	glPointSize(10);
	for (auto obj : objects)
		obj -> draw();
	glutSwapBuffers();
}

void GameManager::worldUpdate() {
	for (auto obj : objects)
		obj -> worldUpdate();
}

void GameManager::registerObject(BaseObject *obj) {
	objects.push_back(obj);
	obj->init();
}

void GameManager::enqueueCommand(Command * command)
{
	commandsQueue.push_back(command);
}
