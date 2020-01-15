#include "dxGhostCamera.h"

bool dxGhostCamera::keyHeldA;
bool dxGhostCamera::keyHeldS;
bool dxGhostCamera::keyHeldW;
bool dxGhostCamera::keyHeldD;

void dxGhostCamera::renderGhostCamera(D3DXMATRIX &in_projectionMatrix, D3D10_VIEWPORT &in_viewPort, D3DXMATRIX &in_worldMatrix,
																																						  D3DXMATRIX &in_viewMatrix)
{
	float yaw, pitch, roll;

	D3DXMATRIX yawMatrix;
	D3DXMATRIX pitchMatrix;
	D3DXMATRIX rollMatrix;

	D3DXMATRIX upLocal;
	D3DXVECTOR3 Direction;

	D3DXMATRIX directionMatrix;

	// Set the yaw (Y axis), pitch (X axis), and roll (Z axis) rotations in radians.
	rotation.x = m_rotationX * 0.0174532925f;
	rotation.y   = m_rotationY * 0.0174532925f;
	rotation.z  = m_rotationZ * 0.0174532925f;

	//rotation.x = pitch;
	//rotation.y = yaw;
	//rotation.z = roll;

	up          = D3DXVECTOR3(0.0f, 1.0f, 0.0f);//Create the up vector
	right        = D3DXVECTOR3(1.0f, 0.0f, 0.0f);
	lookat    = D3DXVECTOR3(0.0f, 0.0f, 1.0f);

	//D3DXVECTOR3 inputMoveVec[2] = {position, rotation};

	// Setup matrices to rotate around axes
	D3DXMatrixRotationAxis(&yawMatrix, &up, rotation.y);
	D3DXMatrixRotationAxis(&pitchMatrix, &right, rotation.x);

	//move lookat vector
	D3DXVec3TransformCoord(&lookat, &lookat, &pitchMatrix);
	D3DXVec3TransformCoord(&lookat, &lookat, &yawMatrix);
	D3DXVec3Normalize(&lookat, &lookat);

	//Get the direction vector from camera to target, normalise it.
	//D3DXVec3Normalize(&Direction, &(lookat - right));
	//Get the UP vector (in the world) and determine the cross product, to give us our right (left) hand vector.
	D3DXVec3Cross(&right, &up, &lookat);
	D3DXVec3Normalize(&right, &right);
	//Cross product the right vector and direction vector, to determine up relative to the camera.
	D3DXVec3Cross(&up, &lookat, &right);//Should be direction instead of lookat

	D3DXMatrixIdentity(&in_viewMatrix);

	in_viewMatrix._11 = right.x;
	in_viewMatrix._21 = right.y;
	in_viewMatrix._31 = right.z;

	in_viewMatrix._12 = up.x;
	in_viewMatrix._22 = up.y;
	in_viewMatrix._32 = up.z;

	in_viewMatrix._13 = lookat.x;
	in_viewMatrix._23 = lookat.y;
	in_viewMatrix._33 = lookat.z;

	in_viewMatrix._41 = -D3DXVec3Dot(&(position), &right);
	in_viewMatrix._42 = -D3DXVec3Dot(&(position), &up);
	in_viewMatrix._43 = -D3DXVec3Dot(&(position ), &lookat);

    D3DXMatrixPerspectiveFovLH(&in_projectionMatrix, (float)D3DX_PI * 0.5f,
												 (float)in_viewPort.Width/(float)in_viewPort.Height, 0.1f, 5000.0f);
}

void dxGhostCamera::walkGhostCamera(float d)
{
	direction = atan2((double)lookat.x, (double)lookat.y);
	velocity.x      = (sin(direction));
	velocity.y = 30.0f;
	velocity.z      = (cos(direction ));

	if(keyHeldW == true)
	{
			//position += d*lookat;
		position += lookat * 8.0f;
	}

	if(keyHeldS == true)
	{
		/*velocity.x      = (sin(direction));
		velocity.y = 30.0f;
		velocity.z      = (cos(direction ));*/

		position -= lookat * 8.0f;
	}
	keyHeldW = false;
	keyHeldS = false;
}

void dxGhostCamera::strafeGhostCamera(float d)
{
	if(keyHeldA == true)
	{
		position -= right*8.0f;
	}

	if(keyHeldD == true)
	{
		position += right*8.0f;
	}
	keyHeldA = false;
	keyHeldD = false;
}
void dxGhostCamera::translateGhostCamera(float &in_CameraX, float in_CameraY, float in_CameraZ)
{
	//direction = atan2((double)lookat.x, (double)lookat.z);

	//	velocity.x      = (sin(direction));
	//	velocity.y = 30.0f;
	//	velocity.z      = (cos(direction ));

	position.x = in_CameraX;
	position.y = in_CameraY;
	position.z = in_CameraZ;
}

void dxGhostCamera::rotateGhostCamera(float &in_rotationX, float & in_rotationY, float &in_rotationZ)
{
	m_rotationX = in_rotationX;
	m_rotationY = in_rotationY;
	m_rotationZ = in_rotationZ;
}