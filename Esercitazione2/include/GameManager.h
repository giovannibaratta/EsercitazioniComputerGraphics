#include <unordered_map>
#include <list>

#include "BaseObject.h"
#include "Bucket.h"
#include "SmoothTransition.h"

using namespace std;

#pragma once
class GameManager
{
public:
	GameManager(int winWidth, int winHeight);
	~GameManager();

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
	const float NEAR_Z = 0.9;
	int winWidth;
	int winHeight;
	float stepSize = 50.0;
	int stepTime = 100;
	unordered_map<string, BaseObject*> objects;
	list<SmoothTransition*> movementHandler;
	bool registerObject(BaseObject* obj);
	void deregisterObject(BaseObject* obj);

	void buildWorld();

	// bucket
	Bucket* bucket;
	int bucketWidth = 40;
	int bucketMaxCapacity = 4;
	SmoothTransition* bucketHandler;
};

