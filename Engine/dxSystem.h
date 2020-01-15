#ifndef DXSYSTEM
#define DXSYSTEM

#include <tchar.h>
#include <windows.h>
#include <D3dx9math.h>
#include "dxCollision.h"
#include "MySoundEventReciever.h"
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

//using namespace irrklang;

class dxSystem: public DEADBEEF_CORE/*public luaManager*/
{
private:
	HINSTANCE hInst; // global handle to hold the application instance
	dxCollision* myCollision;
	int m_iWidth;
	int m_iHeight;

	INT Target_Selected;

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

	float completionElapsed;
	float elapsed;
	int iRendered;
	bool renderMe;

	bool bResearch;
	bool bGather;

	bool paused;

	bool progressSound;
	bool healthSound;

	bool addResearch;
	bool menuIsPlaying;

	float contHealth;
	float contResearch;

	bool shipWorldRotate;
	bool menuinit;

	int planetHealth;
	int planetProgression;
	int progressStore;
	//int currentAge;
	char* currentAge[6];
	int ageIncrementer;
	ID3D10EffectScalarVariable* changeColour;
	int didChangeColour;

	float scenerotx;
	float sceneroty;
	float scenerotz;

	bool rotateWorld;
	bool testProgrees;
	bool firstTimeLoading;
	LPCSTR cont1tex[4];

public:
	dxSystem();
	~dxSystem();
	// start the sound engine with default parameters
//	ISoundEngine* engine;
	//ISound* m_sound;
	//ISound* audioProgress;
	//ISound* audioDeath;
	//ISound* continentAdvance;
	//MySoundEndReceiver* myReceiver;
	dxlightManager testLight;

	bool initialiseObjects();
	void setup();
	int run();

	bool render();
	bool MenuRender();
	bool pauseRender();
	bool controlsRender();
	bool creditsRender();
	bool completetionRender();
	bool failedRender();

	void MenuInput();
	void renderIntersectionData();
	void shutDown();
};

dxSystem::dxSystem():m_iWidth(800), m_iHeight(600)
{
	myReceiver = new MySoundEndReceiver();
	engine = createIrrKlangDevice();
	//enum planetAges {PRIMATIVE = 0, STONE = 1, BRONZE = 2, COLONIAL = 3, IRON = 4, CORPORATE = 5, DATA = 6, SPACEFARING = 7};
	planetHealth = 5;
	elapsed = 600.0f;
	completionElapsed = 0.0f;
	contHealth = 500;
	contResearch = 500;
	paused = FALSE;
	testProgrees = FALSE;
	firstTimeLoading = TRUE;
	shipWorldRotate = FALSE;
	menuIsPlaying = FALSE;
	menuinit = FALSE;
	progressSound = FALSE;
	healthSound = FALSE;

	currentAge[0] = "PRIMATIVE";
	currentAge[1] = "STONE";
	currentAge[2] = "MIDDLE AGE";
	currentAge[3] = "DATA";
	currentAge[4] = "SPACEFARING";
	currentAge[5] = "COMPLETION";

	//currentAge = PRIMATIVE;
}

dxSystem::~dxSystem()
{}

