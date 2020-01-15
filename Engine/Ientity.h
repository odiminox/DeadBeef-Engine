#ifndef IENTITY
#define IENTITY

#include "IupdateEntity.h"

#include <d3d10.h>
#include <d3dx10.h>
#include <string>
#include <iostream>
#include <Windows.h>
#include <vector>

class Ientity: public IupdateEntity
{
private:
public:
	Ientity(void);
	virtual ~Ientity(void);

	static std::vector<int> entityIDVec;//Contains the ids of all the entities in the game

	static int globalPrevIdCheck;
	static int globalNextIdCheck;

	int entityID;

	std::string modelLocation;
	LPCSTR textureLocation;

	D3DXVECTOR3     modelPosition;
	D3DXVECTOR3     modelRotation;

	virtual void draw();
	virtual void setEntityPosition(float, float, float);
	virtual void setEntityRotation(float, float, float);

	virtual float getEntityPositionX();
	virtual float getEntityPositionY();
	virtual float getEntityPositionZ();

	virtual float getEntityRotationX();
	virtual float getEntityRotationY();
	virtual float getEntityRotationZ();

	virtual void addEntityId() = 0;
	virtual int  entityId() = 0;
	virtual int  getEntityId() = 0;
	//virtual const char* pGetActorId() = 0;

	virtual void lighting();
};

#endif