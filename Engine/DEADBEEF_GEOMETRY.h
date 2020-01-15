#include "dxActor.h"
#include "dxSprite.h"
#include "Continents.h"
class DEADBEEF_Geometry
{
private:

public:

	static std::vector<dxActor*>  m_IactorVec;//So we can render everything with a loop through to the interface for the actor class
	static std::vector<dxActor*>  sceneryModels;
	static std::vector<Isprite*> m_IspriteVec;
	static std::vector<Iactor*>  m_IcopyActorVec;
	static std::vector<continents*> m_ContinentVec;

	static float lightPosX;
	static float lightPosY;
	static float lightPosZ;

	static float m_continentHealth[5];
	static float m_continentResearch[5];

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

	static void createSceneryMesh(int numOfMeshes);
	static void initialiseSceneryData(int sceneryNum, std::string modelLocation, LPCSTR textureLocation, LPCSTR bumpLocation, LPCSTR specularLocation);
	static void initialiseSceneryRotLoc(int sceneryNum,float rotX, float rotY, float rotZ, float posX, float posY, float posZ);
	static void drawScenery(int sceneryNum, float rotX, float rotY, float rotZ, float posX, float posY, float posZ);
	static void renderspecificScenery(int sceneryNum);

	void loadAllSceneries();
	void updateAllSceneries();
	void renderAllSceneries();
	void destroyAllSceneries();


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
std::vector<continents*> DEADBEEF_Geometry::m_ContinentVec;

 float DEADBEEF_Geometry::m_continentHealth[];
 float DEADBEEF_Geometry::m_continentResearch[];


int DEADBEEF_Geometry::copyActorCounter;
bool DEADBEEF_Geometry::bumpEnabled;

float DEADBEEF_Geometry::lightPosX;
float DEADBEEF_Geometry::lightPosY;
float DEADBEEF_Geometry::lightPosZ;

DEADBEEF_Geometry::DEADBEEF_Geometry()
{
	m_continentHealth[0] = 500;
	m_continentHealth[1] = 500;
	m_continentHealth[2] = 500;
	m_continentHealth[3] = 500;
	m_continentHealth[4] = 500;
	bumpEnabled = true;
}

DEADBEEF_Geometry::~DEADBEEF_Geometry(){}

void DEADBEEF_Geometry::renderActorSpecific(int actorNum)
{
	m_IactorVec[actorNum]->draw();
}

void DEADBEEF_Geometry::renderspecificScenery(int sceneryNum)
{
	sceneryModels[sceneryNum]->draw();
}

void DEADBEEF_Geometry::createContinent(int numOfContinents)
{
	for(int i = 0; i < numOfContinents; i++)
	{
		continents* newContinent;
		m_ContinentVec.push_back(newContinent = new continents);
	}
}

void DEADBEEF_Geometry::updateAllContinents()
{

	m_ContinentVec[0]->updateContinentData(m_continentHealth[0], m_continentResearch[0]);
	m_ContinentVec[1]->updateContinentData(m_continentHealth[1], m_continentResearch[1]);
	m_ContinentVec[2]->updateContinentData(m_continentHealth[2], m_continentResearch[2]);
	m_ContinentVec[3]->updateContinentData(m_continentHealth[3], m_continentResearch[3]);
	m_ContinentVec[4]->updateContinentData(m_continentHealth[4], m_continentResearch[4]);
}

void DEADBEEF_Geometry::initialiseContinentData(int continentNum, float continentHealth, float continentProgression)
{
	m_ContinentVec[continentNum]->continentHealth = continentHealth;
	m_ContinentVec[continentNum]->continentResearch = continentHealth;
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

void DEADBEEF_Geometry::initialiseSceneryData(int sceneryNum, std::string modelLocation, LPCSTR textureLocation, LPCSTR bumpLocation, LPCSTR specLocation)
{
	sceneryModels[sceneryNum]->addActorId();

	sceneryModels[sceneryNum]->modelLocation	 = modelLocation;
	sceneryModels[sceneryNum]->textureLocation = textureLocation;
	sceneryModels[sceneryNum]->bumpLocation    = bumpLocation;
	sceneryModels[sceneryNum]->specularLocation = specLocation;
}



void DEADBEEF_Geometry::initialiseActorRotLoc(int actorNum,float rotX, float rotY, float rotZ, float posX, float posY, float posZ)
{
	m_IactorVec[actorNum]->setActorRotation(rotX, rotY, rotZ);
	m_IactorVec[actorNum]->setActorPosition(posX, posY, posZ);
}

void DEADBEEF_Geometry::initialiseSceneryRotLoc(int sceneryNum,float rotX, float rotY, float rotZ, float posX, float posY, float posZ)
{
	sceneryModels[sceneryNum]->setActorRotation(rotX, rotY, rotZ);
	sceneryModels[sceneryNum]->setActorPosition(posX, posY, posZ);
}

void DEADBEEF_Geometry::drawScenery(int sceneryNum, float rotX, float rotY, float rotZ, float posX, float posY, float posZ)
{
	sceneryModels[sceneryNum]->setActorRotation(rotX, rotY, rotZ);
	sceneryModels[sceneryNum]->setActorPosition(posX, posY, posZ);
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

void DEADBEEF_Geometry::createSceneryMesh(int numOfMeshes)
{
	for(int i = 0; i < numOfMeshes; i++)
	{
		dxActor* myMesh;
		sceneryModels.push_back(myMesh = new dxActor);
	}
}

void DEADBEEF_Geometry::loadAllSceneries()
{
	for (unsigned int i = 0; i < sceneryModels.size(); i++)
	{
		sceneryModels[i]->load();
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

void DEADBEEF_Geometry::renderAllSceneries()
{
	for (unsigned int i = 0; i < sceneryModels.size(); i++)
	{
		sceneryModels[i]->draw();
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

void DEADBEEF_Geometry::updateAllSceneries()
{
	for (unsigned int i = 0; i < sceneryModels.size(); i++)
	{
		sceneryModels[i]->update();
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

void DEADBEEF_Geometry::destroyAllSceneries()
{
	for (unsigned int i = 0; i < sceneryModels.size(); i++)
	{
		sceneryModels[i]->destroy();
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