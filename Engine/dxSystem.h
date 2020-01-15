#ifndef DXSYSTEM
#define DXSYSTEM

//#include <tchar.h>
//#include <D3dx9math.h>

#include <windows.h>
#include "DEADBEEF_CORE.h"

#include "cal3d\cal3d.h"


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

public:
	dxSystem();
	~dxSystem();

	float m_iWidth;
	float m_iHeight;

	bool initialiseObjects();
	void setup();
	int run();

	bool render();
	bool update();

	float x;
	float y;
	float z;

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

	createSprites(1);
	createActors(1);
	createLights(1);

	initialiseGraphics(800.0f, 600.0f);

	initialiseMouse();
	orthographicCamera();

	initialiseSprite(0, "./Textures/Widget.png", 0.0f, 0, 0, 500.0f, 100.0f);

	initialiseActorData(0, "./Models/Orc2.obj", "./Textures/full_body_1_tex.png",  "./Textures/full_body_1_norm.png", "./Textures/full_body_1_Specular.png");


	initialiseActorRotLoc(0,  0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);



	setLightAmbient(0,  1.0f, 1.0f, 1.0f, 1.0f);
	setLightProperties(0, 0.2f, 0.8f, 0.3f, 15.0f);
    setDirectionalLightPosCol(0, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f , 1.0f, 1.0f);

	loadAllSprites();

	loadAllActors();

	//enableLighting();

	myState.StateSetUp(myState.iGameState);

	return true;
}



bool dxSystem::render()
{ //Obect rendering code goes between beginScene() and endScene()
	beginScene();
	
	enableLight(0);

	/*setLightAmbient(0,  1.0f, 1.0f, 1.0f, 1.0f);
	setLightProperties(0, 0.2f, 0.8f, 0.3f, 15.0f);
    setDirectionalLightPosCol(0, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f , 1.0f, 1.0f);*/

	
	//enableLight(1);
	///////////////////////////////////////////////////////////////////////////////////////
	drawSprite(0, 0.0f, 200.0f, 280.0f, 110.0f, 150.0f);
	drawActor(0, 0.0f,0.0f, 0.0f, 0.0f, 0.0f, 0.0f);

	renderOrbitCamera();

	renderActorSpecific(0);
	renderSpriteSpecific(0);

	updateAllActors();
	updateAllLights();

	endScene();

	return true;
}

bool dxSystem::update()
{
	 float fps = (float)m_iFrameCnt / myTimer.lastElapsedFrame;
	 float mspf = 1000.0f / fps;

	yaw    = Windows->m_inputYaw * 3.0f;
	roll     = Windows->m_inputRoll * 3.0f;
	pitch  = Windows->m_inputPitch * 3.0f;

	translateOrbitCamera(x, y, z);
	rotateOrbitCamera(yaw, roll, pitch);

	if(keys[W])
		y += 1.0f;
	if(keys[S])
		y -= 1.0f;
	if(keys[A])
		x += 1.0f;
	if(keys[D])
		x -= 1.0f;

	delta = myTimer.lastElapsedFrame;

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

	 //return m_fDeltaTime;
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
			//Run while main game is running.
			if (myState.StateGameTest(myState.bTempRunning) != false){
				//render();
// 				//Check state -> Render.
 				switch(myState.iGameState){
 					case 0:
 						render();
 						break;
// 						///....Another render mode....
 					default:
						break;
 						//;//no idea why this statement does not like having no ";" in default label
 				}
			}
		}
		update();
		//updateScene();
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