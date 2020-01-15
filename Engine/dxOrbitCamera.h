#ifndef DXORBITCAMERA_H_
#define DXORBITCAMERA_H_

#include <d3d10.h>
#include <d3dx10.h>

class dxOrbitCamera
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

	D3DXMATRIX posMatrix;
	D3DXMATRIX yawMatrix;

	float *inputX;
	float *inputY;

	float speed;

	D3DXVECTOR3 eye;
	D3DXVECTOR3 lookat;
	D3DXVECTOR3 position;      // camera position
	D3DXVECTOR3 rotation;

	//Camera functions
	void renderOrbitCamera(D3DXMATRIX &in_projectionMatrix, D3D10_VIEWPORT &in_viewPort, D3DXMATRIX &in_worldMatrix,
																																						D3DXMATRIX &in_viewMatrix);
	void translateOrbitCamera(float in_CameraX, float in_CameraY, float in_CameraZ);
	void rotateOrbitCamera(float &in_rotationX, float &in_rotationY, float &in_rotationZ);

	D3DXVECTOR3 GetOrbitCameraPosition();
	D3DXVECTOR3 GetOrbitCameraRotation();
};

#endif