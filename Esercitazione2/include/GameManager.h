#include <unordered_map>
#include <list>
#include <vector>

#include "BaseObject.h"
#include "Bucket.h"
#include "SmoothTransition.h"
#include "Rectangle.h"
#include "Fireworks.h"

using namespace std;

#pragma once
class GameManager
{
public:
	GameManager(int winWidth, int winHeight);
	
	void displayUpdate();
	void worldUpdate();

	enum KEY
	{
		LEFT,
		RIGHT
	};

	void keyPressed(KEY key);

private:
	const float FAR_Z = 0.1;
	const float MID_Z = 0.5;
	const float NEAR_Z = 0.9;
	int winWidth;
	int winHeight;
	float stepSize = 40.0;
	int stepTime = 80;
	unordered_map<string, BaseObject*> objects;
	unordered_map<string, SmoothTransition*> movementHandler;
	vector<BaseObject*> objectWithBB;
	vector<BaseObject*> objectsToDelete;
	vector<int> indexToDelete;
	bool registerObject(BaseObject* obj);
	void deregisterObject(BaseObject* obj);
	void cleanObjects();
	void buildWorld();
	int score;
	int WATER_TO_SPAWN = 4;
	int deletedWater;
	int spawnedWater;
	void checkWinCondition();
	bool gameEnd;
	// in ms
	float SPAWN_EVERY_MS = 1000 * 4;
	float TIME_TO_REACH_FLOOR = 1000 * 3;
	float lastSpawn;
	void spawnWater();
	void spawnFireworks();
	// bucket
	Bucket* bucket;
	int bucketWidth = 40;
	int bucketMaxCapacity = 4;
	SmoothTransition* bucketHandler;
	Fireworks *fire;
	GameObjects::Rectangle* screenEnd;
};