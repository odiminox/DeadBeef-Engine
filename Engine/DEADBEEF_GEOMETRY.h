#include "dxActor.h"
#include "dxSprite.h"
class DEADBEEF_Geometry
{
private:

public:

	static std::vector<dxActor*>  m_IactorVec;//So we can render everything with a loop through to the interface for the actor class
	static std::vector<dxActor*>  sceneryModels;
	static std::vector<Isprite*> m_IspriteVec;
	static std::vector<Iactor*>  m_IcopyActorVec;

	static float lightPosX;
	static float lightPosY;
	static float lightPosZ;

	static bool bumpEnabled;

	std::string m_sVectorStats;

	static int copyActorCounter;

	//Actors and sprites remain separate to easier control and allocation/deallocation of memory resources once a memory manager has been incorporated into the engine.

	//Class methods for Actor control
	void loadAllActors();
	void updateAllActors();
	void renderAllActors();
	void destroyAllActors();

	static void createContinent(int numOfContinents);
	static void initialiseContinentData(int actorNum, float continentHealth, float continentProgression);
	static void updateAllContinents();

	static void createActors(int numOfActors);
	static void initialiseActorData(int actorNum, std::string modelLocation, LPCSTR textureLocation, LPCSTR bumpLocation, LPCSTR specularLocation);
	static void initialiseActorRotLoc(int actorNum,float rotX, float rotY, float rotZ, float posX, float posY, float posZ);
	static void drawActor(int actorNum, float rotX, float rotY, float rotZ, float posX, float posY, float posZ);
	static void copyActor(int actorNum, float rotX, float rotY, float rotZ, float posX, float posY, float posZ);
	static void instanceCopyActor(int actorNum, int copyAcorNum);
	static void renderActorSpecific(int actorNum);
	static void renderCopyActorSpecific(int copyActorNum);


	//Class methods for sprite control
	void loadAllSprites();
	void updateAllSprites();
	void renderAllSprites();
	void destroyAllSprites();

	static void createSprites(int numOfSprites);
	static void initialiseSprite(int spriteNum, LPCSTR spritetextureLocation, float rot, float posX, float posY, float scaleX, float scaleY);
	static void drawSprite(int spriteNum, float rot, float scaleX, float scaleY, float posX, float posY);
	static void renderSpriteSpecific(int spriteNum);

	//Set the per-object lighting
	void enableLighting();
	void setLightingAmbient(float R, float G, float B, float A);
	void setLightingPos(float X, float Y, float Z);
	void setLightingColour(float R, float G, float B, float A);
	void setLightingProperties(float ambience, float diffuse, float specular, float shininess);

	float getLightingPosX(int actorNum);
	float getLightingPosY(int actorNum);
	float getLightingPosZ(int actorNum);

	//Camera control functions
	void attatchCameraToActor(int actorNum, float offSetX, float offSetY, float offSetZ);
	void attatchCameraToSprite(int spriteNum);
	void translateCamera(float camX, float camY, float camZ);

	DEADBEEF_Geometry();
	~DEADBEEF_Geometry();
};

std::vector<dxActor*>  DEADBEEF_Geometry::m_IactorVec;
std::vector<Isprite*> DEADBEEF_Geometry::m_IspriteVec;
std::vector<dxActor*> DEADBEEF_Geometry::sceneryModels;
std::vector<Iactor*> DEADBEEF_Geometry::m_IcopyActorVec;


int DEADBEEF_Geometry::copyActorCounter;
bool DEADBEEF_Geometry::bumpEnabled;

float DEADBEEF_Geometry::lightPosX;
float DEADBEEF_Geometry::lightPosY;
float DEADBEEF_Geometry::lightPosZ;

DEADBEEF_Geometry::DEADBEEF_Geometry()
{
	bumpEnabled = true;
}

DEADBEEF_Geometry::~DEADBEEF_Geometry(){}

void DEADBEEF_Geometry::renderActorSpecific(int actorNum)
{
	m_IactorVec[actorNum]->draw();
}

void DEADBEEF_Geometry::renderCopyActorSpecific(int copyActorNum)
{
	m_IcopyActorVec[copyActorNum]->draw();
}

void DEADBEEF_Geometry::renderSpriteSpecific(int spriteNum)
{
	m_IspriteVec[spriteNum]->draw();
}

void DEADBEEF_Geometry::copyActor(int actorNum, float rotX, float rotY, float rotZ, float posX, float posY, float posZ)
{
	dxActor* myActor;
	m_IcopyActorVec.push_back(myActor = new dxActor);

	m_IcopyActorVec[copyActorCounter]->modelLocation = m_IactorVec[actorNum]->modelLocation;
	m_IcopyActorVec[copyActorCounter]->textureLocation = m_IactorVec[actorNum]->textureLocation;
	m_IcopyActorVec[copyActorCounter]->bumpLocation = m_IactorVec[actorNum]->bumpLocation;

	m_IcopyActorVec[copyActorCounter]->setActorRotation(rotX, rotY, rotZ);
	m_IcopyActorVec[copyActorCounter]->setActorPosition(posX, posY, posZ);

	copyActorCounter++;
}

