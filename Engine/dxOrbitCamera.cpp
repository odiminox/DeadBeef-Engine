#include "dxOrbitCamera.h"

void dxOrbitCamera::renderOrbitCamera(D3DXMATRIX &in_projectionMatrix, D3D10_VIEWPORT &in_viewPort, D3DXMATRIX &in_worldMatrix,
																																						  D3DXMATRIX &in_viewMatrix)
{
	float yaw, pitch, roll;
	D3DXMATRIX rotationMatrix;
	D3DXVECTOR3 Direction;
	D3DXMATRIX matRotAxis,matRotZ;
	D3DXVECTOR3 RotAxis;
	// Set the yaw (Y axis), pitch (X axis), and roll (Z axis) rotations in radians.
	pitch = m_rotationX * 0.0174532925f;
	yaw   = m_rotationY * 0.0174532925f;
	roll  = m_rotationZ * 0.0174532925f;

	up          = D3DXVECTOR3(0.0f, 1.0f, 0.0f);//Create the up vector
	//Build eye ,lookat and rotation vectors from player input data
	eye        = D3DXVECTOR3(m_fCameraX, m_fCameraY, m_fCameraZ);
	lookat    = D3DXVECTOR3(m_fLookatX, m_fLookatY, m_fLookatZ);
	rotation = D3DXVECTOR3(m_rotationX, m_rotationY, m_rotationZ);

	D3DXVECTOR3 camera[3] = {	eye,//Eye
															lookat,//LookAt
															up };//Up
	RotAxis.x = pitch;
	RotAxis.y = yaw;
	RotAxis.z = roll;

	D3DXVECTOR3 up2;
    D3DXVECTOR3 right;

	D3DXVec3Normalize(&Direction, &(camera[1] - camera[0]));//Direction vector

	//Use the lookat vector to determine our right vector
	D3DXVec3Cross(&right, &up, &lookat);//right vector
	D3DXVec3Normalize(&right, &right);

	//D3DXVec3Cross(&RotAxis, &Direction, &camera[2]);//Strafe vector
	//D3DXVec3Normalize(&RotAxis, &RotAxis);

	// Create the rotation matrix from the yaw, pitch, and roll values.
	D3DXMatrixRotationYawPitchRoll(&matRotAxis, pitch,yaw, roll);

	//rotate direction
	D3DXVec3TransformCoord(&Direction,&Direction,&matRotAxis);
	//Translate up vector
	D3DXVec3TransformCoord(&camera[2], &camera[2], &matRotAxis);

	 //Translate in the direction of player rotation
	D3DXVec3TransformCoord(&camera[0], &camera[0], &matRotAxis);

	camera[1] = Direction + camera[0];//Avoid gimble locking

	D3DXMatrixLookAtLH(&in_viewMatrix, &camera[0], &camera[1], &camera[2]);

    D3DXMatrixPerspectiveFovLH(&in_projectionMatrix, (float)D3DX_PI * 0.5f,
												 (float)in_viewPort.Width/(float)in_viewPort.Height, 0.1f, 5000.0f);
}

void dxOrbitCamera::translateOrbitCamera(float in_CameraX, float in_CameraY, float in_CameraZ)
{
	m_fCameraX = in_CameraX;
	m_fCameraY = in_CameraY;
	m_fCameraZ = in_CameraZ;
}

void dxOrbitCamera::rotateOrbitCamera(float &in_rotationX, float & in_rotationY, float &in_rotationZ)
{
	m_rotationX = in_rotationX;
	m_rotationY = in_rotationY;
	m_rotationZ = in_rotationZ;
}