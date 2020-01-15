#ifndef WINDOWSMANAGER
#define WINDOWSMANAGER

#include <tchar.h>
#include <windows.h>
#include "dxInput.h"
#include "input.h"
#include "dxFPSCamera.h"
#include "dxOrbitCamera.h"
#include "resource.h"

/**************************************************************************************
* dxWindows.h
* Simon GL Jordan 498992

* Description:
* Main windows procedures and initialisation.
*
* Use:
* Instance within main main engine body.
***************************************************************************************/

static BOOL	active=TRUE;		// Window Active Flag Set To TRUE By Default
static BOOL	done=FALSE;								// Bool Variable To Exit Loop
static BOOL	fullscreen=TRUE;	// Fullscreen Flag Set To Fullscreen Mode By Default

class windowsManager : public Input
{
private:
	int mWidth;
	int mHeight;

public:
	windowsManager();
	~windowsManager();

	HINSTANCE hInst; // global handle to hold the application instance

	bool InitWindow(HINSTANCE hInstance, int width, int height);
	LRESULT CALLBACK MessageHandler(HWND, UINT, WPARAM, LPARAM);

	//Function imported from "input" class
	virtual void update(int p);


	// Set the yaw (Y axis), pitch (X axis), and roll (Z axis) rotations
	static float m_inputRoll;
	static float m_inputYaw;
	static float m_inputPitch;

	static float dx;
	static float dy;

	static bool m_bInputGame; // Test Bool for global game-state
	static int m_iInputState; // Test var for changing state to second menu ("game")
	static float m_fRotTest; // Test for rotating a sprite

	RECT rcClient;                 // client area rectangle
	float mOldMousePosX;
	float mOldMousePosY;

	float currentMouseX;
	float currentMouseY;

	float newMouseX;
	float newMouseY;

	//dxCameraManager *DBCameraManager;
	dxFPSCamera* myFPSCamera;
	dxOrbitCamera* myOrbitCamera;

protected:
};

windowsManager::windowsManager()
{
	//DBCameraManager = new dxCameraManager;
	myFPSCamera = new dxFPSCamera;
	myOrbitCamera = new dxOrbitCamera;
	m_inputRoll=0;
	m_inputYaw=0;
	m_inputPitch = 0;
}
windowsManager::~windowsManager()
{}


float windowsManager::m_inputRoll;
float windowsManager::m_inputYaw;
float windowsManager::m_inputPitch;

float windowsManager::dx;
float windowsManager::dy;


bool windowsManager::m_bInputGame;
int windowsManager::m_iInputState;
float windowsManager::m_fRotTest;

static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
static windowsManager* ApplicationHandle = 0;

//Global -test-
windowsManager myTestInput; //global instance of "windowManager" class

//virtual function from "input" class
	//Function: sets up varibles to be used in the program.
void windowsManager::update(int p){
	windowsManager::m_bInputGame = true;
	windowsManager::m_iInputState = 1;
	windowsManager::m_fRotTest = 0.0f;

	return;
}

LRESULT CALLBACK windowsManager::MessageHandler(HWND hwnd, UINT umsg, WPARAM wparam, LPARAM lparam){
	return DefWindowProc(hwnd, umsg, wparam, lparam);
}

bool firstMouseLoad = false;

