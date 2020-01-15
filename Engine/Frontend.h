#ifndef FRONTEND
#define FRONTEND

#include "dxSpriteManager.h"
#include "dxFontManager.h"
#include "dxD3D.h"

class frontEnd
{
private:
	dxFontManager*		thisFont;
	dxSpriteManager*	thisSprite;
	RECT			    thisRect;
	dxD3D*  dxInstance;

public:
	frontEnd();
	~frontEnd();

	//void initFont(int in_number);
	//void placeFont(int in_rectNum,  int in_bottom, int in_top, int in_left, int in_right);
	//void createFont(LPCSTR in_filename, int in_Fontnumber, int in_rectNumber, float in_r, float in_b, float in_g, float in_a );

	//bool CreateSprite(LPCSTR in_filename, int in_spriteNum);
	//void setSpriteScaleRotation(int in_spriteNum, float in_scaleX, float in_scaleY, float in_posX, float in_posY, float in_rot);
	//void renderSprites(int in_numSprites);

	void initDialogBox_A(int in_bottom, int in_top, int in_left, int in_right, float in_scaleX, float in_scaleY, float in_posX, float in_posY, float in_rot);
	void renderDialogBox_A(float in_red, float in_blue, float in_green, float in_alpha);
};

frontEnd::frontEnd()
{
	//for(int loop = 0; loop < 9; loop++){//Create maximum of 10 new font objects
	//	myFont[loop]  = new dxFontManager;
	//}

	thisSprite = new dxSpriteManager;
	thisFont = new dxFontManager;

	//for(int loop = 0; loop < 9; loop++){
	//	mySprite[loop]  = new dxSpriteManager;
	//}

	dxInstance = new dxD3D;

}
frontEnd::~frontEnd()
{

}


void frontEnd::initDialogBox_A(int bottom, int top, int left, int right,  float scaleX, float scaleY, float posX, float posY, float rot)
{
	thisSprite->pD3DDevice = dxInstance->pD3DDevice;
	thisFont->initFont();

	thisRect.bottom = bottom;
	thisRect.left = left;
	thisRect.right = right;
	thisRect.top = top;
	
	thisSprite->createSprite(dxInstance->pD3DDevice, dxInstance->ProjectionMatrix, "Textures/test.png");

	thisSprite->setSpriteScale(scaleX, scaleY);
	thisSprite->setSpritePosition(posX, posY);
	thisSprite->setSpriteRotation(rot);

}
void frontEnd::renderDialogBox_A(float red, float blue, float green, float alpha)
{
	thisFont->renderFont("Textures/test.png", thisRect, red, blue, green, alpha);
	thisSprite->renderSprite();
}

//bool frontEnd::CreateSprite(LPCSTR filename, int spriteNum)
//{
//	mySprite[spriteNum]->createSprite(dxD3D::pD3DDevice, dxD3D::projectionMatrix, filename);
//
//	return true;
//}
//void frontEnd::setSpriteScaleRotation(int spriteNum, float scaleX, float scaleY, float posX, float posY, float rot)
//{
//	mySprite[spriteNum]->setSpriteScale(scaleX, scaleY);
//	mySprite[spriteNum]->setSpritePosition(posX, posY);
//	mySprite[spriteNum]->setSpriteRotation(rot);
//
//}
//void frontEnd::renderSprites(int numSprites)
//{
//
//	mySprite[numSprites]->renderSprite();
//}
//
//void frontEnd::initFont(int number)
//{
//
//	for(int loop = 0; loop < number; loop++){
//		myFont[loop]->pD3DDevice = dxD3D::pD3DDevice;
//		myFont[loop]->initFont();
//	}
//
//}
//void frontEnd::placeFont(int rectNum, int bottom, int top, int left, int right)
//{
//	myRect[rectNum].bottom = bottom;
//	myRect[rectNum].left = left;
//	myRect[rectNum].right = right;
//	myRect[rectNum].top = top;
//}
//void frontEnd::createFont(LPCSTR filename, int Fontnumber, int rectNumber, float r, float b, float g, float a )
//{
//	myFont[Fontnumber]->renderFont(filename, myRect[rectNumber], r, b, g, a);
//}

#endif