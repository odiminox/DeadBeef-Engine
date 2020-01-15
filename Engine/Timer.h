#ifndef GAME_TIMER_H_BV
#define GAME_TIMER_H_BV

#include <Windows.h>
// For getting time <QueryPerformanceFrequency>

/*******************************************************************
* MyTimer is a instance of GAME_Timer created in winMain.cpp  < To include header "GAME_Timer.h" >
*
*******************************************************************/

class GAME_Timer
{
private:

public:
	LARGE_INTEGER timerFreq;
	float anim_rate;
	LARGE_INTEGER timeStart;
	LARGE_INTEGER timeEnd;

	// Variable to hold how long since last frame change
	float lastElapsedFrame;
	// How long should the frames last
	float frameDuration;

	void init(float &LFrame, float &FrameDur){
		LFrame = 0.0f; // Is -> lastElapsedFrame
		FrameDur += 0.0000000005; // Is -> frameDuration	//Change this number (example :  0.00000005  to get a faster rendering time) 0.001 = slow
	}
	float Counts(LARGE_INTEGER End, LARGE_INTEGER Start)
	{
		float anim_Measure;
		anim_Measure = ( (float)End.QuadPart  - (float)Start.QuadPart)  / timerFreq.QuadPart;
		return anim_Measure;
	}

	float LastFrame(float LFrame, float Rate)
	{
		LFrame += Rate;
		return LFrame;
	}
};

#endif