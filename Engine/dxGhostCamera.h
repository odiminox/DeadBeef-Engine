#ifndef DXGHOSTCAMERA_H_
#define DXGHOSTCAMERA_H_

#include <d3d10.h>
#include <d3dx10.h>

#include <iostream>
#include <sstream>
#include <string.h>

class dxGhostCamera
{
private:

public:
	float m_fCameraX;
	float m_fCameraY;
	float m_fCameraZ;

	float m_fLookatX;
	float m_fLookatY;
	float m_fLookatZ;

	float m_rotationX;
	float m_rotationY;
	float m_rotationZ;

	D3DXVECTOR3 up;

	D3DXMATRIX yawMatrix;
	D3DXMATRIX pitchMatrix;
	D3DXMATRIX rollMatrix;
	D3DXMATRIX posMatrix;

	float *inputX;
	float *inputY;

	static bool keyHeldW;
	static bool keyHeldS;
	static bool keyHeldA;
	static bool keyHeldD;

	float movemntSpeed;
	float direction;

	std::string m_sPosStats;
	std::string m_sPrevPosStats;

	D3DXVECTOR3 right;
	D3DXVECTOR3 lookat;
	D3DXVECTOR3 position;      // camera position
	D3DXVECTOR3 rotation;

	D3DXVECTOR3 velocity;

	//Camera functions
	void renderGhostCamera(D3DXMATRIX &in_projectionMatrix, D3D10_VIEWPORT &in_viewPort, D3DXMATRIX &in_worldMatrix,
																																						D3DXMATRIX &in_viewMatrix);
	void translateGhostCamera(float &in_CameraX, float in_CameraY, float in_CameraZ);
	void rotateGhostCamera(float &in_rotationX, float &in_rotationY, float &in_rotationZ);

	void walkGhostCamera(float d);
	void strafeGhostCamera(float d);

	D3DXVECTOR3 GetGhostCameraPosition();
	D3DXVECTOR3 GetGhostCameraRotation();
};

#endif