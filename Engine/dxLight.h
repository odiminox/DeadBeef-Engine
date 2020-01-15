#ifndef DXLIGHTMANAGER_H_
#define DXLIGHTMANAGER_H_

#include "dxBaseLight.h"

class dxLight
{
	private:

	public:
		dxBaseLight* myLight;
		D3DXVECTOR3 position;
		D3DXVECTOR4 colour;
		D3DXVECTOR3 direction;
		D3DXVECTOR4 material;
		D3DXVECTOR4 ambient;
		D3DXVECTOR3 attenuation;
		float range;

		void load();
		void update();
		void destroy();

		void setLightPosition(float posX, float posY, float posZ);
		void setLightColour(float R, float G, float B, float A);
		void setLightDirection(float dirX, float dirY, float dirZ);
		void setMaterials(float ambience, float diffuse, float specular, float shininess);
		void setAmbient(float R, float G, float B, float A);
		void setLightType(int lightType);
		void setAttenutation(float attX, float attY, float attZ);
		void setLightPower(float power);
		void setRange(float range);

		D3DXVECTOR3 getLightPosition();
		D3DXVECTOR4 getLightColour();
		D3DXVECTOR3 getLightDirection();
		D3DXVECTOR4 getLightAmbient();
		D3DXVECTOR4 getLightMaterials();
		D3DXVECTOR3 getLightAttenuation();
		float		getLightRange();

	dxLight();
};

dxLight::dxLight()
{
	myLight = new dxBaseLight;
}

void dxLight::setRange(float range)
{
	myLight->mRange = range;
}

void dxLight::load()
{
	myLight->loadLight();
}

void dxLight::setLightPower(float power)
{
	myLight->mSpotPower = power;
}

void dxLight::setAttenutation(float attX, float attY, float attZ)
{
	myLight->mAttenutation.x = attX;
	myLight->mAttenutation.y = attY;
	myLight->mAttenutation.z = attZ;
}

void dxLight::setLightType(int lightType)
{
	myLight->LightType = lightType;
}

void dxLight::setLightPosition(float posX, float posY, float posZ)
{
	myLight->mPosition.x = posX;
	myLight->mPosition.y = posY;
	myLight->mPosition.z = posZ;
}

void dxLight::setLightColour(float R, float G, float B, float A)
{
	myLight->mColour.x = R;
	myLight->mColour.y = G;
	myLight->mColour.z = B;
	myLight->mColour.x = A;
}

void dxLight::setLightDirection(float X, float Y, float Z)
{
	myLight->mDirection.x = X;
	myLight->mDirection.y = Y;
	myLight->mDirection.z = Z;
}

void dxLight::setMaterials(float ambience, float diffuse, float specular, float shininess)
{
	myLight->mMaterial.x = ambience;
	myLight->mMaterial.y = diffuse;
	myLight->mMaterial.z = specular;
	myLight->mMaterial.w = shininess;
}

void dxLight::setAmbient(float R, float G, float B, float A)
{
	myLight->mAmbient.x = R;
	myLight->mAmbient.y = G;
	myLight->mAmbient.z = B;
	myLight->mAmbient.w = A;
}

void dxLight::update()
{
	myLight->translate(myLight->mPosition);
	myLight->setLightColour(myLight->mColour);
	myLight->setLightDirection(myLight->mDirection);
	myLight->setMaterials(myLight->mMaterial);
	myLight->setAmbient(myLight->mAmbient);
	myLight->setAttenuation(myLight->mAttenutation);
	myLight->setRange(myLight->mRange);
	myLight->setSpotPower(myLight->mSpotPower);
}

D3DXVECTOR3 dxLight::getLightPosition()
{
	return position;
}
D3DXVECTOR3 dxLight::getLightDirection()
{
	return direction;
}
D3DXVECTOR4 dxLight::getLightAmbient()
{
	return ambient;
}
D3DXVECTOR4 dxLight::getLightMaterials()
{
	return material;
}
D3DXVECTOR4 dxLight::getLightColour()
{
	return colour;
}
D3DXVECTOR3 dxLight::getLightAttenuation()
{
	return attenuation;
}

float dxLight::getLightRange()
{
	return range;
}
#endif