#pragma once

#include <windows.h>
#include <string.h>
#include <iostream>
class continents
{
public:
	continents(void);
	~continents(void);

	float continentHealth;
	float continentResearch;
	bool dead;
	bool removeLife;
	bool planetProgressed;
	bool needAttention;
	std::string wellded;

	void updateContinentData(float, float);
	float getHealth();
	float getResearch();
	void checkIfDead(bool);
};
