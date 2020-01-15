#ifndef DXSPRITE_H
#define DXSPRITE_H

#include "Isprite.h"
#include "dxBaseSprite.h"

#include <cstdlib>
#include <time.h>
#include <stdint.h>

class dxSprite: public Isprite
{
private:
	dxBaseSprite* pMySprite;
public:
	dxSprite();
	~dxSprite();

	D3DXVECTOR2					spriteScale;//Root scale and position of the sprite
	D3DXVECTOR2					spritePosition;
	float											spriteRotation;

	void load();
	void update();
	void draw();
	void destroy();

	void setSpritePosition(float posX, float posY);
	void setSpriteRotation(float rot);
	void setSpriteScale(float scaleX, float scaleY);

	float getSpritePositionX();
	float getSpritePositionY();
	float getSpriteRotation();
	float getSpriteScaleX();
	float getSpriteScaleY();

	int spriteId();
	int getSpriteId();
	void addSpriteId();

	static int swappedSpriteID;
	static LPCSTR spriteswappedTexture;
};
int dxSprite::swappedSpriteID;
LPCSTR dxSprite::spriteswappedTexture;

dxSprite::dxSprite()
{
	pMySprite = new dxBaseSprite;
}
dxSprite::~dxSprite(){}

int dxSprite::getSpriteId()
{
	return spriteID;
}

void dxSprite::addSpriteId()
{
	spriteIDVec.push_back(spriteId());
}

int dxSprite::spriteId()
{
	srand( time(NULL));

	spriteglobalNextIdCheck = rand() % 1000 + rand();//Generate the actor id
	spriteID = spriteglobalNextIdCheck;//Needed to avoid last out duplications

	spriteID = rand() % 1000 + rand();
	//Do a quick check to see if we have a clash, and, if we do: change it.
	if(spriteID == spriteglobalPrevIdCheck){
		spriteID = rand() % 1000 + 60;
	}
	//Assign current id into previous variable.
	spriteglobalPrevIdCheck = spriteID;//to ensure no first in duplications.
	spriteglobalNextIdCheck = rand() % 1000 + rand();//To ensure there is not an existing duplication when we come into the function again.

	return spriteID;
}

float dxSprite::getSpritePositionX()
{
	return spritePosition.x;
}

float dxSprite::getSpritePositionY()
{
	return spritePosition.y;
}

float dxSprite::getSpriteRotation()
{
	return spriteRotation;
}

float dxSprite::getSpriteScaleX()
{
	return spriteScale.x;
}

float dxSprite::getSpriteScaleY()
{
	return spriteScale.y;
}

void dxSprite::setSpritePosition(float posX, float posY)
{
	spritePosition.x = posX;
	spritePosition.y = posY;
}

void dxSprite::setSpriteRotation(float rot)
{
	spriteRotation = rot;
}

void dxSprite::setSpriteScale(float scaleX, float scaleY)
{
	spriteScale.x = scaleX;
	spriteScale.y = scaleY;
}

void dxSprite::load()
{
	//pMySprite->addClass();

	//pMySprite->classId;

	spriteswappedTexture	= spritetextureLocation;
	pMySprite->loadSprite(spriteswappedTexture);
}

void dxSprite::update()
{
}

void dxSprite::draw()
{
	pMySprite->rotate(spriteRotation);
	pMySprite->translate(spritePosition);
	pMySprite->scale(spriteScale);

	pMySprite->render();
}

void dxSprite::destroy()
{
	delete pMySprite;
}

#endif