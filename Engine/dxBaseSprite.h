#include <d3d10.h>
#include <d3dx10.h>
#include <vector>

#include "dxD3D.h"

class dxBaseSprite: public dxD3D
{
private:
public:
	dxBaseSprite();
	~dxBaseSprite();

	int classId;

	D3DXVECTOR2					root_Scale;//Root scale and position of the sprite
	D3DXVECTOR2					root_Position;
	float											root_Rotation;

	ID3D10ShaderResourceView*   SpriteTextureRV;//Shader resource var

	ID3D10Resource*				pD3D10Resource;

	D3DX10_SPRITE				testSprite;// Create a new sprite variable
	ID3DX10Sprite*				spriteObject;

	D3DXMATRIX					matTranslation;//Translation sprite matrix
	D3DXMATRIX					matScaling;
	D3DXMATRIX					matRotation;

	ID3D10Texture2D*			pTexture2D;
	int							ScreenHeight;

	void loadSprite(LPCSTR textureLocation);
	void render();

	void scale(D3DXVECTOR2 in_Scale);//Call to set the sprite location, call first
	void translate(D3DXVECTOR2 in_Position);//Call to set the sprite position
	void rotate(float in_Rotation);//Call to set the sprite rotation
};

dxBaseSprite::dxBaseSprite():spriteObject(NULL),
							 SpriteTextureRV(NULL)
{
	ScreenHeight = 600;

	root_Scale.x	 = 0.0f;//Root scale and position vectors
	root_Scale.y	 = 0.0f;

	root_Position.x  = 0.0f;
	root_Position.y  = 0.0f;

	root_Rotation    = 0.0f;
}
dxBaseSprite::~dxBaseSprite(){}

void dxBaseSprite::loadSprite(LPCSTR textureLocation)
{
	D3DX10CreateTextureFromFile(pD3DDevice,  LPCSTR(textureLocation) , NULL, NULL, &pD3D10Resource, NULL);//Load in texture into a temporary ID3D10Resource

	pD3D10Resource->QueryInterface(__uuidof( ID3D10Texture2D ), (LPVOID*) &pTexture2D);//Translates ID3D10Resource into ID3D10Texture2D
	pD3D10Resource->Release();

	D3D10_TEXTURE2D_DESC desc;
	pTexture2D->GetDesc(&desc);

	D3D10_SHADER_RESOURCE_VIEW_DESC SRVDesc;
	ZeroMemory( &SRVDesc, sizeof(SRVDesc) );

	// Set the texture format
	SRVDesc.Format			    = desc.Format;
	SRVDesc.ViewDimension		= D3D10_SRV_DIMENSION_TEXTURE2D;
	SRVDesc.Texture2D.MipLevels = desc.MipLevels;//Set the mip levels of the texture

	pD3DDevice->CreateShaderResourceView(pTexture2D, &SRVDesc, &SpriteTextureRV);//Create the shader resource for the texture

	testSprite.pTexture      = SpriteTextureRV;	// Set the sprite’s shader resource view
	testSprite.TexCoord.x    = 0;// top-left location in U,V coords
	testSprite.TexCoord.y    = 0;
	testSprite.TexSize.x     = 1.0f;// Determine the texture size in U,V coords
	testSprite.TexSize.y     = 1.0f;
	testSprite.TextureIndex  = 0;// Set the texture index. Single textures will use 0
	testSprite.ColorModulate = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);// The color to apply to this sprite, full color applies white.

	D3DX10CreateSprite(pD3DDevice, 0, &spriteObject);//Create the sprite object
	spriteObject->SetProjectionTransform(&projectionMatrix);//Set the projection matrix for the sprite
}

void dxBaseSprite::render()
{
	D3DXMatrixIdentity(&matRotation);
	D3DXMatrixIdentity(&matScaling);
	D3DXMatrixIdentity(&matTranslation);

	D3DXMatrixRotationZ(&matRotation, root_Rotation);
	D3DXMatrixTranslation(&matTranslation, root_Position.x, (ScreenHeight - root_Position.y), 0.1f); //Set the translation matrix for center
	D3DXMatrixScaling(&matScaling, root_Scale.x, root_Scale.y, 1.0f ); //Create sprite scaling matrix
	testSprite.matWorld = (matRotation * (matScaling * matTranslation));

	spriteObject->Begin(D3DX10_SPRITE_SORT_TEXTURE);	 // Start the Draw process
	spriteObject->DrawSpritesImmediate(&testSprite, 1, 0, 0);// Draw the sprite
	spriteObject->End();
}

void dxBaseSprite::scale(D3DXVECTOR2 in_Scale)
{
	root_Scale.x = in_Scale.x;
	root_Scale.y = in_Scale.y;
}
void dxBaseSprite::translate(D3DXVECTOR2 in_Position)
{
	root_Position.x = in_Position.x;
	root_Position.y = in_Position.y;
}
void dxBaseSprite::rotate(float in_Rotation)
{
	root_Rotation = in_Rotation;
}