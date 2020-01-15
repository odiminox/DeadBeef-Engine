/**************************************************************************************
* gameTimer.h
* Simon GL Jordan 498992

* Description:
* Controls the use of time and calculates current, prev and paused times.
* adapted from Frank.D.Luna's Introduction to 3D Game Programming with DirectX 10
*
* Use:
*
***************************************************************************************/
class gameTimer
{
public:
	gameTimer();

	float getGameTime()const; //in seconds
	float getDeltaTime()const; //in seconds

	void reset(); //call before message loop
	void start(); //call when unpaused
	void stop();  //call when paused
	void tick();  //call every frame

private:
	double mSecondsPerCount;
	double mDeltaTime;

	_int64 mBaseTime;
	_int64 mPausedTime;
	_int64 mStopTime;
	_int64 mPrevTime;
	_int64 mCurrTime;

	bool mStopped;
};
//Constructor queries the frequency of the performance counter.
gameTimer::gameTimer():mSecondsPerCount(0.0), mDeltaTime(-1.0), mBaseTime(0),
					  mPausedTime(0), mPrevTime(0), mCurrTime(0), mStopped(false)
{
	_int64 countsPerSec;
	QueryPerformanceFrequency((LARGE_INTEGER*)&countsPerSec);
	mSecondsPerCount = 1.0 / (double)countsPerSec;
}

void gameTimer::tick()
{
	if(mStopped)
	{
		mDeltaTime = 0.0;
		return;
	}

	//get the time this frame
	_int64 currTime;
	QueryPerformanceCounter((LARGE_INTEGER*)&currTime);
	mCurrTime = currTime;

	//time difference between this frame and the previous
	mDeltaTime = (mCurrTime - mPrevTime)*mSecondsPerCount;

	//prepare for next frame
	mPrevTime = mCurrTime;

	//for nonnegative. the DXDSDK's CDUXUTTimer mentions that if the
	//processor goes into power save mode we get shuffled to another
	//processor, then mDeltaTime can be negative.
	if(mDeltaTime < 0.0)
	{
		mDeltaTime = 0.0;
	}
}

float gameTimer::getDeltaTime()const
{
	return (float)mDeltaTime;
}

void gameTimer::reset()
{
	_int64 currTime;
	QueryPerformanceCounter((LARGE_INTEGER*)&currTime);

	mBaseTime = currTime;
	mPrevTime = currTime;
	mStopTime = 0;
	mStopped  = false;
}

void gameTimer::stop()
{
	//if we are already stopped, then don't do anything
	if(!mStopped)
	{
		_int64 currTime;
		QueryPerformanceCounter((LARGE_INTEGER*)&currTime);

		//otherwise, save the time we stopped at, and set
		//the boolean flag indicating the timer is stopped.
		mStopTime = currTime;
		mStopped  = true;
	}
}

void gameTimer::start()
{
	_int64 startTime;
	QueryPerformanceCounter((LARGE_INTEGER*)&startTime);

	//Accumulate the time elapsed between stop and start pairs

	//
	//				  |<-------d------->|
	// ---------------*-----------------*------------> time
	//           mStopTime            startTime

	//if we resume the timer from a stopped state...
	if(mStopped)
	{
		//then accumulate the paused time
		mPausedTime += (startTime - mStopTime);

		//since we are starting the timer back up, the current
		//previous time is not valid, as it occurred while paused.
		//so reset it to the current time.
		mPrevTime = startTime;

		//no longer stopped...
		mStopTime = 0;
		mStopped  = false;
	}
}

float gameTimer::getGameTime()const
{
	// If we are stopped, do not count the time that has passed since
	// we stopped.
	//
	// ----*---------------*------------------------------*------> time
	// mBaseTime		mStopTime					  mCurrTime

	if(mStopped)
	{
		return (float)((mStopTime - mBaseTime))*mSecondsPerCount;

		// The distance mCurrTime - mBaseTime includes paused time,
		// which we do not want to count. To correct this, we can subtract
		// the paused time from mCurrTime:
		//
		// (mCurrTime - mPausedTime) - mBaseTime
		//
		//                     |<-------d------->|
		// ----*---------------*-----------------*------------*------> time
		// mBaseTime	   mStopTime		 startTime	  mCurrTime
	}
	else
	{
		return (float)
			(((mCurrTime - mPausedTime)-mBaseTime)*mSecondsPerCount);
	}
}