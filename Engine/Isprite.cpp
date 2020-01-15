#include "Isprite.h"

std::vector<int> Isprite::spriteIDVec;//Contains the ids of all the Sprites in the game
int Isprite::spriteglobalPrevIdCheck;
int Isprite::spriteglobalNextIdCheck;
Isprite::Isprite(void){
}
Isprite::~Isprite(void){
}
void Isprite::draw(){
}

void Isprite::setSpritePosition(float, float){
}
void Isprite::setSpriteRotation(float){
}
void Isprite::setSpriteScale(float, float){
}
void Isprite::addSpriteId(){
}
int Isprite::spriteId(){
	return spriteID;
}

float Isprite::getSpritePositionX(){
	return spritePosition.x;
}
float Isprite::getSpritePositionY(){
	return spritePosition.y;
}

float Isprite::getSpriteRotation(){
	return spriteRotation;
}

float Isprite::getSpriteScaleX()
{
	return spriteScale.x;
}

float Isprite::getSpriteScaleY()
{
	return spriteScale.y;
}

int Isprite::getSpriteId()
{
	return spriteID;
}