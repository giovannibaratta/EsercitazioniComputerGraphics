#pragma once

/**
	Classe che aggiunge il colore ad un oggetto.
*/
class Colorable
{
	protected:
		float color[3];
	public:
		Colorable(float r, float g, float b);
		void setColor(float r, float g, float b);
		float getRedColor();
		float getGreenColor();
		float getBlueColor();
};

