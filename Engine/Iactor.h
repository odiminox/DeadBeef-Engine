#ifndef IACTOR
#define IACTOR

#include "IupdateActor.h"

#include <d3d10.h>
#include <d3dx10.h>
#include <string>
#include <iostream>
#include <Windows.h>
#include <vector>


class Iactor: public IupdateActor
{
private:
public:
	Iactor(void);
	virtual ~Iactor(void);

	static std::vector<int> actorIDVec;//Contains the ids of all the actors in the game

	static int globalPrevIdCheck;
	static int globalNextIdCheck;

	int actorID;

	std::string modelLocation;
	LPCSTR textureLocation;
	LPCSTR bumpLocation;
	LPCSTR specularLocation;

	float lightPosX;
	float lightPosY;
	float lightPosZ;

	D3DXVECTOR3     modelPosition;
	D3DXVECTOR3     modelRotation;

	ID3DX10Mesh*       pActorMesh;

	virtual void draw();
	virtual void setActorPosition(float, float, float);
	virtual void setActorRotation(float, float, float);

	virtual float getActorPositionX();
	virtual float getActorPositionY();
	virtual float getActorPositionZ();

	virtual float getActorRotationX();
	virtual float getActorRotationY();
	virtual float getActorRotationZ();

	virtual void addActorId() = 0;
	virtual int  actorId() = 0;
	virtual int  getActorId() = 0;
	virtual ID3DX10Mesh* getActorMesh();
	//virtual const char* pGetActorId() = 0;

	virtual void enableLighting();
	virtual void setLightingAmbient(float R, float G, float B, float A);
	virtual void setLightingPos(float X, float Y, float Z);
	virtual void setLightingColour(float R, float G, float B, float A);
	virtual void setLightingProperties(float ambience, float diffuse, float specular, float shininess);
};

#endif