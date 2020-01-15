#ifndef DEADBEEF_CORE_H_
#define DEADBEEF_CORE_H_

#include "DEADBEEF_ENGINE.h"
#include "DEADBEEF_GEOMETRY.h"
#include "dxLightManager.h"

class DEADBEEF_CORE:  public DEADBEEF, public DEADBEEF_Geometry
{
public:
	//dxlightManager DBCoreLight;

	DEADBEEF_CORE();

	std::vector<dxlightManager*>  m_LightVec;

	std::string lightStats;
	std::string debugText;

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

	void initialiseFPSCamera(float, float, float);
	void translateFPSCamera(float&, float, float);
	void rotateFPSCamera(float&, float&, float&);
	void walkFPSCamera(float, float);
	void strafeFPSCamera(float);
	void renderFPSCamera();

	void translateOrbitCamera(float, float, float);
	void rotateOrbitCamera(float&, float&, float&);
	void renderOrbitCamera();

	void initialiseMouse();

	void createLights(int numLights);

	void orthographicCamera();
	void orthoCamera(D3DXMATRIX &in_projectionMatrix, D3D10_VIEWPORT &in_viewPort);

	void setLightAmbient(int lightNum, float R, float G, float B, float A);
	void setLightProperties(int lightNum, float ambience, float diffuse, float specular, float shininess);

	void enableLight(int lightNum);
	void setDirectionalLightPosCol(int lightNum, float X, float Y, float Z, float R, float G, float B, float A);

	void enablePointLight(int lightNum);
	void setPointLightPosCol(int lightNum, float X, float Y, float Z, float R, float G, float B, float A);

	void enableDebugMode();

	void renderCoreLighting();
	void initialiseCoreLighting();

	float getFPSDirectionX();
	float getFPSDirectionY();

	D3DXVECTOR3 getFPSLookat();
	D3DXVECTOR3 getFPSPosition();
	D3DXVECTOR3 getFPSRotation();
	D3DXVECTOR3 getFPSTarget();

private:
};

DEADBEEF_CORE::DEADBEEF_CORE()
{
}

void DEADBEEF_CORE::setPointLightPosCol(int lightNum, float X, float Y, float Z, float R, float G, float B, float A)
{
// 	m_LightVec[lightNum]->lightPosition.x = X;
// 	m_LightVec[lightNum]->lightPosition.y = Y;
// 	m_LightVec[lightNum]->lightPosition.z = Z;
//
// 	m_LightVec[lightNum]->diffuseColor.x = R;
// 	m_LightVec[lightNum]->diffuseColor.y = G;
// 	m_LightVec[lightNum]->diffuseColor.z = B;
// 	m_LightVec[lightNum]->diffuseColor.w = A;
}

void DEADBEEF_CORE::orthoCamera(D3DXMATRIX &in_projectionMatrix, D3D10_VIEWPORT &in_viewPort)
{
	D3DXMatrixOrthoOffCenterLH(&in_projectionMatrix,
		(float)in_viewPort.TopLeftX,
		(float)in_viewPort.Width,
		(float)in_viewPort.TopLeftY,
		(float)in_viewPort.Height,
		0.1f,
		10);
}

void DEADBEEF_CORE::enablePointLight(int lightNum)
{
// 	m_LightVec[lightNum]->diffuseColorPtr = pBasicEffect->GetVariableByName("diffuseColor")->AsVector();
// 	m_LightVec[lightNum]->lightPositionPtr = pBasicEffect->GetVariableByName("lightPosition")->AsVector();
//
// 	// Set the diffuse color of the lights.
// 	m_LightVec[lightNum]->diffuseColorPtr->SetFloatVectorArray((float*)m_LightVec[lightNum]->material.diffuse, 0, 4);
//
// 	// Set the direction of the lights.
// 	m_LightVec[lightNum]->lightPositionPtr->SetFloatVectorArray((float*)m_LightVec[lightNum]->lightPosition, 0, 4);
}

void DEADBEEF_CORE::orthographicCamera()
{
	orthoCamera(projectionMatrix, viewPort);
}

void DEADBEEF_CORE::createLights(int numLights)
{
	for(int i = 0; i < numLights; i++)
	{
		dxlightManager* DBLight;
		m_LightVec.push_back(DBLight = new dxlightManager);
	}
}

void DEADBEEF_CORE::setDirectionalLightPosCol(int lightNum, float X, float Y, float Z, float R, float G, float B, float A)
{
	m_LightVec[lightNum]->createDirectionalLight(R, G, B, A, X, Y, Z);
}

void DEADBEEF_CORE::setLightAmbient(int lightNum, float R, float G, float B, float A)
{
	m_LightVec[lightNum]->setAmbient(R, G, B, A);
}

void DEADBEEF_CORE::setLightProperties(int lightNum, float ambience, float diffuse, float specular, float shininess)
{
	m_LightVec[lightNum]->materialProperties(ambience, diffuse, specular, shininess);
}

