#ifndef DXCOLLISION_H_
#define DXCOLLISION_H_

#include "dxBaseModel.h"
class dxCollision
{
private:
public:
	static D3DXMATRIX Projection;
	static D3DXMATRIX View;
	static D3DXVECTOR3 CameraPos;
	static D3DXVECTOR2 MousePosition;
	static UINT tScreenWidth;
	static UINT tScreenHeight;
	static ID3D10Buffer* PTVB;			//Object collision buffer

	//internal update saves on writing long function data arguments, and screen size changes for view space to ray collision, call once every frame
	void UpdateCollision(float mousePositionX, float mousePositionY, int ScreenWidth, int ScreenHeight, D3DXMATRIX CamProjection, D3DXMATRIX CamView, D3DXVECTOR3 CamPosition){
		Projection = CamProjection;
		View = CamView;
		CameraPos = CamPosition;
		MousePosition.x = mousePositionX;
		MousePosition.y = mousePositionY;
		tScreenWidth = ScreenWidth;
		tScreenHeight = ScreenHeight;
	}

	void initialiseCollision(ID3D10Device *Device)
	{
		//initialise the collision buffer
		D3D10_BUFFER_DESC vbd;
		vbd.Usage = D3D10_USAGE_DYNAMIC;
		vbd.ByteWidth = sizeof(D3DXVECTOR3) * 3;
		vbd.BindFlags = D3D10_BIND_VERTEX_BUFFER;
		vbd.CPUAccessFlags = D3D10_CPU_ACCESS_WRITE;
		vbd.MiscFlags = 0;
		Device->CreateBuffer(&vbd, 0, &PTVB);
	}

	D3DXVECTOR3 Get_Collision_Point(UINT Triangle, dxBaseModel *Mesh, FLOAT BC_U, FLOAT BC_V){
		ID3DX10Mesh* mesh = Mesh->pMesh;

		ID3DX10MeshBuffer* vb = 0;
		ID3DX10MeshBuffer* ib = 0;
		mesh->GetVertexBuffer(0, &vb);
		mesh->GetIndexBuffer(&ib);

		//get the indices of the picked triangle in the object.
		DWORD* indices = 0;
		SIZE_T size;
		ib->Map((void**)&indices, &size);

		DWORD i0 = indices[Triangle*3+0];
		DWORD i1 = indices[Triangle*3+1];
		DWORD i2 = indices[Triangle*3+2];

		ib->Unmap();

		//get the vertices of the picked triangle and copy them into our VB.
		VERTEX* vertices;
		vertices = 0;
		vb->Map((void**)&vertices, &size);

		//picked triangle vertex buffer
		D3DXVECTOR3* TriVerts = 0;
		PTVB->Map(D3D10_MAP_WRITE_DISCARD, 0, (void**)&TriVerts);

		//get the triangle vertex points from the Indices
		TriVerts[0] = vertices[i0].pos;
		TriVerts[1] = vertices[i1].pos;
		TriVerts[2] = vertices[i2].pos;

		//transform the triangle coordinates to the objects world space
		D3DXVec3TransformCoord( &TriVerts[0], &TriVerts[0], &Mesh->meshWorld);
		D3DXVec3TransformCoord( &TriVerts[1], &TriVerts[1], &Mesh->meshWorld);
		D3DXVec3TransformCoord( &TriVerts[2], &TriVerts[2], &Mesh->meshWorld);

		//get the actual point from the transformed vertices and the barycentric coordinates
		D3DXVECTOR3 ReturnPoint;
		D3DXVec3BaryCentric(&ReturnPoint, &TriVerts[0], &TriVerts[1], &TriVerts[2], BC_U, BC_V);

		PTVB->Unmap();
		vb->Unmap();

		vb->Release();
		ib->Release();

		return ReturnPoint;
	}

		/*Single mouse pick on an mesh via bounding box
	  Cheap collision detection based off a meshes bounding box
	  This function only returns if an mesh has been picked
	  with the mouse*/
	int Mouse_Pick_Mesh(dxBaseModel *Mesh, D3DXVECTOR3 &OutPutV3){
		D3DXMATRIX P = Projection;
		D3DXMATRIX V = View;

		//Compute picking ray in view space.
// 		FLOAT vx = (+2.0f*MousePosition.x/tScreenWidth  - 1.0f)/P(0,0);
// 		FLOAT vy = (-2.0f*MousePosition.y/tScreenHeight + 1.0f)/P(1,1);
		FLOAT vx = (+2.0f*MousePosition.x/tScreenWidth  - 1.0f)/P(0,0);
		FLOAT vy = (-2.0f*MousePosition.y/tScreenHeight + 1.0f)/P(1,1);

		D3DXVECTOR3 rayOrigin(0.0f, 0.0f, 0.0f);
		D3DXVECTOR3 rayDir(vx, vy, 1.0f);

		//Transform the pick via inversion.
		D3DXMATRIX inverseV;
		D3DXMatrixInverse(&inverseV, 0, &V);

		D3DXVec3TransformCoord(&rayOrigin, &rayOrigin, &inverseV);
		D3DXVec3TransformNormal(&rayDir, &rayDir, &inverseV);

		//Transform to the mesh's local space.
		D3DXMATRIX inverseW;
		D3DXMatrixInverse(&inverseW, 0, &Mesh->meshWorld);

		D3DXVec3TransformCoord(&rayOrigin, &rayOrigin, &inverseW);
		D3DXVec3TransformNormal(&rayDir, &rayDir, &inverseW);

// 		//collision check and increment the total hits, store the hit distance and object hit if there is one
// 		if (D3DXBoxBoundProbe (&Mesh->Get_BB_Min(), &Mesh->Get_BB_Max(), &rayOrigin, &rayDir) == TRUE){
// 			return 1;
// 		}
		ID3DX10Mesh* d3dxmesh = Mesh->pMesh;
		UINT PickedTriangle;
		UINT hitCount;
		float u,v,t;
		ID3D10Blob* allHits;
		d3dxmesh->Intersect(&rayOrigin, &rayDir, &hitCount, &PickedTriangle, &u, &v, &t, &allHits);
		//allHits->Release();
		if (hitCount > 0){
			//return the vector point function of a collision hit
			OutPutV3 = Get_Collision_Point(PickedTriangle, Mesh, u, v);
			return 1;
		}
		return -1;
	}
};
D3DXMATRIX dxCollision::Projection;
D3DXMATRIX dxCollision::View;
D3DXVECTOR3 dxCollision::CameraPos;
D3DXVECTOR2 dxCollision::MousePosition;
UINT dxCollision::tScreenWidth;
UINT dxCollision::tScreenHeight;
ID3D10Buffer* dxCollision::PTVB;		
#endif