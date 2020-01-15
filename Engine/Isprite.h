#include <vector>
#include <string>
#include <iostream>
#include <Windows.h>
#include <vector>
#include <d3d10.h>
#include <d3dx10.h>

#include "IupdateSprite.h"

class Isprite:public IupdateSprite
{
private:
public:
	static std::vector<int> spriteIDVec;//Contains the ids of all the Sprites in the game

	Isprite(void);
	virtual ~Isprite(void);

	static int spriteglobalPrevIdCheck;
	static int spriteglobalNextIdCheck;

	D3DXVECTOR3     spritePosition;
	D3DXVECTOR3     spriteScale;
	float     spriteRotation;

	int spriteID;

	LPCSTR spritetextureLocation;

	virtual void draw();

	virtual void setSpritePosition(float, float);
	virtual void setSpriteRotation(float);
	virtual void setSpriteScale(float, float);

	virtual float getSpritePositionX();
	virtual float getSpritePositionY();

	virtual float getSpriteRotation();

	virtual float getSpriteScaleX();
	virtual float getSpriteScaleY();

	virtual void addSpriteId() = 0;
	virtual int  spriteId() = 0;
	virtual int  getSpriteId() = 0;
};