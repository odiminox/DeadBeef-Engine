#ifndef DXSHADERLOADER_H_
#define DXSHADERLOADER_H_

#include <d3d10.h>
#include <d3dx10.h>
#include <Windows.h>

#include "dxTextureLoader.h"

class dxShaderLoader
{
private:
public:

	void InitializeShader(ID3D10Device* device, ID3D10Effect* pBasicEffect, HWND hwnd, LPCSTR* filename);
	void RenderShader(ID3D10Device* device, int indexCount);
};

#endif