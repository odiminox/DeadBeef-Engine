#pragma once
#include <iostream>
#include <windows.h>
#include <WindowsX.h>
#include <D3D10.h>
#include <D3DX10.h>
#include <stdio.h>
#include <fstream>
#include <vector>
#include <sstream>
#include <string.h>

#include "dxGeometry.h"

using namespace std;
/**************************************************************************************
* meshImporter.h
* Simon GL Jordan 498992/Martin Radomski

* Description:
* Reads .obj file data: Vertices's, Normals, Texture coordinates, faces in correct order
*
* Use:
* Data collected from .obj file can be read from vectors
***************************************************************************************/

class dxMeshLoader
{
private:

	fstream modelFile;

public:
	dxMeshLoader(void);
	~dxMeshLoader(void);
	int loadModel(std::string fileName);
	void calculateTangentBinormal(D3DXVECTOR3 dxvertex1, D3DXVECTOR3 dxvertex2, D3DXVECTOR3 dxvertex3,
								  D3DXVECTOR3& CrossTangent, D3DXVECTOR3& CrossBinormal);

	//Temporary vectors to hold the incoming file data.
	std::vector <D3DXVECTOR3> vertVect;
	std::vector <D3DXVECTOR2> textureVect;
	std::vector <D3DXVECTOR3> normalVect;

	std::string meshStats;
	std::string nameStats;
	std::string	vertStats;

	VERTEX* vertexArray;
	DWORD* indicesArray;

	//data description
	UINT Vertices_Count;
	UINT Indices_Count;

	//Temp vector arrays of our structure VERTEX and a DWORD used for indices.
	std::vector <VERTEX> meshElements;					//The Elements in the mesh (D3DXVECTOR3, D3DXVECTOR2 D3DXVECTOR3)
	std::vector <DWORD> meshIndices;					//The Indices
};

void dxMeshLoader::calculateTangentBinormal(D3DXVECTOR3 dxvertex1,     D3DXVECTOR3 dxvertex2,     D3DXVECTOR3 dxvertex3,
											D3DXVECTOR3& CrossTangent, D3DXVECTOR3& CrossBinormal){
	D3DXVECTOR3 dxvector1, dxvector2;
	D3DXVECTOR2 dxtuvector, dxtvvector;
	D3DXVECTOR2 dxtexvertex1, dxtexvertex2, dxtexvertex3;

	D3DXVECTOR3 CrossTangent;
	D3DXVECTOR3 CrossBinormal;
	float dxlength;

	/*float vector1[3], vector2[3];
	float tuVector[2], tvVector[2];
	float den;
	float length;*/

	float den;

	// Calculate the two vectors for this face.
	dxvector1 = dxvertex2 - dxvertex1;
	dxvector2 = dxvertex3 - dxvertex1;

	// Calculate the tu and tv texture space vectors.
	D3DXVECTOR3(dxtuvector) = dxvertex2 - dxvertex1;
	D3DXVECTOR3(dxtvvector) = dxvertex3 - dxvertex1;

	// Calculate the denominator of the tangent/binormal equation.
	den = (1.0f / dxtuvector.x * dxtvvector.y - dxtuvector.y * dxtvvector.x);

	// Calculate the cross products and multiply by the coefficient to get the tangent and binormal.
	D3DXVec3Cross(&CrossTangent, &D3DXVECTOR3(D3DXVECTOR3(dxtvvector) * dxvector1), &D3DXVECTOR3(dxtvvector * dxvector2) );

	CrossTangent * den;

	//tangent.x = (tvVector[1] * vector1[0] - tvVector[0] * vector2[0]) * den;
	//tangent.y = (tvVector[1] * vector1[1] - tvVector[0] * vector2[1]) * den;
	//tangent.z = (tvVector[1] * vector1[2] - tvVector[0] * vector2[2]) * den;

	D3DXVec3Cross(&CrossBinormal, &D3DXVECTOR3(dxtuvector.x * dxvector2), &D3DXVECTOR3(dxtuvector.y * dxvector1) );

	CrossBinormal * den;

	//binormal.x = (tuVector[0] * vector2[0] - tuVector[1] * vector1[0]) * den;
	//binormal.y = (tuVector[0] * vector2[1] - tuVector[1] * vector1[1]) * den;
	//binormal.z = (tuVector[0] * vector2[2] - tuVector[1] * vector1[2]) * den;

	// Calculate the length of this normal.
	//D3DXVec3Normalize(&dxlength, &CrossTangent);
	dxlength = D3DXVec3Length(&CrossTangent);
	//dxlength
	//length = sqrt((tangent.x * tangent.x) + (tangent.y * tangent.y) + (tangent.z * tangent.z));

	// Normalize the normal and then store it
	CrossTangent = CrossTangent / dxlength;

	/*tangent.x = tangent.x / length;
	tangent.y = tangent.y / length;
	tangent.z = tangent.z / length;*/

	// Calculate the length of this normal.
	dxlength = D3DXVec3Length(&CrossBinormal);
	//D3DXVec3Normalize(&dxlength, &CrossBinormal);

	//length = sqrt((binormal.x * binormal.x) + (binormal.y * binormal.y) + (binormal.z * binormal.z));

	// Normalize the normal and then store it
	CrossBinormal = CrossBinormal / dxlength;
	//binormal.x = binormal.x / length;
	//binormal.y = binormal.y / length;
	//binormal.z = binormal.z / length;

	return;
}

