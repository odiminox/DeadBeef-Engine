#ifndef DXSYSTEM
#define DXSYSTEM

#include <tchar.h>
#include <windows.h>
#include <D3dx9math.h>

#include "DEADBEEF_CORE.h"

/**************************************************************************************
* dxSystem.h
* Simon GL Jordan 498992

* Description:
* Main application entry point, all user programming with use of libraries and the engine is
* done here. When external libraries are compiled to .dlls, this can be created in a wizard
* for quick deadbeef engine development.
*
* Use:
* #include the needed deadbeef engine libraries and then initialize game elements within
* initialiseObjects() and render them in render() betweeen beginScene() and endScene()
***************************************************************************************/

class dxSystem: public DEADBEEF_CORE/*public luaManager*/
{
private:
	HINSTANCE hInst; // global handle to hold the application instance

	int m_iWidth;
	int m_iHeight;

	float testX;
	float testY;
	float testZ;
	float test1;
	float test2;
	float test3;

	float x;
	float y;
	float z;

	float fogStart;
	float fogEnd;

	float gunOffset;

	float value;

public:
	dxSystem();
	~dxSystem();

	dxlightManager testLight;

	bool initialiseObjects();
	void setup();
	int run();

	bool render();
	bool MenuRender();
	void MenuInput();

	void shutDown();
};

dxSystem::dxSystem():m_iWidth(800), m_iHeight(600)
{
}

dxSystem::~dxSystem()
{}

bool dxSystem::initialiseObjects()
{  //Object init code goes here
	shaderLoader("MEGASHADER.fx", "RENDER_PL_BLINNPHONG");//For testing, will be made a proper shader loader in the future

	createActors(2);
	createSprites(1);

	initialiseGraphics(800.0f, 600.0f);

	initialiseMouse();

	initialiseFPSCamera(70.0f, 25.0f, 3.5f);

	translateFPSCamera(testX, 0.0f, 0.0f);

	initialiseActorData(0, "./Models/BelnderEXport.obj", "./Textures/full_body_1_tex.png",  "", "");
	initialiseActorRotLoc(0,  0.0f, 0.0f, 0.0f, 0.0f, 0.0f, -60.0f);
	initialiseActorData(1, "./Models/blenderRoom.obj", "./Textures/level_textures/Main_room/main_room.png",  "", "");
	initialiseActorRotLoc(1,  0.0f, 0.0f, 0.0f, 0.0f, 0.0f, -60.0f);


	createLights(1);
	//Create Directional light
 	setLightAmbient(0,  1.0f, 1.0f, 1.0f, 1.0f);
	setLightProperties(0, 0.2f, 0.8f, 0.3f, 15.0f);
    setDirectionalLightPosCol(0, 0.0f, -1.0f, -1.0f, 1.0f, 1.0f , 1.0f, 1.0f);

	initialiseSprite(0, "./Textures/Directx 10.png", 0.0f, 50, 550, 100.0f, 100.0f);

	loadAllSprites();
	loadAllActors();

	myState.StateSetUp(myState.iGameState);

	initFont();

	return true;
}

void dxSystem::MenuInput(){
	return;
}

bool dxSystem::MenuRender(){
	//Start scene up
	beginScene();

	drawActor(0, 0.0f, 5.0f, 0.0f,  100.0f, 0.0f, -200.0f);


	rotateFPSCamera(pitch, yaw, roll);
	renderFPSCamera();

	//Apply game variables with temp variables
	myState.iGameState = windowsManager::m_iInputState;

	drawSprite(0, Windows->m_fRotTest, 200.0f, 200.0f, 0.0f, 0.0f);

	renderAllActors();

	enableDebugMode();

	enableLight(0);

	//end scene for rendering
	endScene();
	return true;
}
bool dxSystem::render()
{ //Obect rendering code goes between beginScene() and endScene()
	beginScene();

	drawSprite(0, 0.0f, 100.0f, 100.0f, 50.0f, 550.0f);

	drawActor(0, 0.0f, delta, 0.0f, 100.0f, 0.0f, 0.0f);

	rotateFPSCamera(pitch, yaw, roll);
	walkFPSCamera(8.0f, delta);
	strafeFPSCamera(8.0f);
	renderFPSCamera();

	renderAllActors();
	renderAllSprites();

	enableDebugMode();

	enableLight(0);
	//enableLight(1);

	endScene();

	return true;
}

void dxSystem::setup()
{
	initWindow(m_iWidth, m_iHeight);
	//initialiseGraphics(m_iWidth, m_iHeight);
	initialiseObjects();
}

int dxSystem::run()
{//Any scene updating functions will need to go here, like updateActors()
	// main message loop:
	MSG msg = {0};

	//time set up
	myTimer.lastElapsedFrame = 0.0f;
	myTimer.frameDuration = 0.0000000005;
	//Get Frequency;
	QueryPerformanceFrequency(&myTimer.timerFreq);
	//timer init
	myTimer.init(myTimer.lastElapsedFrame, myTimer.frameDuration);

	while (!done)
	{
		while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) == TRUE)
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		//Timer Start
		QueryPerformanceCounter(&myTimer.timeStart);
		//Frame lapsed
		myTimer.lastElapsedFrame = (myTimer.LastFrame(myTimer.lastElapsedFrame, myTimer.anim_rate));

		if (myTimer.lastElapsedFrame < myTimer.frameDuration)  // test if its time to call render function
		{
			//If the current frame count is below the current FPS then do nothing
		} else
		{

			if (keys[ESCAPE])				// Was ESC Pressed?
			{
				done=TRUE;						// ESC Signalled A Quit
			}

// 			if(keys[])
// 			{
// 
// 			}
// 			if(keys[])
// 			{
// 
// 			}
			render();
			//Run while main game is running.
			//if (myState.StateGameTest(myState.bTempRunning) != false){
			//	render();
// 				//Check state -> Render.
// 				switch(myState.iGameState){
// 					case 0:
// 						MenuRender();
// 						break;
// 					case 1:
// 						render();
// 						///....Another render mode....
// 						break;
// 					default:
// 						;//no idea why this statement does not like having no ";" in default label
// 				}
			//}
		}

		updateScene();
		// End Timer
		QueryPerformanceCounter(&myTimer.timeEnd);
	   // Current frame count
		myTimer.anim_rate = (myTimer.Counts(myTimer.timeEnd, myTimer.timeStart));
	}

	return (int) msg.wParam;
}

void dxSystem::shutDown()
{
	dxD3D::dxShutDown();
	delete Windows;
	delete myFont;
}
#endif