#include "dxFontManager.h"

dxFontManager::dxFontManager(): pFont(NULL)
{
}

dxFontManager::~dxFontManager()
{
	if (pFont != NULL) {
		pFont->Release();
		pFont = NULL;
	}
}

void dxFontManager::getFontRectangle(LPCSTR text, RECT* rect)
{
	// Using DT_CALCRECT causes the rectangle to be determined but
	// not to be drawn
	pFont->DrawText(NULL,
	text,
	-1,
	rect,
	DT_CALCRECT | DT_LEFT,
	D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
}

bool dxFontManager::initFont(ID3D10Device* pD3DDevice)
{
	myRect.bottom = 300;
	myRect.left = 30;
	myRect.right = 300;
	myRect.top = 25;

	myRectW.bottom = 810;
	myRectW.left = 30;
	myRectW.right = 300;
	myRectW.top = 280;

	myRectA.bottom = 510;
	myRectA.left = 30;
	myRectA.right = 300;
	myRectA.top = 320;

	myRectS.bottom = 300;
	myRectS.left = 10;
	myRectS.right = 300;
	myRectS.top = 135;

	myRectD.bottom = 300;
	myRectD.left = 10;
	myRectD.right = 300;
	myRectD.top = 180;

	myRectE.bottom = 300;
	myRectE.left = 650;
	myRectE.right = 900;
	myRectE.top = 25;

	HRESULT hr = D3DX10CreateFont(pD3DDevice,
	15, // the font height
	0, // the font width
	0, // the weight of the font
	1, // number of mip levels
	FALSE, // this is not an italic font
	DEFAULT_CHARSET, // default character set
	OUT_DEFAULT_PRECIS, // default size mapping
	DEFAULT_QUALITY, // default quality mapping
	DEFAULT_PITCH | FF_DONTCARE, // default pitch
	"Terminal", // use Helvetica as the basis for this font
	&pFont); // the output

	if(FAILED(hr))
	{
		return false;
	}

	return true;
}
void dxFontManager::renderFont(ID3D10Device* pD3DDevice, LPCSTR mytext, RECT rectIn, float red, float blue, float green, float alpha)
{
	if (pD3DDevice != NULL) {
		// Create and Initialize the destination rectangle
		//SetRectEmpty(&rectIn);
		// Use the GetFontRectangle helper function to get the proper size of the rectangle.
		//getFontRectangle(TEXT("Space"), &rectIn);
		// Draw the text to the screen
		pFont->DrawText( NULL,
		TEXT( mytext),
		-1,
		&rectIn,
		DT_LEFT,
		D3DXCOLOR( red , blue, green, alpha ) );
	}
}