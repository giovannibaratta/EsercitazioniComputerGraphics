#include "BaseObject.h"
#include <vector>
#pragma once
class GameLogic
{
public:
	GameLogic();
	virtual ~GameLogic();
	virtual std::vector<BaseObject*> objectToSpawn() = 0;
};

