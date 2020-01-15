/**************************************************************************************
* Files to contain vertex information.
* This file will have to be adapted into a class and changed depending on the projects
* requirements
*
***************************************************************************************/
#ifndef GEOM_H
#define GEOM_H

const D3DXCOLOR WHITE(1.0f, 1.0f, 1.0f, 1.0f);
const D3DXCOLOR BLACK(0.0f, 0.0f, 0.0f, 1.0f);
const D3DXCOLOR RED(1.0f, 0.0f, 0.0f, 1.0f);
const D3DXCOLOR GREEN(0.0f, 1.0f, 0.0f, 1.0f);
const D3DXCOLOR BLUE(0.0f, 0.0f, 1.0f, 1.0f);
const D3DXCOLOR YELLOW(1.0f, 1.0f, 0.0f, 1.0f);
const D3DXCOLOR CYAN(0.0f, 1.0f, 1.0f, 1.0f);
const D3DXCOLOR MAGENTA(1.0f, 0.0f, 1.0f, 1.0f);

//The Vertex format structure used to pass the data into final buffer array.
struct VERTEX{
	VERTEX()
	{
		ZeroMemory(this, sizeof(VERTEX));
	}

	D3DXVECTOR3 pos; //the position
	D3DXVECTOR3 Norm;	  //the normals
	D3DXVECTOR2 Tex; //the texture coords
	//D3DXVECTOR3 tangent;
};

struct meshInstance
{
	D3DXVECTOR3     position;
	D3DXVECTOR3     rotation;
	std::string		modelLocation;
	LPCSTR			textureLocation;
} instancedMesh;

std::vector<meshInstance*> worldMeshes;

const D3D10_INPUT_ELEMENT_DESC layout[] =
{
	{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D10_INPUT_PER_VERTEX_DATA, 0 },
	{ "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D10_INPUT_PER_VERTEX_DATA, 0 },
	{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 24, D3D10_INPUT_PER_VERTEX_DATA, 0 },
	{ "TANGENT", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 36, D3D10_INPUT_PER_VERTEX_DATA, 0 }
};

const D3D10_INPUT_ELEMENT_DESC layout2[] =
{
	{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D10_INPUT_PER_VERTEX_DATA, 0 },
	{ "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D10_INPUT_PER_VERTEX_DATA, 0 },
	{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 24, D3D10_INPUT_PER_VERTEX_DATA, 0 }
};

const D3D10_INPUT_ELEMENT_DESC layout3[] =
{
	{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D10_INPUT_PER_VERTEX_DATA, 0 },
	{ "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D10_INPUT_PER_VERTEX_DATA, 0 }
};

//const D3D10_INPUT_ELEMENT_DESC layout4[] =
//{
//	{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D10_INPUT_PER_VERTEX_DATA, 0 },
//	{ "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D10_INPUT_PER_VERTEX_DATA, 0 },
//	{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 24, D3D10_INPUT_PER_VERTEX_DATA, 0 },
//	{ "TANGENT", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 36, D3D10_INPUT_PER_VERTEX_DATA, 0 },
//	{ "BINORMAL", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 48, D3D10_INPUT_PER_VERTEX_DATA, 0 }
//};

const int vertexInputLayoutNumElements = sizeof(layout)/sizeof(layout[0]);
const int vertexInputLayoutNumElements2 = sizeof(layout2)/sizeof(layout2[0]);
const int vertexInputLayoutNumElements3 = sizeof(layout3)/sizeof(layout3[0]);
//const int vertexInputLayoutNumElements4 = sizeof(layout4)/sizeof(layout4[0]);

#endif