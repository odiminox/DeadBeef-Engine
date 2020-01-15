#ifndef DXBASEMODEL_H_
#define DXBASEMODEL_H_

#include <d3d10.h>
#include <d3dx10.h>
#include <vector>

#include "dxD3D.h"
#include "dxGeometry.h"
#include "DX_Mesh_Loader.h"
#include "dxLightManager.h"
#include "dxTextureLoader.h"
#include "IclassBaseManager.h"

class dxBaseModel: public dxD3D, public IclassBaseManager
{
private:
	

public:
	D3DXMATRIX meshWorld;
	D3DXVECTOR3     position;
	D3DXVECTOR3     rotation;

	ID3DX10Mesh*	pMesh;

	bool bumpMap;
	bool specMap;

	int classId;

	dxlightManager myLight;
	dxTextureLoader myTexture;
	DX_Mesh_Loader* pMyMesh;

	D3DXMATRIX posMatrix;
	D3DXMATRIX rotMatrix;

	dxBaseModel();
	~dxBaseModel();
	void translate(D3DXVECTOR3 in_position);
	void rotate(D3DXVECTOR3 in_rotation);
	int classID();
	const char* pGetClassName();
	void addClass();
	//Need to overload this method to accommodate for normal and specular maps
	void loadModel(std::string modelLocation, LPCSTR textureLocation, LPCSTR bumpLocation, LPCSTR specularLocation);
	void render();
};

dxBaseModel::dxBaseModel()/*: position(0.0f,0.0f,0.0f),rotation(0.0f, 0.0f, 0.0f) */
{
	pMyMesh = new DX_Mesh_Loader;
}
dxBaseModel::~dxBaseModel()
{
	if(pMesh){
		pMesh->Release();
		pMesh = 0;
	}
}

void dxBaseModel::translate(D3DXVECTOR3 in_position)
{
	position = in_position;
}

void dxBaseModel::rotate(D3DXVECTOR3 in_rotation)
{
	rotation.x = in_rotation.x;
	rotation.y = in_rotation.y;
	rotation.z = in_rotation.z;
}

int dxBaseModel::classID()
{
	classId = reinterpret_cast<int>(typeid(this).name());
	return classId;
}
const char* dxBaseModel::pGetClassName()
{
	return typeid(this).name();
}

void dxBaseModel::addClass()
{
	classID();
	VecId.push_back(classID());
}

void dxBaseModel::loadModel(std::string modelLocation, LPCSTR textureLocation, LPCSTR bumpLocation, LPCSTR specularLocation)
{
	pMyMesh->Load_Mesh_File(modelLocation);

	if(specularLocation == "" && bumpLocation == "")
	{
		myTexture.loadTexture(textureLocation, pD3DDevice);
		//myTexture.loadTexture(alphaLocation, pD3DDevice);
		specMap = false;
		bumpMap = false;
		//alphaMap = true;
	}


	D3DX10CreateMesh(pD3DDevice, layout2, vertexInputLayoutNumElements2, "POSITION", pMyMesh->Vertices_Count, pMyMesh->Indices_Count/3, D3DX10_MESH_32_BIT, &pMesh);

	pMesh->SetVertexData(0,pMyMesh->VertexArray);
	pMesh->SetIndexData(pMyMesh->IndciesArray, pMyMesh->Indices_Count);
	pMesh->CommitToDevice();

// 	pVar = pBasicEffect->GetVariableByName( "light" );
// 	pVar->SetRawValue(&myLight.directionalLight, 0, sizeof(DirectionalLight));
//
// 	pVar = pBasicEffect->GetVariableByName( "material" );
// 	pVar->SetRawValue(&myLight.material, 0, sizeof(Material));
//
// 	pVar = pBasicEffect->GetVariableByName( "ambientLight" );
// 	pVar->SetRawValue( &myLight.ambientLight, 0, 16 );

	myTexture.pTextureSR			= pBasicEffect->GetVariableByName( "tex2D" )->AsShaderResource();
	myTexture.pBumSR                = pBasicEffect->GetVariableByName( "bump2D" )->AsShaderResource();
	myTexture.pSpecSR               = pBasicEffect->GetVariableByName( "spec2D")->AsShaderResource();
	myTexture.specPowerPtr		    = pBasicEffect->GetVariableByName("specularPower")->AsScalar();
}

void dxBaseModel::render()
{
	D3DXMatrixIdentity(&posMatrix);
	D3DXMatrixIdentity(&rotMatrix);
	D3DXMatrixIdentity(&meshWorld);

	D3DXMatrixRotationYawPitchRoll(&rotMatrix, rotation.y, rotation.x, rotation.z);

	D3DXMatrixTranslation(&posMatrix, position.x, position.y, position.z);

	D3DXMatrixMultiply(&meshWorld, &rotMatrix, &posMatrix);

	//pViewMatrixEffectVariable->SetMatrix(viewMatrix);
	//pProjectionMatrixEffectVariable->SetMatrix(projectionMatrix);

	//WVP = meshWorld*viewMatrix*projectionMatrix;

	//pWVPMatrixEffectVariable->SetMatrix((float*)&WVP);
	//pWorldMatrixEffectVariable->SetMatrix((float*)&meshWorld);

	pWorldMatrixEffectVariable->SetMatrix(meshWorld);
	pViewMatrixEffectVariable->SetMatrix(viewMatrix);
	pProjectionMatrixEffectVariable->SetMatrix(projectionMatrix);

	//mfxWVPVar->SetMatrix((float*)&mWVP);

	if(bumpMap == true && specMap == true){
		myTexture.pTextureSR->SetResource( myTexture.textureSRV[0] );
		myTexture.pBumSR->SetResource(myTexture.textureSRV[1]);
		myTexture.pSpecSR->SetResource(myTexture.textureSRV[2]);
	}  if(bumpMap == false){
		myTexture.pTextureSR->SetResource( myTexture.textureSRV[0] );
		//myTexture.pSpecSR->SetResource(myTexture.textureSRV[2]);
	} else if (specMap == false){
		myTexture.pTextureSR->SetResource( myTexture.textureSRV[0] );
		myTexture.pBumSR->SetResource(myTexture.textureSRV[1]);
	} else if(specMap == false && bumpMap == false)
	{
		myTexture.pTextureSR->SetResource( myTexture.textureSRV[0] );
	} 

// 	myTexture.pTextureSR->SetResource( myTexture.textureSRV[0] );
// 	myTexture.pBumSR->SetResource(myTexture.textureSRV[1]);
// 	myTexture.pSpecSR->SetResource(myTexture.textureSRV[2]);

	D3D10_TECHNIQUE_DESC TechDesc;

	pBasicTechnique->GetDesc(&TechDesc);

	for( UINT p = 0; p < TechDesc.Passes; p++ )
	{
		pBasicTechnique->GetPassByIndex( p )->Apply( 0 );
		pMesh->DrawSubset(0);
	}
}

#endif