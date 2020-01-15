#ifndef DXLIGHTMANAGER_H_
#define DXLIGHTMANAGER_H_

#include <d3d10.h>
#include <d3dx10.h>

#include "dxGeometry.h"

struct DirectionalLight
{
	D3DXVECTOR4 color;
	D3DXVECTOR3 position;
};

struct pointLight
{
	float  spotPower;
	D3DXVECTOR3 dir;
	D3DXVECTOR3 att;
	float range;
	D3DXVECTOR4 color;
	D3DXVECTOR3 pos;
};

struct Material
{
	float ambient, diffuse, specular, shininess;
};

class dxlightManager
{
	private:

	public:

		dxlightManager();

		int LightType;

		D3DXVECTOR4					ambientLight;
		DirectionalLight			directionalLight;
		Material					material;
		pointLight                  pointLight;

		ID3D10Effect*				pLightEffect;
		ID3D10EffectTechnique*		pLightTechnique;
		ID3D10EffectVariable*		pLightVar;
		ID3D10EffectScalarVariable* pLightType;

		//ID3D10Effect*               pLightEffect;

		void setAmbient(float r, float g, float b, float a);
		void createDirectionalLight(float r, float g, float b, float a, float x, float y, float z);
		void materialProperties(float ambient, float diffuse, float specular, float shininess);

		D3DXVECTOR3 getDirection();
};

dxlightManager::dxlightManager()
{
}

void dxlightManager::setAmbient(float r, float g, float b, float a)
{
	ambientLight = D3DXVECTOR4(r, g , b, a);
}

void dxlightManager::createDirectionalLight(float r, float g, float b, float a, float x, float y, float z)
{
	//set directional light - MAKE sure light direction is a unit vector
	directionalLight.color = D3DXVECTOR4(r, g, b, a);
	directionalLight.position = D3DXVECTOR3(x, y, z);

	D3DXVec3Normalize(&directionalLight.position, &directionalLight.position);
}

D3DXVECTOR3 dxlightManager::getDirection()
{
	return directionalLight.position;
}

void dxlightManager::materialProperties(float ambient, float diffuse, float specular, float shininess)
{
	material.ambient = ambient;
	material.diffuse = diffuse;
	material.specular = specular;
	material.shininess = shininess;
}

#endif