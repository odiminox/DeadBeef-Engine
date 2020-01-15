#ifndef DXBASELIGHT_H_
#define DXBASELIGHT_H_

#include <d3d10.h>
#include <d3dx10.h>

#include "dxGeometry.h"
#include "dxD3D.h"

struct Material
{
	float ambient, diffuse, specular, shininess;
};

struct DirectionalLight
{
	D3DXVECTOR4 color;
	D3DXVECTOR3 position;
};

struct pointLight
{
	D3DXVECTOR3 att;
	float range;
	D3DXVECTOR4 color;
	D3DXVECTOR3 pos;
};

struct spotLight
{
	float  spotPower;
	D3DXVECTOR3 dir;
	D3DXVECTOR3 att;
	float range;
	D3DXVECTOR4 color;
	D3DXVECTOR3 pos;
};

class dxBaseLight:public dxD3D
{
private:
	dxBaseLight* myLight;
public:

	D3DXVECTOR3 mPosition;
	D3DXVECTOR4 mColour;
	D3DXVECTOR3 mDirection;
	D3DXVECTOR4 mMaterial;
	D3DXVECTOR4 mAmbient;
	D3DXVECTOR3 mAttenutation;
	float mRange;
	float mSpotPower;

	DirectionalLight			directionalLight;
	Material					material;
	pointLight                  pointLight;
	spotLight					spotLight;
	D3DXVECTOR4					ambient;

	ID3D10Effect*				pLightEffect;
	ID3D10EffectTechnique*		pLightTechnique;
	ID3D10EffectVariable*		pLightVar;
	ID3D10EffectScalarVariable* pLightType;

	int LightType;

	void loadLight();

	void translate(D3DXVECTOR3 position);
	void setLightColour(D3DXVECTOR4 colour);
	void setLightDirection(D3DXVECTOR3 direction);
	void setMaterials(D3DXVECTOR4 material);
	void setAmbient(D3DXVECTOR4 ambient);
	void setAttenuation(D3DXVECTOR3 attenuation);
	void setSpotPower(float power);
	void setRange(float range);
};

void dxBaseLight::setAttenuation(D3DXVECTOR3 in_attenuation)
{
	spotLight.att = in_attenuation;
	pointLight.att = in_attenuation;
}

void dxBaseLight::setRange(float in_range)
{
	spotLight.range = in_range;
	pointLight.range = in_range;
}

void dxBaseLight::setSpotPower(float in_power)
{
	spotLight.spotPower = in_power;
}

void dxBaseLight::translate(D3DXVECTOR3 in_position)
{
	directionalLight.position = in_position;
	pointLight.pos = in_position;
	spotLight.pos = in_position;
}
void dxBaseLight::setLightColour(D3DXVECTOR4 in_colour)
{
	directionalLight.color = in_colour;
	spotLight.color = in_colour;
	pointLight.color = in_colour;
}
void dxBaseLight::setLightDirection(D3DXVECTOR3 in_direction)
{
	spotLight.dir = in_direction;
}
void dxBaseLight::setMaterials(D3DXVECTOR4 in_material)
{
	material.ambient = in_material.x;
	material.diffuse = in_material.y;
	material.specular = in_material.z;
	material.shininess = in_material.w;
}
void dxBaseLight::setAmbient(D3DXVECTOR4 in_ambient)
{
	ambient = in_ambient;
}

void dxBaseLight::loadLight()
{
	pLightVar = pBasicEffect->GetVariableByName( "pLight" );
	pLightVar->SetRawValue(&pointLight, 0, sizeof(pointLight));

	pLightVar = pBasicEffect->GetVariableByName( "sLight" );
	pLightVar->SetRawValue(&spotLight, 0, sizeof(spotLight));

	pLightVar = pBasicEffect->GetVariableByName( "light" );
	pLightVar->SetRawValue(&directionalLight, 0, sizeof(DirectionalLight));

	pLightVar = pBasicEffect->GetVariableByName( "material" );
	pLightVar->SetRawValue(&mMaterial, 0, sizeof(Material));

	pLightVar = pBasicEffect->GetVariableByName( "ambientLight" );
	pLightVar->SetRawValue( &mAmbient, 0, 16 );

	pLightType = pBasicEffect->GetVariableByName("pLightType")->AsScalar();
	pLightType->SetInt(LightType);
}

#endif