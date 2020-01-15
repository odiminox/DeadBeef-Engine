#ifndef STATEMANP_H_
#define STATEMANP_H_

class GameState
{
private:

	bool bGameRunning;//Game Running

public:

	bool bTempRunning;//Public access
	int iGameState;//Current Game State

	//init Function
	void StateSetUp(int &iState){
		bGameRunning = true;
		iState = 0;

		return;
	}

	bool StateGameTest(bool &bGame){
		bGame = bGameRunning;

		if (bGame == false){
			return false;
		}
		else{
			return true;
		}
	}
};

#endif