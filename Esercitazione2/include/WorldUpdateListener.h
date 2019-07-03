#pragma once

/**
	Listener per gli aggiornamenti del gioco. Quando è necessario calolare un aggiornamento
	viene richiamata la funzione worldUpdateEvent.
*/
class WorldUpdateListener {

public:
	virtual void worldUpdateEvent() = 0;
	WorldUpdateListener();
};
