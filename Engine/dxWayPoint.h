#ifndef DXWAYPOINT_H_
#define DXWAYPOINT_H_

#include <d3d10.h>
#include <d3dx10.h>
#include <vector>

class dxWayPoint
{
public:
	D3DXVECTOR3 currentWayPoint;
	D3DXVECTOR3 nextWayPoint;

	D3DXVECTOR3 rootPlayerPosition;
	D3DXVECTOR3 rootPlayerDestination;

	int rootCurrentWayPointNum;

	void setCurrentWaypoint(D3DXVECTOR3 in_waypoint);
	void setNextWaypoint(D3DXVECTOR3 in_waypoint);
	void setPreviousWaypoint(D3DXVECTOR3 in_waypoint);

	D3DXVECTOR3 getCurrentWaypoint();
	D3DXVECTOR3 getNextWaypoint();
	D3DXVECTOR3 getPreviousWaypoint();

private:
};

void dxWayPoint::setCurrentWaypoint(D3DXVECTOR3 in_waypoint)
{
	currentWayPoint = in_waypoint;
}
void dxWayPoint::setNextWaypoint(D3DXVECTOR3 in_waypoint)
{
	nextWayPoint = in_waypoint;
}

D3DXVECTOR3 dxWayPoint::getCurrentWaypoint()
{
	return currentWayPoint;
}

D3DXVECTOR3 dxWayPoint::getNextWaypoint()
{
	return nextWayPoint;
}

#endif