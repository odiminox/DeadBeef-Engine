#ifndef DXCAMERAMANAGER_H_
#define DXCAMERAMANAGER_H_

#include "dxFPSCamera.h"
#include "dxGhostCamera.h"
#include "dxOrbitCamera.h"

class dxCameraManager
{
private:
public:

	bool WHeld;
	bool SHeld;
	bool AHeld;
	bool DHeld;

	dxCameraManager();
	~dxCameraManager();

	dxFPSCamera* myFPSCamera;
	dxOrbitCamera* myOrbitCamera;
	dxGhostCamera* myGhostCamera;

	void orthoCamera(D3DXMATRIX &in_projectionMatrix, D3D10_VIEWPORT &in_viewPort);
};

dxCameraManager::dxCameraManager()
{
	myFPSCamera    = new dxFPSCamera;
	myGhostCamera = new dxGhostCamera;
	myOrbitCamera     = new dxOrbitCamera;

	//myFPSCamera->keyHeldW = WHeld;
}

void dxCameraManager::orthoCamera(D3DXMATRIX &in_projectionMatrix, D3D10_VIEWPORT &in_viewPort)
{
	D3DXMatrixOrthoOffCenterLH(&in_projectionMatrix,
		(float)in_viewPort.TopLeftX,
		(float)in_viewPort.Width,
		(float)in_viewPort.TopLeftY,
		(float)in_viewPort.Height,
		0.1f,
		10);
}

#endif