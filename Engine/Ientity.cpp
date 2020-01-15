#include "Ientity.h"

std::vector<int> Ientity::entityIDVec;//Contains the ids of all the actors in the game
int Ientity::globalPrevIdCheck;
int Ientity::globalNextIdCheck;
Ientity::Ientity(void){
}
Ientity::~Ientity(void){
}
void Ientity::draw(){
}

void Ientity::setEntityPosition(float, float, float){
}
void Ientity::setEntityRotation(float, float, float){
}

float Ientity::getEntityPositionX(){
	return modelPosition.x;
}
float Ientity::getEntityPositionY(){
	return modelPosition.y;
}
float Ientity::getEntityPositionZ(){
	return modelPosition.z;
}

float Ientity::getEntityRotationX(){
	return modelRotation.x;
}
float Ientity::getEntityRotationY(){
	return modelRotation.y;
}
float Ientity::getEntityRotationZ(){
	return modelRotation.z;
}

void Ientity::lighting(){
}

void Ientity::addEntityId(){
}
int Ientity::entityId(){
	return entityID;
}

int Ientity::getEntityId()
{
	return entityID;
}