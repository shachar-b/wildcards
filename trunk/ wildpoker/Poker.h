#pragma once
#include "game.h"

class Poker :
	public Game
{
private:
	virtual void initRound();
	virtual void getDecisions();	
	virtual void decideWinners(int givenPoints=1);
	virtual void initGame();
	virtual const char * returnNameOfWinningPlayer();
public:
	Poker(void);
	~Poker(void);
};