static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam){
    POINT ptClientUL;              // client upper left corner
    POINT ptClientLR;              // client lower right corner

	myTestInput.dx  = (int)LOWORD(lParam);
	myTestInput.dy = (int)HIWORD(lParam);

	if(firstMouseLoad == false)
	{
		//These four values need to be seeded with a value that changes in accordance to the screen size.
		myTestInput.dx = 600;
		myTestInput.dy = 500;

		myTestInput.mOldMousePosX  = 300;
		myTestInput.mOldMousePosY = 400;

		firstMouseLoad = true;
	}



	// Check any available messages from the queue
  	switch (message)
	{

		//case WM_MOUSEMOVE:
		// Capture mouse input.
	

	case WM_ACTIVATE:							// Watch For Window Activate Message
		{
			if (!HIWORD(wParam))					// Check Minimization State
			{
				active=TRUE;						// Program Is Active
			}
			else
			{
				active=FALSE;						// Program Is No Longer Active
			}

			return 0;								// Return To The Message Loop
		}

		case WM_SYSCOMMAND:							// Intercept System Commands
			{
				switch (wParam)							// Check System Calls
				{
				case SC_SCREENSAVE:					// Screensaver Trying To Start?
				case SC_MONITORPOWER:				// Monitor Trying To Enter Powersave?
					return 0;							// Prevent From Happening
				}
				break;									// Exit
			}
		case WM_CLOSE:								// Did We Receive A Close Message?
			 {
			 	PostQuitMessage(0);						// Send A Quit Message
			 	return 0;								// Jump Back
			 }
		case WM_KEYDOWN:							// Is A Key Being Held Down?
			{
				keys[wParam] = TRUE;					// If So, Mark It As TRUE
				return 0;								// Jump Back
			}

		case WM_KEYUP:								// Has A Key Been Released?
			{
				keys[wParam] = FALSE;					// If So, Mark It As FALSE
				return 0;								// Jump Back
			}

		case WM_LBUTTONDOWN:
			{
				leftMouseButton = TRUE;
				return 0;
			}
			SetCapture(hWnd);

			GetClientRect(hWnd, &myTestInput.rcClient);
			ptClientUL.x = myTestInput.rcClient.left;
			ptClientUL.y = myTestInput.rcClient.top;
			ptClientLR.x = myTestInput.rcClient.right + 1;
			ptClientLR.y = myTestInput.rcClient.bottom + 1;
			ClientToScreen(hWnd, &ptClientUL);
			ClientToScreen(hWnd, &ptClientLR);

			SetRect(&myTestInput.rcClient, ptClientUL.x, ptClientUL.y, ptClientLR.x, ptClientLR.y);
			ClipCursor(&myTestInput.rcClient);

			//myTestInput.m_fRotTest = myTestInput.m_fRotTest + 0.2f;
			

		case WM_MOUSEMOVE:	 // mouse movement
			//leftMouseButton = FALSE;
			
			ShowCursor(false);
			float movex, movey, difx, dify;

			difx = (myTestInput.mOldMousePosX  - myTestInput.dx);
			dify = (myTestInput.mOldMousePosY - myTestInput.dy);
			movex = (difx / 5);
			movey = (dify / 5);

			myTestInput.dx += movex;
			//myTestInput.dy += movey;

			myTestInput.m_inputYaw = myTestInput.m_inputYaw = myTestInput.dx / 3;
			myTestInput.m_inputPitch = myTestInput.m_inputPitch -= movey  / 3;

			myTestInput.mOldMousePosX = myTestInput.dx;
			myTestInput.mOldMousePosY = myTestInput.dy;

	}
	return ApplicationHandle->MessageHandler(hWnd, message,wParam, lParam);
	//return DefWindowProc(hWnd, message, wParam, lParam);
}

bool windowsManager::InitWindow(HINSTANCE hInstance, int width, int height)
{
	ApplicationHandle = this;

	WNDCLASSEX wcex;
	// Fill in the WNDCLASSEX structure. This describes how the window
	// will look to the system
	wcex.cbSize = sizeof(WNDCLASSEX); // the size of the structure
	wcex.style = CS_HREDRAW | CS_VREDRAW; // the class style
	wcex.lpfnWndProc = WndProc; // the window procedure callback
	wcex.cbClsExtra = 0; // extra bytes to allocate for this class
	wcex.cbWndExtra = 0; // extra bytes to allocate for this instance
	wcex.hInstance = hInstance; // handle to the application instance
	wcex.hIcon = 0; // icon to associate with the application
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW); // the default cursor to use
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW+1); // the background color
	wcex.lpszMenuName = NULL; // the resource name for the menu
	wcex.lpszClassName = TEXT("DEADBEEF ENGINE DEVELOPMENT BUILD V3.1.6"); // the class name being created
	wcex.hIconSm = 0; // the handle to the small icon
	RegisterClassEx(&wcex);
	// Resize the window
	RECT rect = { 0, 0, width, height };
	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, FALSE);
	// create the window from the class above
	wndHandle = CreateWindow(TEXT("DEADBEEF ENGINE DEVELOPMENT BUILD V3.1.6"),
		TEXT("DEADBEEF ENGINE DEVELOPMENT BUILD V3.1.6"),
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		rect.right - rect.left,
		rect.bottom - rect.top,
		NULL,
		NULL,
		hInstance,
		NULL);
	if (!wndHandle)
	{
		MessageBox(NULL, "Could not initialize the window.", "Error", MB_OK);
		return false;
	}
	// Display the window on the screen
	ShowWindow(wndHandle, SW_SHOW);
	UpdateWindow(wndHandle);
	return true;
}

#endif