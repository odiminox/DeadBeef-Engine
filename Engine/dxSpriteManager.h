#ifndef DXSPRITEMANAGER
#define DXSPRITEMANAGER

#include <windows.h>
#include <string>
#include <d3d10.h>
#include <d3dx10.h>

/**************************************************************************************
* dxSpriteManager
* Simon GL Jordan

* Description:
*	Loads in the sprite texture with loadTexture which is called by
*	createRtex which creates the shader resource for the texture
*	which is called by createSprite which generates the sprite
*	based on the information generated in the other functions
*
* Use:
*	Call createSprite to generate the sprite in the main Init code.
*	Inside dxManager render function -
*	setSpriteScale will set the scale of the sprite with your scale vector.
*	setSpritePosition will set the position of the sprite with your position vector.
*	renderSprite is called last to generate the sprite to the screen
***************************************************************************************/

class dxSpriteManager
{
private:
	D3DXVECTOR2					rScale;//Root scale and position of the sprite
	D3DXVECTOR2					rPosition;

	HWND*						hWnd;//window handle

	D3DXMATRIX                  projectionMatrix;	//projection and view matrices

	ID3D10ShaderResourceView*   SpriteTextureRV;//Shader resource var

    D3DX10_SPRITE				testSprite;// Create a new sprite variable
	ID3DX10Sprite*				spriteObject;

	D3DXMATRIX					matTranslation;//Translation sprite matrix
	D3DXMATRIX					matScaling;
	D3DXMATRIX					matRotation;

	ID3D10Texture2D*			pTexture2D;
	ID3D10Resource*				pD3D10Resource;
	int							ScreenHeight;

	float fScaleX;
	float fScaleY;

	float fPosX;
	float fPosY;

	float root_fRot;

public:
	dxSpriteManager(); //constructor and destructor
	~dxSpriteManager();

	bool loadTexture(ID3D10Device* pD3DDevice, LPCSTR);//Loads in the texture
	void createRtex(ID3D10Device* pD3DDevice, std::string filename);//Create the texture resource, contains loadTexture
	bool createSprite(ID3D10Device* pD3DDevice, D3DXMATRIX projectionMatrix, std::string filename);//Create Sprite, Contains CreateRtex

	void setSpriteScale(float fPosX, float fPosY);//Call to set the sprite location, call first
	void setSpritePosition(float fPosX, float fPosY);//Call to set the sprite position
	void setSpriteRotation(float fRot);//Call to set the sprite rotation

	void renderSprite();//Call to render the sprite

public:
};

#endif