dxMeshLoader::dxMeshLoader(void): Vertices_Count(0),
	Indices_Count(0)
{}

dxMeshLoader::~dxMeshLoader(void)
{
}

int dxMeshLoader::loadModel(std::string fileName)
{
	modelFile.open(fileName, fstream::in);
	while(!modelFile.is_open()){
		modelFile.open(fileName.c_str()); //retry the file
		if (!modelFile.good()){
			std::string ErrorStr = "The Model could not be found at the location.";
			MessageBox(NULL, ErrorStr.c_str(), "Error in loading Model File", MB_OK );
			return S_FALSE;					//ok open file failed
		}
	}

	//Temporary character buffer for reading the data from file
	char buffer[256] = {0};

	//all good lets get on and load the data
	if(modelFile.good()){
		for (;;){
			//temporary variables
			D3DXVECTOR3 Temp_Position;
			D3DXVECTOR2 Temp_Tex;
			D3DXVECTOR3 Temp_Normal;

			modelFile >> buffer;
			if(!modelFile){ break;}

			//vertex positions
			if(0 == strcmp(buffer, "v")){
				modelFile >> Temp_Position.x >> Temp_Position.y >> Temp_Position.z;
				vertVect.push_back(Temp_Position);
			}

			//Normal coordinates
			if(0 == strcmp(buffer, "vn")){
				modelFile >> Temp_Normal.x >> Temp_Normal.y >> Temp_Normal.z;
				normalVect.push_back(Temp_Normal);
			}

			//texture coordinates
			if(0 == strcmp(buffer, "vt")){
				modelFile >> Temp_Tex.x >> Temp_Tex.y;
				textureVect.push_back(Temp_Tex);
			}

			//faces
			if(0==strcmp(buffer,"f")){
				UINT Position, TexCoord, Normal;
				VERTEX vertex1;

				for(int i=0; i<3; i++){
					ZeroMemory(&vertex1, sizeof(VERTEX));

					modelFile >> Position;
					vertex1.pos = vertVect[Position - 1];
					meshIndices.push_back(Position -1);

					if('/'==modelFile.peek()){
						modelFile.ignore();

						if('/'!=modelFile.peek()){
							modelFile >> TexCoord;
							vertex1.Tex = textureVect[TexCoord - 1];
						}
					}

					if('/'==modelFile.peek()){
						modelFile.ignore();

						if('/'!=modelFile.peek()){
							modelFile >> Normal;
							vertex1.Norm = normalVect[Normal - 1];
						}
					}

					meshElements.push_back(vertex1);
				}
			}
		}

		ostringstream meshOut;
		meshOut.precision(4);
		meshOut << "\n\n\nvertVect.size(): " << vertVect.size()
			<< "\ntextureVect.size(): " << textureVect.size()
			<< "\nnormalVect.size(): "	  << normalVect.size()
			<< "\nmeshElements.size(): "    << meshElements.size()
			<< "\nmeshIndices.size(): "     << meshIndices.size();

		//all done here lets close the file up
		modelFile.close();

		//lets set some model requirements up
		Vertices_Count = meshElements.size();
		Indices_Count = meshIndices.size();

		vertexArray = new VERTEX [meshElements.size()];

		indicesArray = new DWORD [meshIndices.size()];

		for (UINT Count = 0; Count < meshElements.size(); Count++){
			vertexArray[Count] = meshElements[Count];
		}

		for (UINT Count = 0; Count < meshIndices.size(); Count++){
			indicesArray[Count] = Count;
		}

		ostringstream nameOut;
		nameOut.precision(10);
		nameOut << "\nModel name: " << fileName
				<< "\nvertexArray: "      << vertexArray
				<< "\nindicesArray: "     << indicesArray
				<< "\nIndices_Count: "    << Indices_Count
				<< "\nVertices_Count: "   << Vertices_Count
				<< "\nFaces: " << Indices_Count / 3;

		nameStats = nameOut.str();

		return S_OK;
	}else{
		std::string ErrorStr = "A error occurred while accessing Model";
		MessageBox(NULL, ErrorStr.c_str(), "Error in loading Model File", MB_OK );
		return S_FALSE; //file is in use !
	}
}