void DEADBEEF_CORE::enableLight(int lightNum)
{
	m_LightVec[lightNum]->pLightVar = pBasicEffect->GetVariableByName( "pLight" );
	m_LightVec[lightNum]->pLightVar->SetRawValue(&m_LightVec[lightNum]->pointLight, 0, sizeof(pointLight));

	m_LightVec[lightNum]->pLightVar = pBasicEffect->GetVariableByName( "light" );
	m_LightVec[lightNum]->pLightVar->SetRawValue(&m_LightVec[lightNum]->directionalLight, 0, sizeof(DirectionalLight));

	m_LightVec[lightNum]->pLightVar = pBasicEffect->GetVariableByName( "material" );
	m_LightVec[lightNum]->pLightVar->SetRawValue(&m_LightVec[lightNum]->material, 0, sizeof(Material));

	m_LightVec[lightNum]->pLightVar = pBasicEffect->GetVariableByName( "ambientLight" );
	m_LightVec[lightNum]->pLightVar->SetRawValue( &m_LightVec[lightNum]->ambientLight, 0, 16 );

	m_LightVec[lightNum]->pLightType = pBasicEffect->GetVariableByName("pLightType")->AsScalar();
	m_LightVec[lightNum]->pLightType->SetInt(m_LightVec[lightNum]->LightType);
}

void DEADBEEF_CORE::enableDebugMode()
{
// 	std::ostringstream outs;
// 	outs.precision(5);
// 	outs
// 		<< "\nPLAYER STATS"
// 		<< "\nlookat X: " << Windows->myOrbitCamera->lookat.x
// 		<< "\nlookat Y: " << Windows->myOrbitCamera->lookat.y
// 		<< "\nmouse X: " << Windows->dx
// 		<< "\nmouseY: " << Windows->dy;
// 	m_sVectorStats = outs.str();


	//std::ostringstream out3;
	//out3.precision(3);
	//out3
		//<< "DEBUG MODE ENABLED";
	//debugText = out3.str();

	//renderFont(m_sVectorStats.c_str(), myFont->myRect, 1.0f, 0.0f, 0.0f, 1.0f);//Create a debug mode to display data like this
	//renderFont(lightStats.c_str(), myFont->myRectA, 1.0f, 0.0f, 0.0f, 1.0f);//Create a debug mode to display data like this
	//renderFont(m_sFrameStats.c_str(), myFont->myRectW, 1.0f, 0.0f, 0.0f, 1.0f);//Create a debug mode to display data like this
	//renderFont(debugText.c_str(), myFont->myRectE, 0.0f, 0.0f, 1.0f, 0.3f);//Create a debug mode to display data like this
}

void DEADBEEF_CORE::initialiseMouse()
{
	Windows->mOldMousePosX = Windows->dx;
	Windows->mOldMousePosY = Windows->dy;
}

float DEADBEEF_CORE::getFPSDirectionX()
{
	return Windows->myFPSCamera->directionX;
}

float DEADBEEF_CORE::getFPSDirectionY()
{
	return Windows->myFPSCamera->directionY;
}

D3DXVECTOR3 DEADBEEF_CORE::getFPSTarget()
{
	return Windows->myFPSCamera->right;
}
D3DXVECTOR3 DEADBEEF_CORE::getFPSLookat()
{
	return Windows->myFPSCamera->lookat;
}

D3DXVECTOR3 DEADBEEF_CORE::getFPSPosition()
{
	return Windows->myFPSCamera->position;
}

D3DXVECTOR3 DEADBEEF_CORE::getFPSRotation()
{
	return Windows->myFPSCamera->rotation;
}

void DEADBEEF_CORE::initialiseFPSCamera(float in_headHeight, float in_bobPeriod, float in_bobScale)
{
	Windows->myFPSCamera->initialiseFPSCamera(in_headHeight, in_bobPeriod, in_bobScale);
}
void DEADBEEF_CORE::translateFPSCamera(float &in_CameraX, float in_CameraY, float in_CameraZ)
{
	Windows->myFPSCamera->translateFPSCamera(in_CameraX, in_CameraY, in_CameraZ);
}
void DEADBEEF_CORE::rotateFPSCamera(float &in_rotationX, float &in_rotationY, float &in_rotationZ)
{
	Windows->myFPSCamera->rotateFPSCamera(in_rotationX, in_rotationY, in_rotationZ);
}
void DEADBEEF_CORE::walkFPSCamera(float speed, float sin)
{
	Windows->myFPSCamera->walkFPSCamera(speed, sin);
}
void DEADBEEF_CORE::strafeFPSCamera(float speed)
{
	Windows->myFPSCamera->strafeFPSCamera(speed);
}

void DEADBEEF_CORE::translateOrbitCamera(float in_CameraX, float in_CameraY, float in_CameraZ)
{
	Windows->myOrbitCamera->translateOrbitCamera(in_CameraX, in_CameraY, in_CameraZ);
}

void DEADBEEF_CORE::rotateOrbitCamera(float &in_rotationX, float &in_rotationY, float &in_rotationZ)
{
	Windows->myOrbitCamera->rotateOrbitCamera(in_rotationX, in_rotationY, in_rotationZ);
}
void DEADBEEF_CORE::renderOrbitCamera()
{
	Windows->myOrbitCamera->renderOrbitCamera(projectionMatrix, viewPort, worldMatrix, viewMatrix);
}
void DEADBEEF_CORE::renderFPSCamera()
{
	Windows->myFPSCamera->renderFPSCamera(projectionMatrix, viewPort, worldMatrix, viewMatrix);
}

#endif