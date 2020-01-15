#include "Iactor.h"

std::vector<int> Iactor::actorIDVec;//Contains the ids of all the actors in the game
int Iactor::globalPrevIdCheck;
int Iactor::globalNextIdCheck;
Iactor::Iactor(void){
}
Iactor::~Iactor(void){
}
void Iactor::draw(){
}

void Iactor::setActorPosition(float, float, float){
}
void Iactor::setActorRotation(float, float, float){
}

float Iactor::getActorPositionX(){
	return modelPosition.x;
}
float Iactor::getActorPositionY(){
	return modelPosition.y;
}
float Iactor::getActorPositionZ(){
	return modelPosition.z;
}

float Iactor::getActorRotationX(){
	return modelRotation.x;
}
float Iactor::getActorRotationY(){
	return modelRotation.y;
}
float Iactor::getActorRotationZ(){
	return modelRotation.z;
}

 ID3DX10Mesh* Iactor::getActorMesh()
 {
	 return pActorMesh;
 }

void Iactor::enableLighting(){
}

void  Iactor::setLightingAmbient(float R, float G, float B, float A){
}
void  Iactor::setLightingPos(float X, float Y, float Z){
}
void Iactor::setLightingColour(float R, float G, float B, float A){
}
void  Iactor::setLightingProperties(float ambience, float diffuse, float specular, float shininess){
}

void Iactor::addActorId(){
}
int Iactor::actorId(){
	return actorID;
}

int Iactor::getActorId()
{
	return actorID;
}
//const char* Iactor::pGetActorId(){
//	return name;
//}