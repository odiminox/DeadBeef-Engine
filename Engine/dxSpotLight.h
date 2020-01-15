#ifndef DXSPOTLIGHT_H_
#define DXSPOTLIGHT_H_

struct spotLight
{
	float  spotPower;
	D3DXVECTOR3 dir;
	D3DXVECTOR3 att;
	float range;
	D3DXVECTOR4 color;
	D3DXVECTOR3 pos;
};

class dxSpotLight
{
public:
};

#endif