#include "BaseObject.h"
#include <list>
#include "Command.h"
#include "GameLogic.h"

using namespace std;

#pragma once
class GameManager
{

private:
	std::list<BaseObject*> objects;
	std::list<Command*> commandsQueue;
	GameLogic* gameLogic;

public:
	GameManager(GameLogic* gameLogic);
	~GameManager();

	void displayUpdate();
	void worldUpdate();
	void registerObject(BaseObject *obj);
	void enqueueCommand(Command *command);
};

