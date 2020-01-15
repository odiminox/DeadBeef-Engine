#ifndef DXACTOR_H_
#define DXACTOR_H_

#include "Iactor.h"
#include "dxBaseModel.h"

#include <cstdlib>
#include <time.h>
#include <stdint.h>

//This is where we are going to create our basic primitives

class dxActor: public Iactor
{
private:


public:
	dxActor();
	~dxActor();

	D3DXVECTOR3     modelPosition;
	D3DXVECTOR3     modelRotation;

	ID3DX10Mesh*       pActorMesh;
		dxBaseModel* pMyModel;
	float lightColourR;
	float lightColourG;
	float lightColourB;
	float lightColourA;

	float lightPosX;
	float lightPosY;
	float lightPosZ;

	float lightAmb;
	float lightSpec;
	float lighDiff;
	float lightShin;

	float lightAmbientR;
	float lightAmbientG;
	float lightAmbientB;
	float lightAmbientA;

	void load();
	void update();
	void draw();
	void destroy();

	void setActorPosition(float posX, float posY, float posZ);
	void setActorRotation(float rotX, float rotY, float rotZ);

	float getActorPositionX();
	float getActorPositionY();
	float getActorPositionZ();

	float getActorRotationX();
	float getActorRotationY();
	float getActorRotationZ();

	ID3DX10Mesh* getActorMesh();
	std::string* getActorLocation();
	LPCSTR* getActorTexture();

	void addActorId();
	int actorId();
	int getActorId();

	void enableLighting();
	void setLightingAmbient(float R, float G, float B, float A);
	void setLightingPos(float X, float Y, float Z);
	void setLightingColour(float R, float G, float B, float A);
	void setLightingProperties(float ambience, float diffuse, float specular, float shininess);

	static int swappedActorID;
	static std::string swappedLocation;
	static LPCSTR swappedTexture;
	static LPCSTR swappedBumpLocation;
	static LPCSTR swappedSpecLocation;
};
int dxActor::swappedActorID;
std::string dxActor::swappedLocation;
LPCSTR dxActor::swappedTexture;
LPCSTR dxActor::swappedBumpLocation;
LPCSTR dxActor::swappedSpecLocation;

dxActor::dxActor(): lightColourR(0.0f),  lightColourG(0.0f), lightColourB(0.0f), lightColourA(0.0f),
								lightPosX(0.0f), lightPosY(0.0f), lightPosZ(0.0f),
								lightAmb(0.0f), lightSpec(0.0f), lighDiff(0.0f), lightShin(0.0f),
								lightAmbientR(0.0f), lightAmbientG(0.0f), lightAmbientB(0.0f), lightAmbientA(0.0f)
{
	pMyModel	  = new dxBaseModel;

	//Default locations for the texture and bump map to fill out the vector. Cheap and dirty fix.
	//swappedTexture = "./Textures/Directx 10.png";
	//swappedBumpLocation = "./Textures/Directx 10.png";
}

dxActor::~dxActor(){}

int dxActor::getActorId()
{
	return actorID;
}

void dxActor::addActorId()
 {
	actorIDVec.push_back(actorId());
}
int dxActor::actorId()
{
	srand( time(NULL));

	globalNextIdCheck = rand() % 1000;
	actorID = globalNextIdCheck;//Needed to avoid last out duplications

	actorID = rand() % 1000 + rand();

	//Do a quick check to see if we have a clash, and, if we do: change it.
	if(actorID == globalPrevIdCheck) actorID = rand() % 1000;
	//Assign current id into previous variable.
	globalPrevIdCheck = actorID;//to ensure no first in duplications.
	globalNextIdCheck = rand() % 1000;//To ensure there is not an existing duplication when we come into the function again.

	//Check against all actorIDs in the vector and fix duplication issues
	if(actorIDVec.size() != 0)
	{
		for(int i = 0; i <= actorIDVec.size() - 1; i++)
		{
			if(actorIDVec[i] == actorID)
				actorID = rand() % 1000;
		}
	}
	//Due to fast execution of method, check if we are not already in the current actorID to prevent duplications
	//if(actorID != actorID)
		//actorIDVec.push_back(actorID);

	return actorID;
}

void dxActor::setLightingPos(float X, float Y, float Z)
{
	lightPosX = X;
	lightPosY = Y;
	lightPosZ = Z;
}

void dxActor::setLightingColour(float R, float G, float B, float A)
{
	lightColourR = R;
	lightColourG = G;
	lightColourB = B;
	lightColourA = A;
}

void dxActor::setLightingProperties(float ambience, float diffuse, float specular, float shininess)
{
	lightAmb   = ambience;
	lighDiff      = diffuse;
	lightSpec  = specular;
	lightShin   = shininess;
}

void dxActor::setLightingAmbient(float R, float G, float B, float A)
{
	lightAmbientR = R;
	lightAmbientG = G;
	lightAmbientB = B;
	lightAmbientA = A;
}

void dxActor::enableLighting()
{
	pMyModel->myLight.setAmbient(lightAmbientR, lightColourG, lightColourB, lightColourA);
	pMyModel->myLight.createDirectionalLight(lightColourR, lightColourG, lightColourB, lightColourA, lightPosX, lightPosY, lightPosZ);
	pMyModel->myLight.materialProperties(lightAmb, lighDiff, lightSpec, lightShin);
}

void dxActor::setActorPosition(float posX, float posY, float posZ)
{
	modelPosition.x = posX;
	modelPosition.y = posY;
	modelPosition.z = posZ;
}

void dxActor::setActorRotation(float rotX, float rotY, float rotZ)
{
	modelRotation.x = rotX;
	modelRotation.y = rotY;
	modelRotation.z = rotZ;
}

float dxActor::getActorPositionX()
{
	return modelPosition.x;
}
float dxActor::getActorPositionY()
{
	return modelPosition.y;
}
float dxActor::getActorPositionZ()
{
	return modelPosition.z;
}

float dxActor::getActorRotationX()
{
	return modelRotation.x;
}
float dxActor::getActorRotationY()
{
	return modelRotation.y;
}
float dxActor::getActorRotationZ()
{
	return modelRotation.z;
}

ID3DX10Mesh* dxActor::getActorMesh()
{
	pActorMesh = pMyModel->pMesh;
	return pActorMesh;
}

void dxActor::load()
{
	pMyModel->addClass();//Assign our incoming actors some ids for object management.

	//addActorId();
	//Returns the class id, so we check if the same class is loaded multiple times.
	pMyModel->classId;//So currently we check every time the pMyModel is called into use from each actor

	swappedActorID   = actorID;
	swappedLocation  = modelLocation;//Swap the interface data into the static member to correctly overload and then pass in carried data.
	swappedTexture   = textureLocation;
	swappedBumpLocation = bumpLocation;
	swappedSpecLocation = specularLocation;

	pMyModel->pMesh = pActorMesh;
	pMyModel->loadModel(swappedLocation, swappedTexture, swappedBumpLocation, swappedSpecLocation);
	//pActorMesh = pMyModel->pMesh;
}
void dxActor::update()
{
}
void dxActor::draw()
{//Might need some modification here depending on the update and parsing in new data from input
	pMyModel->rotate(modelRotation);
	pMyModel->translate(modelPosition);

	pMyModel->render();
}
void dxActor::destroy()
{
	delete pMyModel;
}

#endif