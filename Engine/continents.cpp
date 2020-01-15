#include "Continents.h"


continents::continents(void):continentHealth(0), continentResearch(0), planetProgressed(FALSE), removeLife(FALSE), needAttention(FALSE)
{
}


continents::~continents(void)
{
}


void continents::updateContinentData(float health, float research)
{
	//checkIfDead(continentHealth);
	continentHealth = health;
	continentResearch = research;
	
}

float continents::getHealth()
{
	return continentHealth;
}

float continents::getResearch()
{
	return continentResearch;
}

void continents::checkIfDead(bool deded)
{
	if(deded == TRUE){
		wellded = "Dead";
	} else if (deded == FALSE){
		wellded = "Alive";
	}
}
