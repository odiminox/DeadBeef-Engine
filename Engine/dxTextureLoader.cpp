#include "dxTextureLoader.h"

dxTextureLoader::dxTextureLoader(): textureIndex(0)
{
}

dxTextureLoader::~dxTextureLoader()
{
	//free textures
//	for ( unsigned int i=0; i < textureSRV.size(); i++ )
//	{
//		textureSRV[i]->Release();
//	}
}

bool dxTextureLoader::loadTexture(LPCSTR filename, ID3D10Device* pD3DDevice)
{
	filenames.push_back(filename);//We define our own texture file, only one currently

		ostringstream textName;
		textName.precision(4);

		textName << "\n\nTexture file name: " << filename;

		texStats = textName.str();

	//load textures
	for ( int i=0; i < (int) filenames.size(); i++ )
	{
		textureSRV.push_back(NULL);

		if ( FAILED( D3DX10CreateShaderResourceViewFromFile( pD3DDevice, filenames[i].c_str(), NULL, NULL, &textureSRV[i], NULL ) ) )
		{
			  char err[255];
			  sprintf_s(err, "Could not load texture: %s!", filenames[i].c_str());
			  return fatalError( err );
		}
	}

	return true;
}

/*******************************************************************
* Fatal Error Handler
*******************************************************************/
bool dxTextureLoader::fatalError(LPCSTR msg)
{
	MessageBox(*hWnd, msg, "Fatal Error!", MB_ICONERROR);
	return false;
}