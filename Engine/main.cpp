// Include the Windows header file, needed for all Windows applications

#include "dxSystem.h"
#include "dxWindows.h"

dxSystem dx;

// This is winmain, the main entry point for Windows applications
int APIENTRY _tWinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPTSTR lpCmdLine, int nCmdShow )
{
	dx.setup();
	dx.run();
	dx.shutDown();
}