void dxSystem::renderIntersectionData()
{
	//changeColour = true;
}
bool dxSystem::initialiseObjects()
{  //Object init code goes here
	shaderLoader("MEGASHADER.fx", "RENDER_PL_BLINNPHONG");//For testing, will be made a proper shader loader in the future


	ageIncrementer = 0;
	createActors(5);
	createSceneryMesh(7);
	createSprites(11);
	createContinent(5);

	initialiseGraphics(800.0f, 600.0f);
	myCollision->initialiseCollision(pD3DDevice);
	initialiseMouse();

	orthographicCamera();

	changeColour =  pBasicEffect->GetVariableByName("setColour")->AsScalar();
	//initialiseFPSCamera(70.0f, 25.0f, 3.5f);

	//translateFPSCamera(testX, 0.0f, 0.0f);

	initialiseSprite(0, "./Textures/Widget.png", 0.0f, 0, 0, 500.0f, 100.0f);
	initialiseSprite(1, "./Textures/Widget.png", 0.0f, 0, 0, 500.0f, 100.0f);
	initialiseSprite(2, "./Textures/cursor.png", 0.0f, 0, 0, 500.0f, 100.0f);
	initialiseSprite(3, "./Textures/paused.png", 0.0f, 0, 0, 500.0f, 100.0f);
	initialiseSprite(4, "./Textures/completionScreen.png", 0.0f, 0, 0, 500.0f, 100.0f);
	initialiseSprite(5, "./Textures/DeadScreen.png", 0.0f, 0, 0, 500.0f, 100.0f);
	initialiseSprite(6, "./Textures/menuSplash.png", 0.0f, 0, 0, 500.0f, 100.0f);
	initialiseSprite(7, "./Textures/controls.png", 0.0f, 0, 0, 500.0f, 100.0f);
	initialiseSprite(8, "./Textures/credits.png", 0.0f, 0, 0, 500.0f, 100.0f);
	initialiseSprite(9, "./Textures/creditTitle.png", 0.0f, 0, 0, 500.0f, 100.0f);
	initialiseSprite(10, "./Textures/completionText.png", 0.0f, 0, 0, 500.0f, 100.0f);

	initialiseActorData(0, "./Models/World.obj", "./Textures/seaTex.png",  "", "");
	initialiseActorRotLoc(0,  0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
	initialiseActorData(1, "./Models/cont1.obj", "./Textures/contTex.png",  "", "");
	initialiseActorRotLoc(1,  0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
	initialiseActorData(2, "./Models/cont2.obj", "./Textures/contTex.png",  "", "");
	initialiseActorRotLoc(2,  0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
	initialiseActorData(3, "./Models/cont3.obj", "./Textures/contTex.png",  "", "");
	initialiseActorRotLoc(3,  0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
	initialiseActorData(4, "./Models/cont4.obj", "./Textures/contTex.png",  "", "");
	initialiseActorRotLoc(4,  0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
	//initialiseActorData(5, "./Models/PrimativeAge.obj", "./Textures/caveTex.png",  "", "");
	//initialiseActorRotLoc(5,  0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);

	initialiseSceneryData(0, "./Models/PrimativeAge.obj", "./Textures/caveTex.png",  "", "");
	initialiseSceneryRotLoc(0, scenerotx, sceneroty, scenerotz, 0.0f, 0.0f, 0.0f);
	initialiseSceneryData(1, "./Models/StoneAge.obj", "./Textures/templeTex.png",  "", "");
	initialiseSceneryRotLoc(1, scenerotx, sceneroty, scenerotz, 0.0f, 0.0f, 0.0f);
	initialiseSceneryData(2, "./Models/MiddleAge.obj", "./Textures/middleTex.png",  "", "");
	initialiseSceneryRotLoc(2, scenerotx, sceneroty, scenerotz, 0.0f, 0.0f, 0.0f);
	initialiseSceneryData(3, "./Models/boatMiddleAge.obj", "./Textures/middleTex.png",  "", "");
	initialiseSceneryRotLoc(3, scenerotx, sceneroty,scenerotz, 0.0f, 0.0f, 0.0f);
	initialiseSceneryData(4, "./Models/DataAge.obj", "./Textures/DataTex.png",  "", "");
	initialiseSceneryRotLoc(4, scenerotx, sceneroty, scenerotz, 0.0f, 0.0f, 0.0f);
	initialiseSceneryData(5, "./Models/flags.obj", "./Textures/flagTex.png",  "", "");
	initialiseSceneryRotLoc(5, scenerotx, sceneroty, scenerotz, 0.0f, 0.0f, 0.0f);
	initialiseSceneryData(6, "./Models/SpaceAge.obj", "./Textures/spaceTex.png",  "", "");
	initialiseSceneryRotLoc(6, scenerotx, sceneroty, scenerotz, 0.0f, 0.0f, 0.0f);

	initialiseContinentData(0, m_continentHealth[0], m_continentResearch[0]);
	initialiseContinentData(1, m_continentHealth[1], m_continentResearch[1]);
	initialiseContinentData(2, m_continentHealth[2], m_continentResearch[2]);
	initialiseContinentData(3, m_continentHealth[3], m_continentResearch[3]);

	createLights(1);
	//Create Directional light
 	setLightAmbient(0,  1.0f, 1.0f, 1.0f, 1.0f);
	setLightProperties(0, 0.2f, 0.8f, 0.3f, 15.0f);
    setDirectionalLightPosCol(0, 0.0f, 100.0f, -1.0f, 1.0f, 1.0f , 1.0f, 1.0f);

	loadAllSprites();
	loadAllSceneries();
	loadAllActors();

	x = 2;

	myState.StateSetUp(myState.iGameState);


	initFont();

	return true;
}

void dxSystem::MenuInput(){
	return;
}
bool dxSystem::pauseRender()
{
	beginScene();
	if(keys[O] ){
		//paused = TRUE;
		myState.iGameState = 1;
	}
		drawSprite(3, 0.0f, 800, 600, 400.0f, 300.0f);
		renderSpriteSpecific(3);

	endScene();
	return true;
}
bool dxSystem::MenuRender(){
	if(menuIsPlaying == FALSE){
		m_sound = engine->play2D("./Audio/mainMusic.wav", true, false, true);
		menuIsPlaying = TRUE;
	}
	//Start scene up
	beginScene();
	if(menuinit == FALSE)
	{
		scenerotx=0;
		sceneroty=0;
		scenerotz=0;
		planetHealth = 5;
		contHealth = 500;
		contResearch = 500;
		paused = FALSE;
		testProgrees = FALSE;
		firstTimeLoading = TRUE;
		shipWorldRotate = FALSE;
		rotateWorld = FALSE;
		planetProgression = 0;
		ageIncrementer = 0;
		
		for(int i =0; i < m_ContinentVec.size(); i++)
		{
			m_continentHealth[i] = 500;
			m_continentResearch[i] = 0;
			m_ContinentVec[i]->removeLife = FALSE;
			m_ContinentVec[i]->dead = FALSE;
		}
		menuinit = TRUE;
	}

	
	changeColour->SetInt(didChangeColour);
	enableLight(0);
	if(keys[SPACE]){
		myState.iGameState = 1;
	}
	if (keys[I])
	{
		myState.iGameState = 6;
	}
	if(keys[C])
	{
		myState.iGameState = 3;
	}
	setLightAmbient(0,  0.3f, 0.3f, 0.3f, 0.0f);
	setLightProperties(0, 0.2f, 0.8f, 0.3f, 15.0f);
	setDirectionalLightPosCol(0, 0.0f, 200.0f, -10.0f, 0.1f, 0.1f , 0.1f, 1.0f);
	translateOrbitCamera(320, 240, 280);
	renderOrbitCamera();
	scenerotx = -pitch / 20;
	sceneroty = -yaw / 20;
	scenerotz = -roll / 20;
	drawActor(4, delta,0.0f, -0.0f, 0.0f, 0.0f, 0.0f);
	renderActorSpecific(4);
	drawActor(3, delta,0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
	renderActorSpecific(3);
	drawActor(2, delta,0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
	renderActorSpecific(2);
	drawActor(1, delta,0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
	renderActorSpecific(1);
	drawActor(0, delta,0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
	renderActorSpecific(0);

	//To render the sprite with alpha, apparently we need an font being rendered somewhere. Oook...
	std::ostringstream outs2;
	outs2.precision(5);
	outs2
		<< "";
	lightStats = outs2.str();

	renderFont(lightStats.c_str(), myFont->myRectA, 0.0f, 0.0f, 0.0f, 1.0f);//Create a debug mode to display data like this

	renderSpriteSpecific(6);
	drawSprite(6, 0.0f, 800, 600, 400, 300.0f);

	endScene();
	return true;
}
bool dxSystem::controlsRender()
{
	beginScene();
	std::ostringstream outs2;
	outs2.precision(5);
	outs2
		<< "";
	lightStats = outs2.str();

	renderFont(lightStats.c_str(), myFont->myRectA, 0.0f, 0.0f, 0.0f, 1.0f);//Create a debug mode to display data like this
	drawSprite(7, 0.0f, 800.0f, 600.0f, 400.0f, 300.0f);
	renderSpriteSpecific(7);
	if(keys[B])
	{
		myState.iGameState = 0;
	}
	endScene();

	return true;
}

bool dxSystem::creditsRender()
{
	beginScene();
	std::ostringstream outs2;
	outs2.precision(5);
	outs2
		<< "";
	lightStats = outs2.str();
	elapsed -= delta * 0.3;
	if(elapsed <= 300.0f)
	{
		elapsed = 300.0f;
	}
	renderFont(lightStats.c_str(), myFont->myRectA, 0.0f, 0.0f, 0.0f, 1.0f);//Create a debug mode to display data like this
	drawSprite(8, 0.0f, 659.0f, 166.0f, 400.0f, elapsed);
	renderSpriteSpecific(8);
	drawSprite(9, 0.0f, 800.0f, 600.0f, 400.0f, 300.0f);
	renderSpriteSpecific(9);
	if(keys[B])
	{
		myState.iGameState = 0;
	}
	endScene();

	return true;
}

bool dxSystem::completetionRender()
{
	beginScene();
	beginScene();
	std::ostringstream outs2;
	outs2.precision(5);
	outs2
		<< "";
	lightStats = outs2.str();
	completionElapsed += delta * 0.1;
	if(completionElapsed >= 100.0f)
	{
		completionElapsed = 100.0f;
	}
	renderFont(lightStats.c_str(), myFont->myRectA, 0.0f, 0.0f, 0.0f, 1.0f);//Create a debug mode to display data like this
	drawSprite(4, 0.0f, 800.0f, 600.0f, 400.0f, 300.0f);
	renderSpriteSpecific(4);
	drawSprite(10, 0.0f, 682, 57, 400.0f, completionElapsed);
	renderSpriteSpecific(10);

	if(keys[B])
	{
		myState.iGameState = 0;
	}

	endScene();

	return true;
}

bool dxSystem::failedRender()
{
	beginScene();
	if(keys[B])
	{
		myState.iGameState = 0;
	}
	beginScene();
	std::ostringstream outs2;
	outs2.precision(5);
	outs2
		<< "";
	lightStats = outs2.str();

	renderFont(lightStats.c_str(), myFont->myRectA, 0.0f, 0.0f, 0.0f, 1.0f);//Create a debug mode to display data like this
	drawSprite(5, 0.0f, 800.0f, 600.0f, 400.0f, 300.0f);
	renderSpriteSpecific(5);
	endScene();

	return true;
}


bool dxSystem::render()
{ //Obect rendering code goes between beginScene() and endScene()
	beginScene();
	menuinit = FALSE;

	if(keys[P]){
		myState.iGameState = 2;
	//	paused = TRUE;
	}

	if(keys[CTRL]){
		rotateWorld = TRUE;
	}
	if(!keys[CTRL]){
		rotateWorld = FALSE;
	}
	if(ageIncrementer >= 5)
	{
		myState.iGameState = 4;
	}
	if(planetHealth <= 0)
	{
		myState.iGameState = 5;
	}

	//changeColour->SetInt(didChangeColour);
	setDirectionalLightPosCol(0, 0.0f, 100.0f, -1.0f, 1.0f, 1.0f , 1.0f, 1.0f);
	D3DXVECTOR3 temp = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	//translateOrbitCamera(320, 240, 280);
	scenerotx = -pitch / 20;
	sceneroty = -yaw / 20;
	scenerotz = -roll / 20;

	if(firstTimeLoading == TRUE){
		drawActor(4, -pitch / 20,-yaw / 20, -roll / 20, 0.0f, 0.0f, 0.0f);
		drawActor(3, -pitch / 20,-yaw / 20, -roll / 20, 0.0f, 0.0f, 0.0f);
		drawActor(2, -pitch / 20,-yaw / 20, -roll / 20, 0.0f, 0.0f, 0.0f);
		drawActor(1, -pitch / 20,-yaw / 20, -roll / 20, 0.0f, 0.0f, 0.0f);
		drawActor(0, -pitch / 20,-yaw / 20, -roll / 20, 0.0f, 0.0f, 0.0f);

		rotateOrbitCamera(pitch, yaw, roll);
		drawScenery(6, scenerotx ,sceneroty, scenerotz, 0.0f, 0.0f, 0.0f);
		//drawScenery(5, scenerotx ,sceneroty, scenerotz, 0.0f, 0.0f, 0.0f);
		drawScenery(4, scenerotx ,sceneroty, scenerotz, 0.0f, 0.0f, 0.0f);
		drawScenery(3, scenerotx ,sceneroty, scenerotz, 0.0f, 0.0f, 0.0f);
		drawScenery(2, scenerotx ,sceneroty, scenerotz, 0.0f, 0.0f, 0.0f);
		drawScenery(1, scenerotx ,sceneroty, scenerotz, 0.0f, 0.0f, 0.0f);
		drawScenery(0, scenerotx ,sceneroty, scenerotz, 0.0f, 0.0f, 0.0f);
		
		firstTimeLoading = FALSE;
	}

	/***************************************************************************************
	CAMERA ROTATIONS
	***************************************************************************************/
	
	//Set_Zbuffer_On();

	if(rotateWorld == TRUE){
		rotateOrbitCamera(pitch, yaw, roll);
		drawActor(4, -pitch / 20,-yaw / 20, -roll / 20, 0.0f, 0.0f, 0.0f);
		drawActor(3, -pitch / 20,-yaw / 20, -roll / 20, 0.0f, 0.0f, 0.0f);
		drawActor(2, -pitch / 20,-yaw / 20, -roll / 20, 0.0f, 0.0f, 0.0f);
		drawActor(1, -pitch / 20,-yaw / 20, -roll / 20, 0.0f, 0.0f, 0.0f);
		drawActor(0, -pitch / 20,-yaw / 20, -roll / 20, 0.0f, 0.0f, 0.0f);

		switch (ageIncrementer)
		{
		case  0:
			drawScenery(5, scenerotx ,sceneroty, scenerotz, 0.0f, 0.0f, 0.0f);
			drawScenery(0, scenerotx ,sceneroty, scenerotz, 0.0f, 0.0f, 0.0f);
			break;
		case 1:
			drawScenery(5, scenerotx ,sceneroty, scenerotz, 0.0f, 0.0f, 0.0f);
			drawScenery(1, scenerotx ,sceneroty, scenerotz, 0.0f, 0.0f, 0.0f);
			break;
		case 2:
			drawScenery(5, scenerotx ,sceneroty, scenerotz, 0.0f, 0.0f, 0.0f);
			drawScenery(2, scenerotx ,sceneroty, scenerotz, 0.0f, 0.0f, 0.0f);
			drawScenery(3, scenerotx ,sceneroty, scenerotz, 0.0f, 0.0f, 0.0f);
			break;
		case 3:
			drawScenery(5, scenerotx ,sceneroty, scenerotz, 0.0f, 0.0f, 0.0f);
			drawScenery(4, scenerotx ,sceneroty, scenerotz, 0.0f, 0.0f, 0.0f);
			break;
		case 4:
			drawScenery(6, scenerotx ,sceneroty, scenerotz, 0.0f, 0.0f, 0.0f);
		default:
			break;
		}
	}
	renderOrbitCamera();
	///////////////////////////////////////////////////////////////////////////////////////
	


	/***************************************************************************************
	RAY INTERSECTION TEST
	***************************************************************************************/
	  	if(leftMouseButton == TRUE)
	   	{
			
	   		for(int i=0;i<m_IactorVec.size();i++)
	   		{
	 			if(myCollision->Mouse_Pick_Mesh(m_IactorVec[i]->pMyModel, temp) == 1)
	   			{
					if(m_IactorVec[i]!=m_IactorVec[0]){
						Target_Selected = i;
						renderMe = TRUE;
						break;
					}
					
	  			} 
	 			leftMouseButton = FALSE;
	   		}
		}
	///////////////////////////////////////////////////////////////////////////////////////




	/***************************************************************************************
	RENDER WORLD MESHES
	***************************************************************************************/
		if(renderMe == TRUE){
				m_IactorVec[Target_Selected]->setActorPosition(0.0f, 30.0f, 10.0f);
				renderActorSpecific(4);
				renderActorSpecific(3);
				renderActorSpecific(2);
				renderActorSpecific(1);
				renderActorSpecific(0);

				renderMe = FALSE;
		}else {
			//for(int i = m_IactorVec.size(); i < m_IactorVec.size(); i--){
				m_IactorVec[4]->setActorPosition(0.0f, 0.0f, 0.0f);
				renderActorSpecific(4);
				m_IactorVec[3]->setActorPosition(0.0f, 0.0f, 0.0f);
				renderActorSpecific(3);
				m_IactorVec[2]->setActorPosition(0.0f, 0.0f, 0.0f);
				renderActorSpecific(2);
				m_IactorVec[1]->setActorPosition(0.0f, 0.0f, 0.0f);
				renderActorSpecific(1);
				m_IactorVec[0]->setActorPosition(0.0f, 0.0f, 0.0f);
				renderActorSpecific(0);
			//}
		}
	///////////////////////////////////////////////////////////////////////////////////////
		switch (ageIncrementer)
		{
		case  0:
			//renderspecificScenery(5);
			renderspecificScenery(0);
			break;
		case 1:
			//renderspecificScenery(5);
			renderspecificScenery(1);
			break;
		case 2:
			//renderspecificScenery(5);
			renderspecificScenery(3);
			renderspecificScenery(2);
			break;
		case 3:
			//renderspecificScenery(5);
			renderspecificScenery(4);
			break;
		case 4:
			renderspecificScenery(6);
		default:
			break;
		}
		//renderActorSpecific(5);
		
		//renderspecificScenery(3);

	/***************************************************************************************
	UPDATE CONTINENTS
	***************************************************************************************/
		if(planetProgression >= 4)
		{
			audioProgress = engine->play2D("./Audio/advance.wav", false, false, true);
			if(audioProgress) 
				audioProgress->setSoundStopEventReceiver(myReceiver);

			for(int i = 0; i < m_ContinentVec.size(); i++)
			{
				m_continentResearch[i] = 0;
				m_ContinentVec[i]->planetProgressed = FALSE;
			}
		
			planetProgression = 0;
			ageIncrementer++;
			firstTimeLoading = TRUE;
			contHealth += 120;
			contResearch += 120;
		}

		if(keys[A]){
			bResearch = TRUE;
		}
		if(!keys[A]){
			bResearch = FALSE;
		}

		if(keys[S]){
			bGather = TRUE;
		}
		if(!keys[S]){
			bGather = FALSE;
		}

	for(int i =0; i < m_ContinentVec.size(); i++)
	{
		m_continentHealth[i] -= 0.2;
		m_ContinentVec[i]->checkIfDead(m_ContinentVec[i]->dead);

		if(m_continentHealth[i] <= 0)
		{
			m_continentHealth[i] = 0;
			m_ContinentVec[i]->dead = TRUE;
			m_continentResearch[i] = 0;
			if(m_ContinentVec[i]->removeLife == FALSE)
			{
				audioDeath = engine->play2D("./Audio/Death.wav", false, false, true);
				if(audioDeath) 
					audioDeath->setSoundStopEventReceiver(myReceiver);

				m_ContinentVec[i]->removeLife = TRUE;
				planetHealth--;
			}
			
		} else {
			m_ContinentVec[i]->dead = FALSE;
		}

	
	}

	if(bGather==TRUE){
		m_continentHealth[Target_Selected] += 1.9;
		m_continentResearch[Target_Selected] -= 0.2;

		if(m_continentHealth[Target_Selected] >= contHealth)
		{
			m_continentHealth[Target_Selected] = contHealth;

			if (m_ContinentVec[Target_Selected]->removeLife == TRUE)
			{
				m_ContinentVec[Target_Selected]->removeLife = FALSE;
				planetHealth++;
			}

		}

		if(m_continentResearch[Target_Selected] <= 0)
		{
			m_continentResearch[Target_Selected] = 0;

			if (m_ContinentVec[Target_Selected]->planetProgressed == TRUE && planetProgression != 0)
			{
				m_ContinentVec[Target_Selected]->planetProgressed = FALSE;
				planetProgression--;
			}
		}
	} 

	if(bResearch==TRUE){
		m_continentResearch[Target_Selected] += 2.3;

		if(m_continentResearch[Target_Selected] >= contResearch)
		{
			m_continentResearch[Target_Selected] = contResearch;

			if(m_ContinentVec[Target_Selected]->planetProgressed == FALSE)
			{
				continentAdvance = engine->play2D("./Audio/upgrade.wav", false, false, true);
				if(continentAdvance) 
					continentAdvance->setSoundStopEventReceiver(myReceiver);

				m_ContinentVec[Target_Selected]->planetProgressed = TRUE;
				planetProgression++;
			}
			
		}

	}
	///////////////////////////////////////////////////////////////////////////////////////

	renderSpriteSpecific(1);
	renderSpriteSpecific(0);


	/***************************************************************************************
	RENDER TEXT
	***************************************************************************************/
	std::ostringstream outs;
	outs.precision(3);
	outs
		<< "\nCONTINENT STATS"
		<< "\n\nCONTINENT: " << Target_Selected << " SELECTED."
		<< "\n\nContinent1 status: "	<< m_ContinentVec[1]->wellded
		<< "\nContinent1 Health: "  << m_ContinentVec[1]->continentHealth << "/" << contHealth
		<< "\nContinent1 Research: " << m_ContinentVec[1]->continentResearch  << "/" << contResearch

		<< "\n\nContinent2 status: "	<< m_ContinentVec[2]->wellded
		<< "\nContinent2 Health: " << m_ContinentVec[2]->continentHealth << "/" << contHealth
		<< "\nContinent2 Research: " << m_ContinentVec[2]->continentResearch << "/" << contResearch

		<< "\n\nContinent3 status: "	<< m_ContinentVec[3]->wellded
		<< "\nContinent3 Health: " << m_ContinentVec[3]->continentHealth << "/" << contHealth
		<< "\nContinent3 Research: " << m_ContinentVec[3]->continentResearch << "/" << contResearch

		<< "\n\nContinent4 status: "	<< m_ContinentVec[4]->wellded
		<< "\nContinent4 Health: " << m_ContinentVec[4]->continentHealth << "/" << contHealth
		<< "\nContinent4 Research: " << m_ContinentVec[4]->continentResearch << "/" << contResearch;

	m_sVectorStats = outs.str();

	std::ostringstream outs2;
	outs2.precision(5);
	outs2
		<< "\PLANET STATS"
		<< "\n\nPlanet Health: " << planetHealth << "/5"
		<< "\nPlanet Progression: " << planetProgression << "/4"
		<< "\nPlanet era " << currentAge[ageIncrementer];
	lightStats = outs2.str();

	renderFont(lightStats.c_str(), myFont->myRectA, 0.0f, 0.0f, 0.0f, 1.0f);//Create a debug mode to display data like this
	renderFont(m_sVectorStats.c_str(), myFont->myRect, 0.0f, 0.0f, 0.0f, 1.0f);//Create a debug mode to display data like this
	///////////////////////////////////////////////////////////////////////////////////////


	/***************************************************************************************
	RENDER AND UPDATE
	***************************************************************************************/
	myCollision->UpdateCollision(Windows->dx, Windows->dy, 800, 600, projectionMatrix, viewMatrix, Windows->myOrbitCamera->position);
	drawSprite(2, 0.0f, 30.0f, 30.0f, Windows->dx, Windows->dy);
	drawSprite(1, 0.0f, 200.0f, 100.0f, 110.0f, 350.0f);
	drawSprite(0, 0.0f, 200.0f, 280.0f, 110.0f, 150.0f);
	
	renderSpriteSpecific(2);

	updateAllContinents();
	
	enableDebugMode();
	enableLight(0);
	//enableLight(1);
	///////////////////////////////////////////////////////////////////////////////////////


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

			//render();
			//Run while main game is running.
			if (myState.StateGameTest(myState.bTempRunning) != false){
				//render();
// 				//Check state -> Render.
 				switch(myState.iGameState){
 					case 0:
 						MenuRender();
 						break;
 					case 1:
 						render();
						break;
// 						///....Another render mode....
					case 2:
						pauseRender();
 						break;
					case 3:
						creditsRender();
						break;
					case 4:
						completetionRender();
						break;
					case 5:
						failedRender();
						break;
					case 6:
						controlsRender();
 					default:
						break;
 						//;//no idea why this statement does not like having no ";" in default label
 				}
			}
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