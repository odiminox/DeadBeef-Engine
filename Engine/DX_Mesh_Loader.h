#ifndef _DX_MESH_LOADER_H_MR
#define _DX_MESH_LOADER_H_MR
//--------------------------------------------------------------------------------------
// Martin Radomski 601492, Simon Jordan 498992, copyright © 2011
// Filename: DX_Mesh_Loader.h
/*
	The DX_Mesh_Loader class is based on reusable code that can be implemented with any DX10
	application. This class provides functions that allow the developer to Load .OBJ model
	formats types to their DX10 development project. (additionally this class should be
	developed to hold many other mesh formats)

	Current Types Supported:
	1) 3ds Max Wavefront OBJ Exporter v0.97b (3ds Max 2010/2012), models must be exported
	with the following settings:
			FlipYZ axis unchecked
			Faces set to triangles
			Export Texture Coordinates checked
			Optimized Texture Coordinates checked
			Scale 1.0
			All other Settings unchecked
	*NOTE
	For UV mapped meshes that contain un-welded or duplicate vertices's the exported UV image
	to be used on the mesh requires to be inverted for the correct orientation of text.

	UV Mapped meshes with all vertices's welded such as using the unfold feature within max
	do not require to be inverted.

	//TODO
	Currently the model loader requires the removal of duplicate elements and the indices list
	requires an update to and changes on removing duplicate elements.

	Simon added the tangent calculations
*/
//--------------------------------------------------------------------------------------

//INCLUDES------------------------------------------------------------------------------
#include <d3d10.h>
#include <d3dx10.h>
#include <iostream>
#include <xnamath.h>
#include <fstream>
#include <vector>
#include <string>

#include "dxGeometry.h"

//--------------------------------------------------------------------------------------
class DX_Mesh_Loader
{
private:

public:

	//VARIABLES
	//Our final Dynamic arrays of data, used in the D3D10 mesh creation process.
	VERTEX *VertexArray;								//The Meshes vertex array
	DWORD  *IndciesArray;								//The Meshes Indices array

	std::string meshStats;

	int meshTriangles;

	//data description
	UINT Vertices_Count;
	UINT Indices_Count;

	//CONSTRUCTOR
	DX_Mesh_Loader(){
		//Initialise Variables
		Vertices_Count = 0;
		Indices_Count = 0;
	};
	//

	//DESTRUCTOR
	virtual~DX_Mesh_Loader(){
		//Clean up
	};
	//

	//load the mesh object, requires a constant char OBJ file location

HRESULT Load_Mesh_File(std::string FileLocation){
		std::ifstream MeshFile (FileLocation.c_str(), std::fstream::in); //Open the file

		//try to open the file
		while(!MeshFile.is_open()){
			MeshFile.open(FileLocation.c_str()); //retry the file
			if (!MeshFile.good()){
				std::string ErrorStr = "The Model : " + FileLocation + " cant be found at the location.";
				MessageBox(NULL, ErrorStr.c_str(), "Error in loading Model File", MB_OK ); //needs to contain the model name
				return S_FALSE;					//ok open file failed
			}
		}

		//Temporary vectors to hold the incoming file data.
		std::vector <D3DXVECTOR3> Mesh_Verts;				//Vertices's
		std::vector <D3DXVECTOR3> Mesh_Normals;				//Normals
		std::vector <D3DXVECTOR2> Mesh_Coords;				//Texture Coordinates

		//Temp vector arrays of our structure VERTEX and a DWORD used for indices.
		std::vector <VERTEX> Mesh_Elements;					//The Elements in the mesh (D3DXVECTOR3, D3DXVECTOR3, D3DXVECTOR2)
		std::vector <DWORD> Mesh_Indices;					//The Indices

		//Temporary character buffer for reading the data from file
		char buffer[256] = {0};

		//all good lets get on and load the data
		if(MeshFile.good()){
			for (;;){
				//temporary variables
				D3DXVECTOR3 Temp_Position;
				D3DXVECTOR3 Temp_Normal;
				D3DXVECTOR2 Temp_Coord;

				MeshFile >> buffer;

				if(!MeshFile){ break;}

				//vertex positions
				if(0 == strcmp(buffer, "v")){
					MeshFile >> Temp_Position.x >> Temp_Position.y >> Temp_Position.z;
					Mesh_Verts.push_back(Temp_Position);
				}

				//vertex normals
				if(0 == strcmp(buffer, "vn")){
					MeshFile >> Temp_Normal.x >> Temp_Normal.y >> Temp_Normal.z;
					Mesh_Normals.push_back(Temp_Normal);
				}

				//texture coordinates
				if(0 == strcmp(buffer, "vt")){
					MeshFile >> Temp_Coord.x >> Temp_Coord.y;
					Mesh_Coords.push_back(Temp_Coord);
				}

				//faces
				if(0 == strcmp(buffer,"f")){
					UINT Position, Normal, TexCoord;
					VERTEX vertex;

					for(int i=0; i<3; i++){
						ZeroMemory(&vertex, sizeof(VERTEX));

						MeshFile >> Position;
						vertex.pos = Mesh_Verts[Position - 1];
						Mesh_Indices.push_back(Position -1);

						if('/'==MeshFile.peek()){
							MeshFile.ignore();

							if('/'!=MeshFile.peek()){
								MeshFile >> TexCoord;
								vertex.Tex = Mesh_Coords[TexCoord - 1];
							}
						}

						if('/'==MeshFile.peek()){
							MeshFile.ignore();

							if('/'!=MeshFile.peek()){
								MeshFile >> Normal;
								vertex.Norm = Mesh_Normals[Normal - 1];
							}
						}

						Mesh_Elements.push_back(vertex);
					}
					meshTriangles++;
				}
			}

			//all done here lets close the file up
			MeshFile.close();

			//check for duplicate elements and remove them \\TODO

			//lets set some model requirements up
			Vertices_Count = Mesh_Elements.size();
			Indices_Count = Mesh_Indices.size();

			VertexArray = new VERTEX [Mesh_Elements.size()];

			IndciesArray = new DWORD [Mesh_Indices.size()];

			for (UINT Count = 0; Count < Mesh_Elements.size(); Count++){
				VertexArray[Count] = Mesh_Elements[Count];
			}

			for (UINT Count = 0; Count < Mesh_Indices.size(); Count++){
				IndciesArray[Count] = Count; //Mesh_Indices[Count];
			}

			//everything is ok
			return S_OK;
		}else{
			std::string ErrorStr = "A error occurred while accessing Model : " + FileLocation;
			MessageBox(NULL, ErrorStr.c_str(), "Error in loading Model File", MB_OK );
			return S_FALSE; //file is in use !
		}
	}
};
//--------------------------------------------------------------------------------------
#endif