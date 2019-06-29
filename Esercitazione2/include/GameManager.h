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
	int winWidth;
	int winHeight;
	unordered_map<string, BaseObject*> objects;
	list<SmoothTransition*> movementHandler;
	bool registerObject(BaseObject* obj);
	void deregisterObject(BaseObject* obj);

	void buildWorld();
	Bucket* bucket;
};

