#include "../include/BaseObject.h"
#include "../include/Command.h"
#include <unordered_map>
#include <list>

using namespace std;

#pragma once
class GameManager
{

private:
	int winWidth;
	int winHeight;
	unordered_map<string, BaseObject*> objects;
	std::list<Command*> commandsQueue;
	bool registerObject(BaseObject* obj);
	void deregisterObject(BaseObject* obj);
	void buildWorld();

public:
	GameManager(int winWidth, int winHeight);
	~GameManager();

	void displayUpdate();
	void worldUpdate();
	void enqueueCommand(Command* command);
};

