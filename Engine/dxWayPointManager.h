#ifndef DXWAYPOINTMANAGER_H_
#define DXWAYPOINTMANAGER_H_

#include "dxWayPoint.h"
#include "dxMartinMath.h"

class dxWayPointManager
{
public:
	dxWayPointManager();

	std::vector<dxWayPoint*> m_wayPoints;

	D3DXVECTOR3 playerPosition;
	D3DXVECTOR3 playerRotation;
	D3DXVECTOR3 playerRotDest;
	D3DXVECTOR3 playerDestination;

	void createNextWayPoint(D3DXVECTOR3 wayPoint);
	void createCurrentWayPoint(D3DXVECTOR3 wayPoint);
	void createWayPoints(int numWayPoints);
	void setWayPoint(int wayPointNum);
	void SetPathNode(UINT Value);
	void generateRandomWayPoint(D3DXVECTOR3 wayPoint);

	D3DXVECTOR3 getPreviousWayPoint();
	D3DXVECTOR3 getCurrentWayPoint();
	D3DXVECTOR3 getNextWayPoint();
	D3DXVECTOR3 getPlayerRotation();
	D3DXVECTOR3 getPlayerPosition();
	D3DXVECTOR3 iterate;
	D3DXVECTOR3 startPosition;
	float iterateX;
	float iterateY;
	float iterateZ;
	float iterateAmountX;
	float iterateAmountY;
	float iterateAmountZ;
	float velocity;
	float deltaTime;
	float deltaWait;
	float finalVelocity;
	bool active;
	float angleSeed;

	void updateWayPoints();
	void updateWayPoints2();
	int currentWayPointNum;

private:
	dxWayPoint* nextWayPoint;
};

dxWayPointManager::dxWayPointManager()
{
	finalVelocity = 0.0f;
	iterateAmountX = 0.0f;
	iterateX = 0.0f;
	iterateY = 0.0f;
	iterateZ = 0.0f;
	velocity = 0.0f;
	deltaTime = 0.0f;
	deltaWait = 0.0f;
	angleSeed = 90.0f;
	active = false;
}

D3DXVECTOR3 dxWayPointManager::getCurrentWayPoint()
{
	return m_wayPoints[currentWayPointNum]->getCurrentWaypoint();
}

D3DXVECTOR3 dxWayPointManager::getNextWayPoint()
{
	return m_wayPoints[currentWayPointNum]->getNextWaypoint();
}

void dxWayPointManager::createWayPoints(int numWayPoints)
{
	for(int i = 0; i < numWayPoints; i++)
	{
		m_wayPoints.push_back(nextWayPoint = new dxWayPoint);
	}
}

void dxWayPointManager::updateWayPoints()
{
	if(active == false){
		//Check if it's the first time running.
		if(currentWayPointNum == 0)
		{
			//Same for initial position
			m_wayPoints[0]->setCurrentWaypoint(D3DXVECTOR3(0.0f, 0.0f, -1.0f));
			m_wayPoints[1]->setCurrentWaypoint(D3DXVECTOR3(0.0f, 0.0f, 150.0f));
			//Because it's our first time(be gentle) set up destination
			iterateX += iterateAmountX;
			iterateY += iterateAmountY;
			iterateZ += iterateAmountZ;
			createNextWayPoint(D3DXVECTOR3(iterateX, iterateY, iterateZ));

			playerPosition    = m_wayPoints[0]->getCurrentWaypoint();
			playerDestination = m_wayPoints[1]->getCurrentWaypoint();
			//playerRotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			//playerRotation = m_wayPoints[currentWayPointNum + 1]->getCurrentWaypoint();

			active = true;
		}
	}

	if(active == true)
	{
		float temp = velocity;
		finalVelocity = temp;
		//finalVelocity = velocity;
		playerPosition = Calculate_Position(playerPosition, playerDestination, finalVelocity);

		if(Distance(playerPosition, playerDestination) <= 0.1f)//This is where the error is
		{
			currentWayPointNum++;
			if(currentWayPointNum == m_wayPoints.size() - 1)
			{
				active = false;
			} else{
				iterateX += iterateAmountX;
				iterateY += iterateAmountY;
				iterateZ += iterateAmountZ;
				createNextWayPoint(D3DXVECTOR3(iterateX, iterateY, iterateZ));

				playerPosition    = m_wayPoints[currentWayPointNum]->getCurrentWaypoint();
				playerDestination = m_wayPoints[currentWayPointNum + 1]->getCurrentWaypoint();

				//playerRotation = Calculate_Position(playerRotation, playerDestination, temp);
				//playerRotation = m_wayPoints[currentWayPointNum + 1]->getCurrentWaypoint();

				//playerRotation = m_wayPoints[currentWayPointNum + 1]->getCurrentWaypoint();
		}
		}
	}
}

void dxWayPointManager::createNextWayPoint(D3DXVECTOR3 wayPoint)
{
	m_wayPoints[currentWayPointNum + 1]->setCurrentWaypoint(wayPoint);
}

D3DXVECTOR3 dxWayPointManager::getPlayerPosition()
{
	return playerPosition;
}

D3DXVECTOR3 dxWayPointManager::getPlayerRotation()
{
	return playerRotation;
}

#endif