#ifndef DXTEXTURELOADER_H_
#define DXTEXTURELOADER_H_

#include <d3d10.h>
#include <d3dx10.h>
#include <Windows.h>
#include <iostream>
#include <sstream>
#include <string>

#include <vector>

using namespace std;
/**************************************************************************************
* dxTextureLoader
* Simon GL Jordan

* Description:
*	Loads texture and texture resource into a vector array, loops through indexes
*	pushing textures and texture resource back onto vector.
*	Enables multiple loading of textures
*
* Use:
*	Call loadTexture() and pass in path and filename of texture in project director
*
***************************************************************************************/

class dxTextureLoader
{
private:
	//Private resources
	HWND*				hWnd;

public:
	//Public resources
	int textureIndex;
	LPCSTR filename;
	std::string texStats;

	std::vector<std::string> filenames;
	std::vector<ID3D10ShaderResourceView*> textureSRV;

	ID3D10EffectShaderResourceVariable* pTextureSR;
	ID3D10EffectShaderResourceVariable* pBumSR;
	ID3D10EffectShaderResourceVariable* pSpecSR;
	ID3D10EffectScalarVariable* specPowerPtr;

	dxTextureLoader();//Constructor/Destructor
	~dxTextureLoader();

	//Public methods
	bool loadTexture(LPCSTR filenameIn, ID3D10Device* pD3DDeviceIn);
	//fatal error handler
	bool fatalError(LPCSTR msg);
};

#endif