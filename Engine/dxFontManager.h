#ifndef DXTEXTMANAGER_H
#define DXTEXTMANAGER_H

#include <windows.h>
#include <d3d10.h>
#include <d3dx10.h>

class dxFontManager
{
private:
	ID3D10RenderTargetView*		pRenderTargetView;
	IDXGISwapChain*				pSwapChain;

public:
	dxFontManager();
	~dxFontManager();

	RECT myRect;

	RECT myRectW;
	RECT myRectA;
	RECT myRectS;
	RECT myRectD;
	RECT myRectE;

	bool initFont(ID3D10Device*	pD3DDevice);
	void getFontRectangle(LPCSTR text, RECT *rect);
	void renderFont(ID3D10Device* pD3DDevice, LPCSTR mytext, RECT rectIn, float red, float blue, float green, float alpha);

	ID3DX10Font*				pFont;

	ID3DX10Font* getFont(){ return pFont; }
};

#endif