void DEADBEEF_Geometry::instanceCopyActor(int actorNum, int copyAcorNum)
{
//	m_IcopyActorVec[copyAcorNum]->pActorMesh = m_IactorVec[actorNum]->getActorMesh();
	//m_IcopyActorVec[copyAcorNum]->load();
}

//void DEADBEEF_Geometry::attatchCameraToActor(int actorNum, float offSetX, float offSetY, float offSetZ)
//{
//	myCamera.m_fLookatX = m_IactorVec[actorNum]->getActorPositionX() + offSetX;
//	myCamera.m_fLookatY = m_IactorVec[actorNum]->getActorPositionY() + offSetY;
//	myCamera.m_fLookatZ = m_IactorVec[actorNum]->getActorPositionZ() + offSetZ;
//}
//Attaching a 3D camera to a sprite? hmmn, I'll leave it in for now. Not the desire effect however.
//void DEADBEEF_Geometry::attatchCameraToSprite(int spriteNum)
//{
//	myCamera.m_fLookatX = m_IspriteVec[spriteNum]->getSpritePositionX();
//	myCamera.m_fLookatY = m_IspriteVec[spriteNum]->getSpritePositionY();
//}

void DEADBEEF_Geometry::initialiseActorData(int actorNum, std::string modelLocation, LPCSTR textureLocation, LPCSTR bumpLocation, LPCSTR specLocation)
{
	m_IactorVec[actorNum]->addActorId();

	m_IactorVec[actorNum]->modelLocation	 = modelLocation;
	m_IactorVec[actorNum]->textureLocation = textureLocation;
	m_IactorVec[actorNum]->bumpLocation    = bumpLocation;
	m_IactorVec[actorNum]->specularLocation = specLocation;
}

void DEADBEEF_Geometry::initialiseActorRotLoc(int actorNum,float rotX, float rotY, float rotZ, float posX, float posY, float posZ)
{
	m_IactorVec[actorNum]->setActorRotation(rotX, rotY, rotZ);
	m_IactorVec[actorNum]->setActorPosition(posX, posY, posZ);
}

void DEADBEEF_Geometry::drawActor(int actorNum, float rotX, float rotY, float rotZ, float posX, float posY, float posZ)
{
	m_IactorVec[actorNum]->setActorRotation(rotX, rotY, rotZ);
	m_IactorVec[actorNum]->setActorPosition(posX, posY, posZ);
}

void DEADBEEF_Geometry::enableLighting()
{
	for (unsigned int i = 0; i < m_IactorVec.size(); i++)
	{
		m_IactorVec[i]->enableLighting();
	}

	for (unsigned int i = 0; i < m_IcopyActorVec.size(); i++)
	{
		m_IcopyActorVec[i]->enableLighting();
	}
}
void DEADBEEF_Geometry::setLightingPos(float X, float Y, float Z)
{
	for (unsigned int i = 0; i < m_IactorVec.size(); i++)
	{
		lightPosX = X;//what the fuck? I need to fix that
		m_IactorVec[i]->lightPosX = lightPosX;
		lightPosY = Y;
		m_IactorVec[i]->lightPosY = lightPosY;
		lightPosZ = Z;
		m_IactorVec[i]->lightPosZ = lightPosZ;
		m_IactorVec[i]->setLightingPos(lightPosX, lightPosY, lightPosZ);
	}

	for (unsigned int i = 0; i < m_IcopyActorVec.size(); i++)
	{
		lightPosX = X;//What???
		lightPosY = Y;
		lightPosZ = Z;
		m_IcopyActorVec[i]->setLightingPos(lightPosX, lightPosY, lightPosZ);
	}
}

float DEADBEEF_Geometry::getLightingPosX(int actorNum)
{
	return m_IactorVec[actorNum]->lightPosX;
}

float DEADBEEF_Geometry::getLightingPosY(int actorNum)
{
	return m_IactorVec[actorNum]->lightPosY;
}

float DEADBEEF_Geometry::getLightingPosZ(int actorNum)
{
	return m_IactorVec[actorNum]->lightPosZ;
}

void DEADBEEF_Geometry::setLightingColour(float R, float G, float B, float A)
{
	for (unsigned int i = 0; i < m_IactorVec.size(); i++)
	{
		m_IactorVec[i]->setLightingColour(R, G, B, A);
	}

	for (unsigned int i = 0; i < m_IcopyActorVec.size(); i++)
	{
		m_IcopyActorVec[i]->setLightingColour(R, G, B, A);
	}
}

