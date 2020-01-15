#include "dxSpriteManager.h"
/*******************************************************************
* Constructor
*******************************************************************/
dxSpriteManager::dxSpriteManager() :    spriteObject(NULL),
										SpriteTextureRV(NULL)
{
	ScreenHeight = 600;

	rScale.x	 = 0.0f;//Root scale and position vectors
	rScale.y	 = 0.0f;

	rPosition.x  = 0.0f;
	rPosition.y  = 0.0f;
}

/*******************************************************************
* Destructor
*******************************************************************/
dxSpriteManager::~dxSpriteManager()
{
	//if(SpriteTextureRV) SpriteTextureRV->Release();
	//if(spriteObject) spriteObject->Release();
}
/*******************************************************************
* Load the texture
* Needs to be made external so just textures can be loaded in
* for multiple textures
*******************************************************************/
bool dxSpriteManager::loadTexture(ID3D10Device* pD3DDevice, LPCSTR filename)
{
//		///Load texture
//	//-----------------------------------------------------------------
//	// Loads the texture into a temporary ID3D10Resource object

	D3DX10CreateTextureFromFile(pD3DDevice,  LPCSTR(filename) , NULL, NULL, &pD3D10Resource, NULL);//Load in texture into a temporary ID3D10Resource

	pD3D10Resource->QueryInterface(__uuidof( ID3D10Texture2D ), (LPVOID*) &pTexture2D);//Translates ID3D10Resource into ID3D10Texture2D
	pD3D10Resource->Release();

	return true;
}
/*******************************************************************
* Create shader resource for the texture
*******************************************************************/
void dxSpriteManager::createRtex(ID3D10Device* pD3DDevice, std::string filename)
{
	loadTexture(pD3DDevice, filename.c_str());
	//myTexture->LoadTexture(pD3DDevice, filename.c_str());

	D3D10_TEXTURE2D_DESC desc;
	pTexture2D->GetDesc(&desc);

	D3D10_SHADER_RESOURCE_VIEW_DESC SRVDesc;
	ZeroMemory( &SRVDesc, sizeof(SRVDesc) );

	// Set the texture format
	SRVDesc.Format			    = desc.Format;
	SRVDesc.ViewDimension		= D3D10_SRV_DIMENSION_TEXTURE2D;
	SRVDesc.Texture2D.MipLevels = desc.MipLevels;//Set the mip levels of the texture

	pD3DDevice->CreateShaderResourceView(pTexture2D, &SRVDesc, &SpriteTextureRV);//Create the shader resource for the texture
}

/*******************************************************************
* Create the sprite
*******************************************************************/
bool dxSpriteManager::createSprite(ID3D10Device* pD3DDevice, D3DXMATRIX projectionMatrix, std::string filename)
{
	createRtex(pD3DDevice, filename);

	testSprite.pTexture      = SpriteTextureRV;	// Set the sprite’s shader resource view
	testSprite.TexCoord.x    = 0;// top-left location in U,V coords
	testSprite.TexCoord.y    = 0;
	testSprite.TexSize.x     = 1.0f;// Determine the texture size in U,V coords
	testSprite.TexSize.y     = 1.0f;
	testSprite.TextureIndex  = 0;// Set the texture index. Single textures will use 0
	testSprite.ColorModulate = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);// The color to apply to this sprite, full color applies white.

	D3DX10CreateSprite(pD3DDevice, 0, &spriteObject);//Create the sprite object
	spriteObject->SetProjectionTransform(&projectionMatrix);//Set the projection matrix for the sprite

	D3DXMatrixTranslation(&matTranslation, rPosition.x, (ScreenHeight - rPosition.y), 0.1f);   //Set the translation matrix for center
	D3DXMatrixScaling(&matScaling, rScale.x, rScale.y, 1.0f);								   //Set the new Scale Matrix
	D3DXMatrixRotationZ(&matRotation, root_fRot);
	testSprite.matWorld = (matRotation * (matScaling * matTranslation));									   //

	return true;
}
/*******************************************************************
* Render sprite
*******************************************************************/
void dxSpriteManager::renderSprite()
{
	spriteObject->Begin(D3DX10_SPRITE_SORT_TEXTURE);	 // Start the Draw process
	spriteObject->DrawSpritesImmediate(&testSprite, 1, 0, 0);// Draw the sprite
	spriteObject->End();								 // Send the sprite to the hardware
}

/*******************************************************************
* Set the sprites scale, overload of D3DXMatrixScaling
* VECTOR2 x and y is converted from float for easier function control
*******************************************************************/
void dxSpriteManager::setSpriteScale(float fScaleX, float fScaleY)
{
	rScale.x = fScaleX;
	rScale.y = fScaleY;
	D3DXMatrixScaling(&matScaling, rScale.x, rScale.y, 1.0f ); //Create sprite scaling matrix
}
/*******************************************************************
* Set the sprites position, overload of D3DXMatrixScaling D3DXMatrixTranslation
* VECTOR2 x and y is converted from float for easier function control
*******************************************************************/
void dxSpriteManager::setSpritePosition(float fPosX, float fPosY)
{
	rPosition.x = fPosX;
	rPosition.y = fPosY;
	D3DXMatrixTranslation(&matTranslation, rPosition.x, (ScreenHeight - rPosition.y), 0.1f); //Set the translation matrix for center
	testSprite.matWorld = (matScaling * matTranslation);
}

void dxSpriteManager::setSpriteRotation(float fRot)
{
	root_fRot = fRot;
	D3DXMatrixRotationZ(&matRotation, root_fRot);
	testSprite.matWorld = (matRotation * (matScaling * matTranslation));
}