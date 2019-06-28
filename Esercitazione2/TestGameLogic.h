#pragma once
#include "GameLogic.h"

class TestGameLogic :
	public GameLogic
{

public:
	TestGameLogic();
	std::vector<BaseObject*> objectToSpawn();
};