void DEADBEEF_Geometry::setLightingAmbient(float R, float G, float B, float A)
{
	for (unsigned int i = 0; i < m_IactorVec.size(); i++)
	{
		m_IactorVec[i]->setLightingAmbient(R, G, B, A);
	}

	for (unsigned int i = 0; i < m_IcopyActorVec.size(); i++)
	{
		m_IcopyActorVec[i]->setLightingAmbient(R, G, B, A);
	}
}

void DEADBEEF_Geometry::setLightingProperties(float ambience, float diffuse, float specular, float shininess)
{
	for (unsigned int i = 0; i < m_IactorVec.size(); i++)
	{
		m_IactorVec[i]->setLightingProperties(ambience, diffuse, specular, shininess);
	}

	for (unsigned int i = 0; i < m_IcopyActorVec.size(); i++)
	{
		m_IcopyActorVec[i]->setLightingProperties(ambience, diffuse, specular, shininess);
	}
}

void DEADBEEF_Geometry::createActors(int numOfActors)
{
	for(int i = 0; i < numOfActors; i++)
	{
		dxActor* myActor;
		m_IactorVec.push_back(myActor = new dxActor);
	}
}


void DEADBEEF_Geometry::loadAllActors()
{
	for (unsigned int i = 0; i < m_IactorVec.size(); i++)
	{
		m_IactorVec[i]->load();
	}

	for(unsigned int i = 0; i < m_IcopyActorVec.size(); i++)
	{
		m_IcopyActorVec[i]->load();
	}
}


void DEADBEEF_Geometry::renderAllActors()
{
	for (unsigned int i = 0; i < m_IactorVec.size(); i++)
	{
		m_IactorVec[i]->draw();
	}

	for(unsigned int i = 0; i < m_IcopyActorVec.size(); i++)
	{
		m_IcopyActorVec[i]->draw();
	}
}


void DEADBEEF_Geometry::updateAllActors()
{
	for (unsigned int i = 0; i < m_IactorVec.size(); i++)
	{
		m_IactorVec[i]->update();
	}

	for(unsigned int i = 0; i < m_IcopyActorVec.size(); i++)
	{
		m_IcopyActorVec[i]->update();
	}
}


void DEADBEEF_Geometry::destroyAllActors()
{
	for (unsigned int i = 0; i < m_IactorVec.size(); i++)
	{
		m_IactorVec[i]->destroy();
	}

	for(unsigned int i = 0; i < m_IcopyActorVec.size(); i++)
	{
		m_IcopyActorVec[i]->destroy();
	}
}

void DEADBEEF_Geometry::initialiseSprite(int spriteNum, LPCSTR spritetextureLocation, float rot, float posX, float posY, float scaleX, float scaleY)
{
	m_IspriteVec[spriteNum]->spriteId();
	m_IspriteVec[spriteNum]->spritetextureLocation = spritetextureLocation;
	m_IspriteVec[spriteNum]->setSpriteRotation(rot);
	m_IspriteVec[spriteNum]->setSpritePosition(posX, posY);
	m_IspriteVec[spriteNum]->setSpriteScale(scaleX, scaleY);
}

void DEADBEEF_Geometry::drawSprite(int spriteNum, float rot, float scaleX, float scaleY, float posX, float posY)
{
	m_IspriteVec[spriteNum]->addSpriteId();
	m_IspriteVec[spriteNum]->setSpriteRotation(rot);
	m_IspriteVec[spriteNum]->setSpritePosition(posX, posY);
	m_IspriteVec[spriteNum]->setSpriteScale(scaleX, scaleY);
}

void DEADBEEF_Geometry::createSprites(int numOfSprites)
{
	for(int i = 0; i < numOfSprites; i++)
	{
		dxSprite* mySprite;
		m_IspriteVec.push_back(mySprite = new dxSprite);
	}
}

void DEADBEEF_Geometry::loadAllSprites()
{
	for (unsigned int i = 0; i < m_IspriteVec.size(); i++)
	{
		m_IspriteVec[i]->load();
	}
}

void DEADBEEF_Geometry::renderAllSprites()
{
	for (unsigned int i = 0; i < m_IspriteVec.size(); i++)
	{
		m_IspriteVec[i]->draw();
	}
}

void DEADBEEF_Geometry::updateAllSprites()
{
	for (unsigned int i = 0; i < m_IspriteVec.size(); i++)
	{
		m_IspriteVec[i]->update();
	}
}

void DEADBEEF_Geometry::destroyAllSprites()
{
	for (unsigned int i = 0; i < m_IspriteVec.size(); i++)
	{
		m_IspriteVec[i]->destroy();
	}
}