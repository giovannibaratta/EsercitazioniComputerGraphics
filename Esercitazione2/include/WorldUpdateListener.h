#pragma once

class WorldUpdateListener {

public:
	virtual void worldUpdateEvent() = 0;
	WorldUpdateListener();
};
