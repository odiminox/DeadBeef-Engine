#ifndef DBENGINE
#define DBENGINE

#include "dxD3D.h"
#include "dxWindows.h"
#include "dxFontManager.h"
#include "Timer.h"
#include "gameStateMan.h"

#include <iostream>
#include <sstream>
#include <string.h>
#include <vector>

/**************************************************************************************
* DEADBEEF_Engine.h3
* Simon GL Jordan 498992

* Description:
* Workhorse for the application. Takes in data from external libraries such as dxWindows,
* dxD3D and dxSpriteManager, then wraps untidy code into clean functions. All data is
* forced into dxSystem into a safe linear way from this class, no issues with ID3D10DEVICE
* or iUnknowns. This class enables easy access to engine features without the programmer
* needing to worry about directx or core libraries.
*
* NOTE:
* This is only the experimental build of the engine. When more features have been implemented
* it will be divided up into several main sections such as DBXgraphics, DBXsound etc.
*
* Use:
*
* Future development:
* Child and parent classes can be added into this class to extend the workload of other engine
* libraries. They can be separated into groups IE: (graphics, sound, physics). Will keep
* classes smaller and enable easier use in dxSystem
***************************************************************************************/

class DEADBEEF: public dxD3D
{
private:

public:
	DEADBEEF();
	~DEADBEEF();

	//Heap objects
	windowsManager*	Windows;
	dxFontManager*      myFont;
	//Stack objects
	GameState				myState;
	GAME_Timer			myTimer;

	void initWindow(int in_width, int in_height);
	void initialiseGraphics(int width, int height);

	//Scene functions
	void beginScene();
	void endScene();
	float updateScene();

	void shaderLoader(LPCSTR shaderFileName, LPCSTR technqueName);
	void fixedFunctionPipeline();

	//Fonts functions
	void initFont();
	void renderFont(LPCSTR mytext, RECT rectIn, float red, float blue, float green, float alpha);

	std::string m_sFrameStats;

	float m_fDeltaTime;
	int m_iFrameCnt;

	float ADInput;
	float WSInput;
	float zInput;
	float EKey;
	float QKey;

	float yaw;
	float roll;
	float pitch;

	float delta;

	bool customShader;
};

DEADBEEF::DEADBEEF():m_fDeltaTime(0), m_iFrameCnt(0)
{
	Windows	  = new windowsManager;
	myFont		  = new dxFontManager;
	m_sFrameStats = "";
	yaw =0;
	roll =0;
	pitch=0;
}
DEADBEEF::~DEADBEEF()
{
}

void DEADBEEF::initialiseGraphics(int width, int height)
{
	dxInitialiseGraphics(width, height);
}
void DEADBEEF::initWindow(int width, int height)
{
	Windows->InitWindow(Windows->hInst, width, height);
}

void DEADBEEF::beginScene()
{
	dxBeginScene();
	//Temp storage for these values, create a function to update each frame call.
	// Set the yaw (Y axis), pitch (X axis), and roll (Z axis) rotations
	yaw    = Windows->m_inputYaw;
	roll     = Windows->m_inputRoll;
	pitch  = Windows->m_inputPitch;

	delta = myTimer.lastElapsedFrame;
}
void DEADBEEF::endScene()
{
	dxEndScene();
}

void DEADBEEF::shaderLoader(LPCSTR shaderFileName, LPCSTR techniqueName)
{
	customShader = true;

	rootCustomShader = customShader;

	rootShaderFileName = shaderFileName;
	rootTechniqueName  = techniqueName;
}

 void DEADBEEF::initFont()
 {
	 myFont->initFont(pD3DDevice);
 }

 void DEADBEEF::renderFont(LPCSTR mytext, RECT rectIn, float red, float blue, float green, float alpha)
 {
	 myFont->renderFont(pD3DDevice, mytext, rectIn, red, blue, green, alpha);
 }

 float DEADBEEF::updateScene()
 {
	 float fps = (float)m_iFrameCnt / myTimer.lastElapsedFrame;
	 float mspf = 1000.0f / fps;

	 std::ostringstream outs;
	 outs.precision(5);
	 outs
		 << "\n\n\n\n\n\nFRAME STATS"
		 << "\nanim rate: " << myTimer.anim_rate
		 << "\nTime: " << myTimer.lastElapsedFrame
		 << "\nframe Count: " << m_iFrameCnt
		 << "\nmiliseconds per frame: " << mspf
		 << "\nFPS: " << fps;
	 m_sFrameStats = outs.str();

	 m_iFrameCnt++;

	 m_fDeltaTime = 100.0f / fps;

	 return m_fDeltaTime;
 }

#endif